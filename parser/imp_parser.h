#ifndef IMP_PARSER_H
#define IMP_PARSER_H

#include"../lexer/imp_lexer.h"
#include"../types/imp_environment.h"
#include"imp_nodes.h"

class OperatorPriotity {
private:
    TokenTypes tokenTypes;
public:
    int priority(IMPTokenType type) {
        if (type == tokenTypes.Colon())     return 16;
        if (type == tokenTypes.OP_Args())   return 15;
        if (type == tokenTypes.OP_Index())  return 15;
        if (type == tokenTypes.Negative())  return 14;
        if (type == tokenTypes.Power())     return 13;
        if (type == tokenTypes.Mult())      return 12;
        if (type == tokenTypes.Divide())    return 12;
        if (type == tokenTypes.Mod())       return 12;
        if (type == tokenTypes.Plus())      return 11;
        if (type == tokenTypes.Minus())     return 11;
        if (type == tokenTypes.BitShiftLeft())  return 10;
        if (type == tokenTypes.BitShiftRight()) return 10;
        if (type == tokenTypes.Less())      return 9;
        if (type == tokenTypes.More())      return 9;
        if (type == tokenTypes.LessEqual()) return 9;
        if (type == tokenTypes.MoreEqual()) return 9;
        if (type == tokenTypes.Equal())     return 8;
        if (type == tokenTypes.NotEqual())  return 8;
        if (type == tokenTypes.BitAnd())    return 7;
        if (type == tokenTypes.BitXor())    return 6;
        if (type == tokenTypes.BitOr())     return 5;
        if (type == tokenTypes.And())       return 4;
        if (type == tokenTypes.Xor())       return 3;
        if (type == tokenTypes.Or())        return 2;
        if (type == tokenTypes.Assign())    return 1;
        return 0;
    }
    int priority(IMPToken token) {
        return priority(token.type);
    }
};

//extern OperatorPriotity opr;

class IMPParser {
private:
    OperatorPriotity opr;
    TokenTypes tokenTypes;
    std::vector<IMPToken> _tokens;
    int _pos;

    std::vector<IMPTokenType> unar_operator_types = {
        tokenTypes.Negative()
    };
    std::vector<IMPTokenType> bin_operator_types = {
        tokenTypes.Colon(),
        tokenTypes.Power(),
        tokenTypes.Mult(),
        tokenTypes.Divide(),
        tokenTypes.Mod(),
        tokenTypes.Plus(),
        tokenTypes.Minus(),
        tokenTypes.BitShiftLeft(),
        tokenTypes.BitShiftRight(),
        tokenTypes.Less(),
        tokenTypes.More(),
        tokenTypes.LessEqual(),
        tokenTypes.MoreEqual(),
        tokenTypes.Equal(),
        tokenTypes.NotEqual(),
        tokenTypes.BitAnd(),
        tokenTypes.BitXor(),
        tokenTypes.BitOr(),
        tokenTypes.And(),
        tokenTypes.Xor(),
        tokenTypes.Or(),
        tokenTypes.Assign()
    };
    
    std::vector<IMPTokenType> expr_types = {tokenTypes.Decimal(),tokenTypes.Hexidec(),tokenTypes.Binary(),tokenTypes.Ident(),tokenTypes.Colon(),tokenTypes.String(),tokenTypes.Comma(),
        tokenTypes.BrOpSquare(),tokenTypes.BrClSquare(),tokenTypes.BrOpCircle(),tokenTypes.BrClCircle(),
        tokenTypes.Power(),tokenTypes.Mult(),tokenTypes.Divide(),tokenTypes.Mod(),tokenTypes.Plus(),tokenTypes.Minus(),
        tokenTypes.BitAnd(),tokenTypes.BitXor(),tokenTypes.BitOr(),tokenTypes.BitShiftLeft(),tokenTypes.BitShiftRight(),
        tokenTypes.And(),tokenTypes.Xor(),tokenTypes.Or(),tokenTypes.Equal(),tokenTypes.NotEqual(),tokenTypes.Negative(),
        tokenTypes.Less(),tokenTypes.More(),tokenTypes.LessEqual(),tokenTypes.MoreEqual(),tokenTypes.KwTrue(),tokenTypes.KwFalse(),
        tokenTypes.Assign(),tokenTypes.Semicolon()};

    IMPToken match(std::vector<IMPTokenType> expected) {
        if (_tokens.size()<1) return IMPToken(NULL_TOKEN,"NULL",0,0);
        if (_pos < _tokens.size()) {
            IMPToken currentToken = _tokens[_pos];
            for (int i = 0; i < expected.size(); i++) {
                if (expected[i].name == currentToken.type.name) {
                    _pos++;
                    return currentToken;
                }
            }
        }
        _pos++;
        return IMPToken(NULL_TOKEN,"NULL",_tokens[_pos].row,_tokens[_pos].col);
    }

    IMPToken require(std::vector<IMPTokenType> expected) {
        IMPToken token = match(expected);
        if (token.type==NULL_TOKEN) {
            std::string str = "";
            for (int i = 0; i < expected.size(); i++) {
                str += expected[i].name + (i+1==expected.size() ? "" : "/");
            }
            
            errors.push_back(
                imperr::message(imperr::semantic::expected_token_not_found,"Expected token not found",str,token.row,token.col)
            );
            return IMPToken(NULL_TOKEN,"NULL",0,0);
        }
        return token;
    }

public:
    IMPParser(std::vector<IMPToken> tokens, std::string file_name) : _tokens(tokens),_pos(0),filename(file_name) {}
    ~IMPParser() {}

    std::vector<imperr::message> errors;
    std::vector<IMPAstNode> nodes;
    std::vector<std::string> required_files;
    std::string filename;

    std::vector<IMPToken> parsePolish(std::vector<IMPToken> tokens) {
        std::vector<IMPToken> stack;
        std::vector<IMPToken> result;
        bool past_var = false;
        bool args_close = false;
        int pos = 0;

        while (tokens.size() > pos) {
            IMPToken token = tokens[pos];
            if ((token.type == tokenTypes.Decimal())
                or (token.type == tokenTypes.Hexidec())
                or (token.type == tokenTypes.Binary())
                or (token.type == tokenTypes.Ident())
                or (token.type == tokenTypes.String())
                or (token.type == tokenTypes.KwTrue())
                or (token.type == tokenTypes.KwFalse())
                or ((token.type == tokenTypes.BrOpCircle()) and past_var)
                or ((token.type == tokenTypes.BrOpSquare()) and past_var)) {
                if (token.type == tokenTypes.BrOpSquare()) {
                    pos++;
                    std::vector<IMPToken> temp;
                    int count_br = 0;
                    while (tokens.size() > pos) {
                        if (tokens[pos].type==tokenTypes.BrClSquare()) {
                            if (count_br > 0) {
                                temp.push_back(tokens[pos]);
                                pos++;
                                count_br--;
                            }
                            else {
                                break;
                            }
                        }
                        else if (tokens[pos].type==tokenTypes.BrOpSquare()) {
                            count_br++;
                            temp.push_back(tokens[pos]);
                            pos++;
                        }
                        else {
                            temp.push_back(tokens[pos]);
                            pos++;
                        }
                    }
                    if (tokens.size() <= pos) {
                        errors.push_back(
                            imperr::message(imperr::semantic::index_error,"Index error","\"]\" not found",token.row,token.col,filename)
                        );
                        return result;
                    }
                    
                    if (temp.size() < 1) {
                        errors.push_back(
                            imperr::message(imperr::semantic::index_error,"Index error","There is no index",token.row,token.col,filename)
                        );
                        return result;
                    }
                    std::vector<IMPToken> temp_result = parsePolish(temp);
                    for (IMPToken t : temp_result) result.push_back(t);
                    result.push_back(IMPToken(tokenTypes.OP_Index(),"[]",token.row,token.col));
                }
                else if (token.type == tokenTypes.BrOpCircle()) {
                    pos++;
                    std::vector<IMPToken> temp;
                    int count_br = 0;
                    int arg_count = 0;
                    while (tokens.size() > pos) {
                        if (tokens[pos].type==tokenTypes.BrClCircle()) {
                            if (count_br > 0) {
                                temp.push_back(tokens[pos]);
                                pos++;
                                count_br--;
                            }
                            else {
                                break;
                            }
                        }
                        else if (tokens[pos].type==tokenTypes.BrOpCircle()) {
                            count_br++;
                            temp.push_back(tokens[pos]);
                            pos++;
                        }
                        else if ((tokens[pos].type==tokenTypes.Comma()) and (count_br<1)) {
                            std::vector<IMPToken> temp_result = parsePolish(temp);
                            for (IMPToken t : temp_result) result.push_back(t);
                            temp.clear();
                            pos++;
                            arg_count++;
                        }
                        else {
                            temp.push_back(tokens[pos]);
                            pos++;
                        }
                    }
                    args_close = true;
                    if (tokens.size() <= pos) {
                        errors.push_back(
                            imperr::message(imperr::semantic::args_error,"Args error","\")\" not found",token.row,token.col,filename)
                        );
                        return result;
                    }
                    
                    if (temp.size()>0) arg_count++;
                    std::vector<IMPToken> temp_result = parsePolish(temp);
                    for (IMPToken t : temp_result) result.push_back(t);
                    result.push_back(IMPToken(tokenTypes.ARGS_COUNT(),std::to_string(arg_count),token.row,token.col));
                    result.push_back(IMPToken(tokenTypes.OP_Args(),"()",token.row,token.col));
                }
                else result.push_back(token);
            }
            else if ((token.type == bin_operator_types) or (token.type == unar_operator_types)) {
                if (stack.size() < 1) stack.push_back(token);
                else if (opr.priority(stack.back()) > opr.priority(token)) {
                    while (stack.size() > 0) {
                        if (opr.priority(stack.back()) > opr.priority(token)) {
                            result.push_back(stack.back());
                            stack.pop_back();
                        }
                        else break;
                    }
                    stack.push_back(token);
                }
                else stack.push_back(token);
            }
            else if (token.type == tokenTypes.BrOpCircle()) {
                stack.push_back(token);
            }
            else if (token.type == tokenTypes.BrClCircle()) {
                while ((stack.back().type != tokenTypes.BrOpCircle()) and (stack.size() > 0)) {
                    result.push_back(stack.back());
                    stack.pop_back();
                }
                if (stack.size() < 1) {
                    std::string str = "";
                    for (int i = 0; i < tokens.size(); i++) str += tokens[i].text;
                    errors.push_back(
                        imperr::message(imperr::semantic::invalid_expression,"Invalid expression",str,token.row,token.col,filename)
                    );
                    return result;
                }
                else {
                    stack.pop_back(); //erase open circle bracket (
                }
            }
            else {
                errors.push_back(
                    imperr::message(imperr::semantic::parse_crash,"PARSE CRASH","Expression parse",token.row,token.col,filename)
                );
                return result;
            }
            if (token.type == tokenTypes.Ident()) past_var=true;
            else past_var=false;
            if (args_close) {
                past_var = true;
                args_close = false;
            }
            pos++;
        }
        while (stack.size() > 0) {
            result.push_back(stack.back());
            stack.pop_back();
        }
        return result;
    }

    IMPAstNode parseExpression(std::vector<IMPToken> math_tokens) {
        std::vector<IMPToken> result = parsePolish(math_tokens);
        IMPAstNode out_node(result[0]);
        for (IMPToken t : result) {
            out_node.childs.push_back(t);
        }
        
        std::vector<IMPAstNode> tree;
        for (IMPToken token : result) {
            if (token.type == std::vector<IMPTokenType>{tokenTypes.Decimal(),tokenTypes.Hexidec(),tokenTypes.Binary(),tokenTypes.String(),
                                            tokenTypes.Ident(),tokenTypes.ARGS_COUNT(),
                                            tokenTypes.KwTrue(),tokenTypes.KwFalse()}) {
                tree.push_back(IMPAstNode(token));
            }
            else if (token.type == bin_operator_types) {
                if (tree.size() < 2) {
                    errors.push_back(
                        imperr::message(imperr::semantic::operator_error,"Operator error",token.text,token.row,token.col,filename)
                    );
                    return tree[0];
                }
                else {
                    IMPAstNode bin_op(token);
                    bin_op.childs.push_back(tree[tree.size()-2]);
                    bin_op.childs.push_back(tree[tree.size()-1]);
                    tree.pop_back();
                    tree.pop_back();
                    tree.push_back(bin_op);
                }
            }
            else if (token.type == unar_operator_types) {
                if (tree.size() < 1) {
                    errors.push_back(
                        imperr::message(imperr::semantic::operator_error,"Operator error",token.text,token.row,token.col,filename)
                    );
                    return tree[0];
                }
                else {
                    IMPAstNode unar_op(token);
                    unar_op.childs.push_back(tree[tree.size()-1]);
                    tree.pop_back();
                    tree.push_back(unar_op);
                }
            }
            else if (token.type == std::vector<IMPTokenType>{tokenTypes.OP_Index()}) {
                if (tree.size() < 2) {
                    errors.push_back(
                        imperr::message(imperr::semantic::operator_error,"Operator error",token.text,token.row,token.col,filename)
                    );
                    return tree[0];
                }
                else {
                    IMPAstNode index_op(token);
                    index_op.childs.push_back(tree[tree.size()-2]);
                    index_op.childs.push_back(tree[tree.size()-1]);
                    tree.pop_back();
                    tree.pop_back();
                    tree.push_back(index_op);
                }
            }
            else if (token.type == std::vector<IMPTokenType>{tokenTypes.OP_Args()}) {
                if (tree.back().value.type != tokenTypes.ARGS_COUNT()) {
                    errors.push_back(
                        imperr::message(imperr::semantic::args_error,"Args error","There is no arguments",token.row,token.col,filename)
                    );
                    return tree[0];
                }
                int args_count = std::stoi(tree.back().value.text);
                tree.pop_back();

                std::vector<IMPAstNode> temp_stack;
                while (args_count > 0) {
                    temp_stack.push_back(tree.back());
                    tree.pop_back();
                    args_count--;
                }
                IMPAstNode func(token);
                func.childs.push_back(tree.back());
                tree.pop_back();
                while (temp_stack.size()>0) {
                    func.childs.push_back(temp_stack.back());
                    temp_stack.pop_back();
                }
                for (IMPAstNode node : temp_stack) func.childs.push_back(node);
                tree.push_back(func);
            }
            else {
                errors.push_back(
                    imperr::message(imperr::semantic::parse_crash,"PARSE CRASH","Expression CRASH",token.row,token.col,filename)
                );
                return IMPAstNode(token);
            }
        }
        return tree[0];
    }

    IMPAstNode parseVarDefinition(IMPToken var_token) {
        IMPAstNode out_node(var_token);
        IMPToken token = require({tokenTypes.Ident()});
        if (token.type == NULL_TOKEN) return out_node;

        std::vector<IMPToken> expr_list = {token};
        while (true) {
            token = match(expr_types);
            if ((token.type == NULL_TOKEN) or (token.type == tokenTypes.Semicolon())) {
                break;
            }
            else expr_list.push_back(token);
        }

        if (token.type == NULL_TOKEN) return out_node;

        out_node.childs.push_back(parseExpression(expr_list));

        return out_node;
    }

    IMPAstNode parseFieldInit(IMPToken field_token) {
        IMPAstNode out_node(field_token);
        IMPToken token = require({tokenTypes.Ident()});
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(IMPAstNode(token));
        token = require({tokenTypes.Semicolon()});
        if (token.type == NULL_TOKEN) return out_node;
        return out_node;
    }

    IMPAstNode parseFuncInit(IMPToken func_token) {
        IMPAstNode out_node(func_token);
        IMPToken token = require({tokenTypes.KwInt(),tokenTypes.KwByte(),tokenTypes.KwWord(),tokenTypes.KwDWord(),tokenTypes.KwFloat(),tokenTypes.KwChar(),tokenTypes.KwBool()});
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(IMPAstNode(token));
        token = require({tokenTypes.Ident()});
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(IMPAstNode(token));
        token = require({tokenTypes.BrOpCircle()});
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(IMPAstNode(token));
        while (_pos < _tokens.size()) {
            token = require({tokenTypes.KwInt(),tokenTypes.KwByte(),tokenTypes.KwWord(),tokenTypes.KwDWord(),tokenTypes.KwFloat(),tokenTypes.KwChar(),tokenTypes.KwBool(),tokenTypes.BrClCircle()});
            if (token.type == NULL_TOKEN) return out_node;
            IMPAstNode arg(token);
            if (token.type == tokenTypes.BrClCircle()) {
                out_node.childs.push_back(token);
                break;
            }
            token = require({tokenTypes.Ident()});
            if (token.type == NULL_TOKEN) return out_node;
            arg.childs.push_back(token);
            out_node.childs.push_back(arg);
            token = require({tokenTypes.Comma(),tokenTypes.BrClCircle()});
            if (token.type == NULL_TOKEN) return out_node;
            if (token.type == tokenTypes.BrClCircle()) {
                out_node.childs.push_back(token);
                break;
            }
        }
        token = require({tokenTypes.KwReturn()});
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(parseReturn(token));
        return out_node;
    }

    IMPAstNode parseMatrix(IMPToken mx_token) {
        IMPAstNode out_node(mx_token);
        IMPToken token = require({tokenTypes.Ident()});
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(IMPAstNode(token));
        token = require({tokenTypes.BrOpSquare()});
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(IMPAstNode(token));

        token = require({tokenTypes.Decimal(),tokenTypes.BrClSquare()});
        if (token.type == NULL_TOKEN) return out_node;
        if (token.type == tokenTypes.Decimal()) {
            out_node.childs.push_back(IMPAstNode(token));
            token = require({tokenTypes.BrClSquare()});
            if (token.type == NULL_TOKEN) return out_node;
            out_node.childs.push_back(IMPAstNode(token));
        }
        else if (token.type == tokenTypes.BrClSquare()) {
            out_node.childs.push_back(IMPAstNode(token));
        }

        token = require({tokenTypes.BrOpCurly()});
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(IMPAstNode(token));

        std::vector<IMPTokenType> req_types({
            tokenTypes.KwInt(),tokenTypes.KwFloat(),tokenTypes.KwChar(),tokenTypes.KwBool(),
            tokenTypes.KwHide(),tokenTypes.KwFunc(),tokenTypes.KwMx(),
            tokenTypes.BrClCurly()
        });
        token = match(req_types);
        while (true) {
            if ((token.type == tokenTypes.BrClCurly()) or (token.type == NULL_TOKEN)) {
                break;
            }
            else if ((token.type == tokenTypes.KwInt()) or
                (token.type == tokenTypes.KwByte()) or
                (token.type == tokenTypes.KwWord()) or
                (token.type == tokenTypes.KwDWord()) or
                (token.type == tokenTypes.KwFloat()) or
                (token.type == tokenTypes.KwChar()) or
                (token.type == tokenTypes.KwBool())) out_node.childs.push_back(parseFieldInit(token));
            else if (token.type == tokenTypes.KwHide()) out_node.childs.push_back(IMPAstNode(token));
            else if (token.type == tokenTypes.KwFunc()) out_node.childs.push_back(parseFuncInit(token));
            else if (token.type == tokenTypes.KwMx()) out_node.childs.push_back(parseMatrix(token));
            token = match(req_types);
        }
        if (token.type == NULL_TOKEN) {
            errors.push_back(
                imperr::message(imperr::semantic::parse_crash,"PARSE CRASH","Parse matrix",token.row,token.col,filename)
            );
            return out_node;
        }
        out_node.childs.push_back(IMPAstNode(token));
        return out_node;
    }

    IMPAstNode parseIf(IMPToken if_token) {
        IMPAstNode out_node(if_token);
        IMPToken token = require({tokenTypes.BrOpCircle()});
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(token);
        int circle_counter = 0;
        std::vector<IMPToken> expr_list;
        while (true) {
            token = match(expr_types);
            if (token.type == tokenTypes.BrClCircle()) {
                if (circle_counter > 0) {
                    expr_list.push_back(token);
                    circle_counter--;
                }
                else {
                    break;
                }
            }
            else if (token.type == tokenTypes.BrOpCircle()) {
                circle_counter++;
                expr_list.push_back(token);
            }
            else if (token.type == tokenTypes.Semicolon()) {
                break;
            }
            else if (token.type == NULL_TOKEN) {
                break;
            }
            else expr_list.push_back(token);
        }
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(parseExpression(expr_list));
        out_node.childs.push_back(IMPAstNode(token));
        token = require({tokenTypes.BrOpCurly()});
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(IMPAstNode(token));
        std::vector<IMPAstNode> ops_vec = parseInstructions();
        for (IMPAstNode op : ops_vec) {
            out_node.childs.push_back(op);
        }
        return out_node;
    }

    IMPAstNode parseElse(IMPToken else_token) {
        IMPAstNode out_node(else_token);
        IMPToken token = require({tokenTypes.BrOpCurly()});
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(IMPAstNode(token));
        std::vector<IMPAstNode> ops_vec = parseInstructions();
        for (IMPAstNode op : ops_vec) {
            out_node.childs.push_back(op);
        }
        return out_node;
    }

    IMPAstNode parseWhile(IMPToken while_token) {
        IMPAstNode out_node(while_token);
        IMPToken token = require({tokenTypes.BrOpCircle()});
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(token);
        int circle_counter = 0;
        std::vector<IMPToken> expr_list;
        while (true) {
            token = match(expr_types);
            if (token.type == tokenTypes.BrClCircle()) {
                if (circle_counter > 0) {
                    expr_list.push_back(token);
                    circle_counter--;
                }
                else {
                    break;
                }
            }
            else if (token.type == tokenTypes.BrOpCircle()) {
                circle_counter++;
                expr_list.push_back(token);
            }
            else if (token.type == tokenTypes.Semicolon()) {
                break;
            }
            else if (token.type == NULL_TOKEN) {
                break;
            }
            else expr_list.push_back(token);
        }
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(parseExpression(expr_list));
        out_node.childs.push_back(IMPAstNode(token));
        token = require({tokenTypes.BrOpCurly()});
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(IMPAstNode(token));
        std::vector<IMPAstNode> ops_vec = parseInstructions();
        for (IMPAstNode op : ops_vec) {
            out_node.childs.push_back(op);
        }
        return out_node;
    }

    IMPAstNode parseReturn(IMPToken return_node) {
        IMPAstNode out_node(return_node);
        IMPToken token(return_node);
        std::vector<IMPToken> expr_list;
        while (true) {
            token = match(expr_types);
            if ((token.type == NULL_TOKEN) or (token.type == tokenTypes.Semicolon())) {
                break;
            }
            else expr_list.push_back(token);
        }
        if (token.type == NULL_TOKEN) return out_node;
        if (expr_list.size() > 0) out_node.childs.push_back(parseExpression(expr_list));
        return out_node;
    }

    IMPAstNode parseProc(IMPToken proc_token) {
        IMPAstNode out_node(proc_token);
        IMPToken token = require({tokenTypes.Ident(),tokenTypes.KwInt(),tokenTypes.KwByte(),tokenTypes.KwWord(),tokenTypes.KwDWord(),tokenTypes.KwFloat(),tokenTypes.KwChar(),tokenTypes.KwBool()});
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(IMPAstNode(token));
        if (token.type != tokenTypes.Ident()) {
            token = require({tokenTypes.Ident()});
            if (token.type == NULL_TOKEN) return out_node;
            out_node.childs.push_back(IMPAstNode(token));
        }
        token = require({tokenTypes.BrOpCircle()});
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(IMPAstNode(token));
        while (_pos < _tokens.size()) {
            token = require({tokenTypes.KwInt(),tokenTypes.KwByte(),tokenTypes.KwWord(),tokenTypes.KwDWord(),tokenTypes.KwFloat(),tokenTypes.KwChar(),tokenTypes.KwBool(),tokenTypes.BrClCircle()});
            if (token.type == NULL_TOKEN) return out_node;
            IMPAstNode arg(token);
            if (token.type == tokenTypes.BrClCircle()) {
                out_node.childs.push_back(token);
                break;
            }
            token = require({tokenTypes.Ident()});
            if (token.type == NULL_TOKEN) return out_node;
            arg.childs.push_back(token);
            out_node.childs.push_back(arg);
            token = require({tokenTypes.Comma(),tokenTypes.BrClCircle()});
            if (token.type == NULL_TOKEN) return out_node;
            if (token.type == tokenTypes.BrClCircle()) {
                out_node.childs.push_back(token);
                break;
            }
        }
        token = require({tokenTypes.BrOpCurly()});
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(IMPAstNode(token));
        std::vector<IMPAstNode> ops_vec = parseInstructions();
        for (IMPAstNode op : ops_vec) {
            out_node.childs.push_back(op);
        }
        return out_node;
    }

    std::vector<IMPAstNode> parseInstructions() {
        std::vector<IMPAstNode> out_nodes;
        IMPTokenType stopper = tokenTypes.BrClCurly();
        std::vector<IMPTokenType> req_types = {
            tokenTypes.KwIf(),tokenTypes.KwElif(),tokenTypes.KwElse(),tokenTypes.KwWhile(),
            tokenTypes.KwReturn(),
            tokenTypes.KwInt(),tokenTypes.KwByte(),tokenTypes.KwWord(),tokenTypes.KwDWord(),tokenTypes.KwFloat(),tokenTypes.KwChar(),tokenTypes.KwBool(),
            tokenTypes.Ident(),
            stopper
        };
        int curly_counter = 0;
        while (_pos < _tokens.size()) {
            IMPToken token = match(req_types);
            if (token.type == tokenTypes.KwIf()) {
                out_nodes.push_back(parseIf(token));
            }
            else if (token.type == tokenTypes.KwElif()) {
                if (out_nodes.back().value.type == std::vector<IMPTokenType>{tokenTypes.KwIf(),tokenTypes.KwElif()}) {
                    out_nodes.push_back(parseIf(token));
                }
                else {
                    errors.push_back(
                        imperr::message(imperr::semantic::statement_required,"Statement required",token.text,token.row,token.col,filename)
                    );
                    return out_nodes;
                }
            }
            else if (token.type == tokenTypes.KwElse()) {
                if (out_nodes.back().value.type == std::vector<IMPTokenType>{tokenTypes.KwIf(),tokenTypes.KwElif()}) {
                    out_nodes.push_back(parseElse(token));
                }
                else {
                    errors.push_back(
                        imperr::message(imperr::semantic::statement_required,"Statement required",token.text,token.row,token.col,filename)
                    );
                    return out_nodes;
                }
            }
            else if (token.type == tokenTypes.KwWhile()) {
                out_nodes.push_back(parseWhile(token));
            }
            else if (token.type == tokenTypes.KwReturn()) {
                out_nodes.push_back(parseReturn(token));
            }
            else if (token.type == std::vector<IMPTokenType>{tokenTypes.KwInt(),tokenTypes.KwFloat(),tokenTypes.KwChar(),tokenTypes.KwBool()}) {
                out_nodes.push_back(parseVarDefinition(token));
            }
            else if (token.type == tokenTypes.Ident()) {
                std::vector<IMPToken> expr_list = {token};
                while (true) {
                    token = match(expr_types);
                    if ((token.type == NULL_TOKEN) or (token.type == tokenTypes.Semicolon())) {
                        break;
                    }
                    else expr_list.push_back(token);
                }
                if (token.type == NULL_TOKEN) return out_nodes;
                out_nodes.push_back(parseExpression(expr_list));
            }
            else if (token.type == stopper) {
                out_nodes.push_back(IMPAstNode(token));
                return out_nodes;
            }
            else {
                return out_nodes;
            }
        }
        errors.push_back(
            imperr::message(imperr::semantic::unknown_instruction,"Unknown instruction",_tokens[_pos].text,_tokens[_pos].row,_tokens[_pos].col,filename)
        );

        return out_nodes;
    }

    IMPAstNode parseEnv(IMPToken env_token) {
        IMPAstNode out_node(env_token);
        IMPToken token = require({tokenTypes.Ident()});
        if (token.type != NULL_TOKEN) {
            out_node.childs.push_back(IMPAstNode(token));
            token = require({tokenTypes.BrOpCurly()});
            if (token.type != NULL_TOKEN) {
                out_node.childs.push_back(IMPAstNode(token));
                std::vector<IMPTokenType> req_types({
                    tokenTypes.KwInt(),tokenTypes.KwByte(),tokenTypes.KwWord(),tokenTypes.KwDWord(),tokenTypes.KwFloat(),tokenTypes.KwChar(),tokenTypes.KwBool(),
                    tokenTypes.KwMx(),tokenTypes.KwProc(),
                    tokenTypes.BrClCurly()
                });
                token = require(req_types);
                while (true) {
                    if ((token.type == tokenTypes.BrClCurly()) or (token.type == NULL_TOKEN)) {
                        break;
                    }
                    if ((token.type == tokenTypes.KwInt()) or
                        (token.type == tokenTypes.KwByte()) or
                        (token.type == tokenTypes.KwWord()) or
                        (token.type == tokenTypes.KwDWord()) or
                        (token.type == tokenTypes.KwFloat()) or
                        (token.type == tokenTypes.KwChar()) or
                        (token.type == tokenTypes.KwBool())) out_node.childs.push_back(parseVarDefinition(token));
                    if (token.type == tokenTypes.KwMx()) out_node.childs.push_back(parseMatrix(token));
                    if (token.type == tokenTypes.KwProc()) out_node.childs.push_back(parseProc(token));
                    token = require(req_types);
                }
                if (token.type == NULL_TOKEN) {
                    errors.push_back(
                        imperr::message(imperr::semantic::parse_crash,"PARSE CRASH","Parse environment",token.row,token.col,filename)
                    );
                    return out_node;
                }
                out_node.childs.push_back(IMPAstNode(token));
                return out_node;
            }
        }
        return out_node;
    }

    IMPAstNode parseAdd(IMPToken add_token) {
        IMPAstNode out_node(add_token);
        IMPToken token = require({tokenTypes.String()});
        if (token.type == NULL_TOKEN) return out_node;
        out_node.childs.push_back(token);
        required_files.push_back(token.text);
        return out_node;
    }

    int parse() {
        while(true) {
            IMPToken token = match({tokenTypes.KwEnv(),tokenTypes.SwAdd()});
            if (token.type == tokenTypes.KwEnv()) {
                nodes.push_back(parseEnv(token));
            }
            else if (token.type == tokenTypes.SwAdd()) {
                nodes.push_back(parseAdd(token));
            }
            else if (_pos < _tokens.size()) {
                errors.push_back(
                    imperr::message(imperr::semantic::out_of_env,
                        "Out of environment","Only service words can be outside of the environment",token.row,token.col,filename)
                );
                break;
            }
            else {
                break;
            }
        }

        return 0;
    }
};

#endif // IMP_PARSER_H
