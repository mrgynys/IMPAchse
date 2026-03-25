#ifndef IMP_LEXER_H
#define IMP_LEXER_H

#include<vector>
#include<list>
#include<map>

#include"../types/imp_error.h"

#include"imp_token.h"

// IMP LEXER

class IMPLexer {
private:
    TokenTypes tokenTypes;
    std::vector<std::string> code;
    int row;
    int col;

    IMPToken lexToken(std::string word, int rowpos, int colpos) {
        if (tokenTypes.Space().is(word))        return IMPToken(tokenTypes.Space(),word,rowpos,colpos);
        if (tokenTypes.KwIf().is(word))         return IMPToken(tokenTypes.KwIf(),word,rowpos,colpos);
        if (tokenTypes.KwElif().is(word))       return IMPToken(tokenTypes.KwElif(),word,rowpos,colpos);
        if (tokenTypes.KwElse().is(word))       return IMPToken(tokenTypes.KwElse(),word,rowpos,colpos);
        if (tokenTypes.KwWhile().is(word))      return IMPToken(tokenTypes.KwWhile(),word,rowpos,colpos);
        if (tokenTypes.KwInt().is(word))        return IMPToken(tokenTypes.KwInt(),word,rowpos,colpos);
        if (tokenTypes.KwByte().is(word))       return IMPToken(tokenTypes.KwByte(),word,rowpos,colpos);
        if (tokenTypes.KwWord().is(word))       return IMPToken(tokenTypes.KwWord(),word,rowpos,colpos);
        if (tokenTypes.KwDWord().is(word))      return IMPToken(tokenTypes.KwDWord(),word,rowpos,colpos);
        if (tokenTypes.KwFloat().is(word))      return IMPToken(tokenTypes.KwFloat(),word,rowpos,colpos);
        if (tokenTypes.KwChar().is(word))       return IMPToken(tokenTypes.KwChar(),word,rowpos,colpos);
        if (tokenTypes.KwBool().is(word))       return IMPToken(tokenTypes.KwBool(),word,rowpos,colpos);
        if (tokenTypes.KwHide().is(word))       return IMPToken(tokenTypes.KwHide(),word,rowpos,colpos);
        if (tokenTypes.KwMx().is(word))         return IMPToken(tokenTypes.KwMx(),word,rowpos,colpos);
        if (tokenTypes.KwEnv().is(word))        return IMPToken(tokenTypes.KwEnv(),word,rowpos,colpos);
        if (tokenTypes.KwFunc().is(word))       return IMPToken(tokenTypes.KwFunc(),word,rowpos,colpos);
        if (tokenTypes.KwProc().is(word))       return IMPToken(tokenTypes.KwProc(),word,rowpos,colpos);
        if (tokenTypes.KwReturn().is(word))     return IMPToken(tokenTypes.KwReturn(),word,rowpos,colpos);
        if (tokenTypes.SwAdd().is(word))        return IMPToken(tokenTypes.SwAdd(),word,rowpos,colpos);
        if (tokenTypes.KwTrue().is(word))       return IMPToken(tokenTypes.KwTrue(),word,rowpos,colpos);
        if (tokenTypes.KwFalse().is(word))      return IMPToken(tokenTypes.KwFalse(),word,rowpos,colpos);
        if (tokenTypes.Decimal().is(word))      return IMPToken(tokenTypes.Decimal(),word,rowpos,colpos);
        if (tokenTypes.Hexidec().is(word))      return IMPToken(tokenTypes.Hexidec(),word.substr(2,word.size()-2),rowpos,colpos);
        if (tokenTypes.Binary().is(word))       return IMPToken(tokenTypes.Binary(),word.substr(2,word.size()-2),rowpos,colpos);
        if (tokenTypes.BrOpCircle().is(word))   return IMPToken(tokenTypes.BrOpCircle(),word,rowpos,colpos);
        if (tokenTypes.BrClCircle().is(word))   return IMPToken(tokenTypes.BrClCircle(),word,rowpos,colpos);
        if (tokenTypes.BrOpSquare().is(word))   return IMPToken(tokenTypes.BrOpSquare(),word,rowpos,colpos);
        if (tokenTypes.BrClSquare().is(word))   return IMPToken(tokenTypes.BrClSquare(),word,rowpos,colpos);
        if (tokenTypes.BrOpCurly().is(word))    return IMPToken(tokenTypes.BrOpCurly(),word,rowpos,colpos);
        if (tokenTypes.BrClCurly().is(word))    return IMPToken(tokenTypes.BrClCurly(),word,rowpos,colpos);
        if (tokenTypes.Assign().is(word))       return IMPToken(tokenTypes.Assign(),word,rowpos,colpos);
        if (tokenTypes.Power().is(word))        return IMPToken(tokenTypes.Power(),word,rowpos,colpos);
        if (tokenTypes.Mod().is(word))          return IMPToken(tokenTypes.Mod(),word,rowpos,colpos);
        if (tokenTypes.Mult().is(word))         return IMPToken(tokenTypes.Mult(),word,rowpos,colpos);
        if (tokenTypes.Divide().is(word))       return IMPToken(tokenTypes.Divide(),word,rowpos,colpos);
        if (tokenTypes.Plus().is(word))         return IMPToken(tokenTypes.Plus(),word,rowpos,colpos);
        if (tokenTypes.Minus().is(word))        return IMPToken(tokenTypes.Minus(),word,rowpos,colpos);
        if (tokenTypes.Equal().is(word))        return IMPToken(tokenTypes.Equal(),word,rowpos,colpos);
        if (tokenTypes.NotEqual().is(word))     return IMPToken(tokenTypes.NotEqual(),word,rowpos,colpos);
        if (tokenTypes.MoreEqual().is(word))    return IMPToken(tokenTypes.MoreEqual(),word,rowpos,colpos);
        if (tokenTypes.LessEqual().is(word))    return IMPToken(tokenTypes.LessEqual(),word,rowpos,colpos);
        if (tokenTypes.More().is(word))         return IMPToken(tokenTypes.More(),word,rowpos,colpos);
        if (tokenTypes.Less().is(word))         return IMPToken(tokenTypes.Less(),word,rowpos,colpos);
        if (tokenTypes.Negative().is(word))     return IMPToken(tokenTypes.Negative(),word,rowpos,colpos);
        if (tokenTypes.And().is(word))          return IMPToken(tokenTypes.And(),word,rowpos,colpos);
        if (tokenTypes.Or().is(word))           return IMPToken(tokenTypes.Or(),word,rowpos,colpos);
        if (tokenTypes.Xor().is(word))          return IMPToken(tokenTypes.Xor(),word,rowpos,colpos);
        if (tokenTypes.BitAnd().is(word))       return IMPToken(tokenTypes.BitAnd(),word,rowpos,colpos);
        if (tokenTypes.BitOr().is(word))        return IMPToken(tokenTypes.BitOr(),word,rowpos,colpos);
        if (tokenTypes.BitXor().is(word))       return IMPToken(tokenTypes.BitXor(),word,rowpos,colpos);
        if (tokenTypes.BitShiftLeft().is(word)) return IMPToken(tokenTypes.BitShiftLeft(),word,rowpos,colpos);
        if (tokenTypes.BitShiftRight().is(word))return IMPToken(tokenTypes.BitShiftRight(),word,rowpos,colpos);
        if (tokenTypes.Comma().is(word))        return IMPToken(tokenTypes.Comma(),word,rowpos,colpos);
        if (tokenTypes.Colon().is(word))        return IMPToken(tokenTypes.Colon(),word,rowpos,colpos);
        if (tokenTypes.Semicolon().is(word))    return IMPToken(tokenTypes.Semicolon(),word,rowpos,colpos);
        if (tokenTypes.String().is(word))       return IMPToken(tokenTypes.String(),word.erase(word.size()-1,1).erase(0,1),rowpos,colpos);
        if (tokenTypes.Ident().is(word))        return IMPToken(tokenTypes.Ident(),word,rowpos,colpos);
        return IMPToken(tokenTypes.Error(),word,rowpos,colpos);
    }

public:
    std::vector<imperr::message> errors;
    std::vector<IMPToken> tokens;
    std::string filename;
    
    IMPLexer(std::vector<std::string> imp_code, std::string file_name)
    : code(imp_code),row(0),col(0),filename(file_name) {
        
    }
    ~IMPLexer() {}

    int lex() {
        if (code.size() < 1) return 0;
        
        std::string splitters = ",^%*/+-:;!()[]{}";
        std::string bit_log_op = "&|#";
        std::string double_op = "=<>";
        std::string x_splitters = " \t\n";
        std::string one_line_comment = "//";
        std::string multi_line_comment_begin = "/?";
        std::string multi_line_comment_end   = "?/";

        int cur_word_row = 0;
        int cur_word_col = 0;
        std::string cur_word = "";

        bool string_begins = false;
        bool multi_line_comment_begins = false;

        int com_begin_counter = 0;

        row = 0;

        for (std::string str : code) {
            if (string_begins) {
                errors.push_back(
                    imperr::message(imperr::syntax::multiline_string_is_illegal,"Multi-line strings is illegal",cur_word,cur_word_row,cur_word_col,filename)
                );
                string_begins = false;
            }
            row++;
            cur_word_row = row;
            cur_word_col = 1;
            col = 0;
            if (str.size()<1) continue;
            while (col < str.size()) {
                col++;
                if (std::string({str[col-1],str[col]})==multi_line_comment_begin) {
                    com_begin_counter++;
                    if (com_begin_counter>1) continue;
                    multi_line_comment_begins = true;
                    IMPToken cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                    if (cur_token.type.name!="SPACE") tokens.push_back(cur_token);
                    if (cur_token.type.name=="ERROR")
                        errors.push_back(
                            imperr::message(imperr::syntax::unknown_token,"Unknown token",cur_word,cur_word_row,cur_word_col,filename)
                        );
                    cur_word = "";
                    cur_word_col = col+1;
                    col++;
                }
                else if (std::string({str[col-1],str[col]})==multi_line_comment_end) {
                    com_begin_counter--;
                    if (com_begin_counter<0) errors.push_back(imperr::message(imperr::syntax::unexpected_end_of_comment,"Unexpected end of comment",multi_line_comment_end,row,col,filename));
                    if (multi_line_comment_begins and (com_begin_counter<1)) multi_line_comment_begins = false;
                    cur_word = "";
                    cur_word_col = col+1;
                    col++;
                }
                else if (multi_line_comment_begins) {
                    continue;
                }
                else if (std::string({str[col-1],str[col]})==one_line_comment) {
                    IMPToken cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                    if (cur_token.type.name!="SPACE") tokens.push_back(cur_token);
                    if (cur_token.type.name=="ERROR")
                        errors.push_back(
                            imperr::message(imperr::syntax::unknown_token,"Unknown token",cur_word,cur_word_row,cur_word_col,filename)
                        );
                    cur_word = "";
                    cur_word_col = 0;
                    break;
                }
                else if (str[col-1]=='\"') {
                    if (string_begins) cur_word += str[col-1];
                    IMPToken cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                    if (cur_token.type.name!="SPACE") tokens.push_back(cur_token);
                    if (cur_token.type.name=="ERROR")
                        errors.push_back(
                            imperr::message(imperr::syntax::unknown_token,"Unknown token",cur_word,cur_word_row,cur_word_col,filename)
                        );
                    if (string_begins) {
                        cur_word = "";
                        cur_word_col = col+1;
                    }
                    else {
                        cur_word = str[col-1];
                        cur_word_col = col;
                    }
                    string_begins = !string_begins;
                }
                else if (string_begins) {
                    cur_word += str[col-1];
                }
                else if (x_splitters.find(str[col-1])!=std::string::npos) {
                    IMPToken cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                    if (cur_token.type.name!="SPACE") tokens.push_back(cur_token);
                    if (cur_token.type.name=="ERROR")
                        errors.push_back(
                            imperr::message(imperr::syntax::unknown_token,"Unknown token",cur_word,cur_word_row,cur_word_col,filename)
                        );
                    cur_word = "";
                    cur_word_col = col+1;
                }
                else if (splitters.find(str[col-1])!=std::string::npos) {
                    IMPToken cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                    if (cur_token.type.name!="SPACE") tokens.push_back(cur_token);
                    if (cur_token.type.name=="ERROR")
                        errors.push_back(
                            imperr::message(imperr::syntax::unknown_token,"Unknown token",cur_word,cur_word_row,cur_word_col,filename)
                        );
                    cur_word = str[col-1];
                    cur_word_col = col;
                    IMPToken new_cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                    if (new_cur_token.type.name!="SPACE") tokens.push_back(new_cur_token);
                    if (new_cur_token.type.name=="ERROR")
                        errors.push_back(
                            imperr::message(imperr::syntax::unknown_token,"Unknown token",cur_word,cur_word_row,cur_word_col,filename)
                        );
                    cur_word = "";
                    cur_word_col = col+1;
                }
                else if (bit_log_op.find(str[col-1])!=std::string::npos) {
                    if (str[col-1]==str[col]) {
                        IMPToken cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                        if (cur_token.type.name!="SPACE") tokens.push_back(cur_token);
                        if (cur_token.type.name=="ERROR")
                            errors.push_back(
                                imperr::message(imperr::syntax::unknown_token,"Unknown token",cur_word,cur_word_row,cur_word_col,filename)
                            );
                        cur_word = "";
                        cur_word += str[col-1];
                        cur_word += str[col];
                        cur_word_col = col;
                        IMPToken new_cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                        tokens.push_back(new_cur_token);
                        cur_word = "";
                        cur_word_col = col+2;
                        col++;
                    }
                    else {
                        IMPToken cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                        if (cur_token.type.name!="SPACE") tokens.push_back(cur_token);
                        if (cur_token.type.name=="ERROR")
                            errors.push_back(
                                imperr::message(imperr::syntax::unknown_token,"Unknown token",cur_word,cur_word_row,cur_word_col,filename)
                            );
                        cur_word = "";
                        cur_word += str[col-1];
                        cur_word_col = col;
                        IMPToken new_cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                        tokens.push_back(new_cur_token);
                        cur_word = "";
                        cur_word_col = col+1;
                    }
                }
                else if (double_op.find(str[col-1])!=std::string::npos) {
                    if (double_op.find(str[col])!=std::string::npos) {
                        IMPToken cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                        if (cur_token.type.name!="SPACE") tokens.push_back(cur_token);
                        if (cur_token.type.name=="ERROR")
                            errors.push_back(
                                imperr::message(imperr::syntax::unknown_token,"Unknown token",cur_word,cur_word_row,cur_word_col,filename)
                            );
                        cur_word = "";
                        cur_word += str[col-1];
                        cur_word += str[col];
                        cur_word_col = col;
                        IMPToken new_cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                        if (new_cur_token.type.name=="ERROR")
                            errors.push_back(
                                imperr::message(imperr::syntax::unknown_token,"Unknown token",cur_word,cur_word_row,cur_word_col,filename)
                            );
                        tokens.push_back(new_cur_token);
                        cur_word = "";
                        cur_word_col = col+1;
                        col++;
                    }
                    else {
                        IMPToken cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                        if (cur_token.type.name!="SPACE") tokens.push_back(cur_token);
                        if (cur_token.type.name=="ERROR")
                            errors.push_back(
                                imperr::message(imperr::syntax::unknown_token,"Unknown token",cur_word,cur_word_row,cur_word_col,filename)
                            );
                        cur_word = "";
                        cur_word += str[col-1];
                        cur_word_col = col;
                        IMPToken new_cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                        if (new_cur_token.type.name=="ERROR")
                            errors.push_back(
                                imperr::message(imperr::syntax::unknown_token,"Unknown token",cur_word,cur_word_row,cur_word_col,filename)
                            );
                        tokens.push_back(new_cur_token);
                        cur_word = "";
                        cur_word_col = col+1;
                    }
                }
                else {
                    cur_word += str[col-1];
                }
            }
            if (cur_word != "") {
                IMPToken cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                if (cur_token.type.name!="SPACE") tokens.push_back(cur_token);
                if (cur_token.type.name=="ERROR")
                    errors.push_back(
                        imperr::message(imperr::syntax::unknown_token,"Unknown token",cur_word,cur_word_row,cur_word_col,filename)
                    );
                cur_word = "";
                cur_word_col = col;
            }
        }
        return 0;
    }


};

#endif //IMP_LEXER_H
