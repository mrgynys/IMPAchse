#ifndef IMP_EXECUTRIX_H
#define IMP_EXECUTRIX_H

#include<vector>
#include<algorithm>

#include"imp_project_manager.h"
#include"lexer/imp_lexer.h"
#include"parser/imp_parser.h"
#include"archivarius/archivarius.h"
#include"types/imp_data_types.h"

#include"std/imp_operators.h"

#include"../qeditdbwindow.h"

std::string str_to_hex(std::string i );

class SrcNode {
private:
    std::string show(int tab_num) {
        std::string tabs_str = "";
        for (int t = 0; t < tab_num; t++) {
            tabs_str += " ";
        }
        std::string temp = tabs_str + file.filename() + file.ext() + "\n";
        for (int i = 0; i < include.size(); i++) {
            temp += tabs_str + include[i].show(tab_num+1);
        }
        return temp;
    }
public:
    archivarius::file file;
    std::vector<std::string> code;
    std::vector<IMPAstNode> nodes;
    std::vector<IMPEnv> envs;
    std::vector<SrcNode> include;
    std::vector<archivarius::file> contents;

    SrcNode() {}
    SrcNode(archivarius::file file) : file(file) {}
    SrcNode(const SrcNode& srcnode) {
        this->file=srcnode.file;
        this->code=srcnode.code;
        this->nodes=srcnode.nodes;
        this->include=srcnode.include;
        this->envs=srcnode.envs;
        this->contents=srcnode.contents;
    }
    ~SrcNode() {}

    std::string show() {
        std::string temp = file.filename() + file.ext() + "\n";
        for (int i = 0; i < include.size(); i++) {
            temp += include[i].show(1);
        }
        return temp;
    }

    SrcNode& operator=(const SrcNode& srcnode) {
        this->file=srcnode.file;
        this->code=srcnode.code;
        this->nodes=srcnode.nodes;
        this->include=srcnode.include;
        this->envs=srcnode.envs;
        this->contents=srcnode.contents;
        return *this;
    }
};

bool always_included(std::string path, std::vector<archivarius::file> contents);

class Executrix {
private:
    DataTypes dataTypes;
    TokenTypes tokenTypes;
    std::string _show_lexer_out;
    std::string _show_parser_out;
    int _exe_code;

public:
    std::vector<imperr::message> errors;
    std::vector<archivarius::file> files;
    std::vector<std::string> button_triggers;
    std::vector<bool> button_state;
    std::vector<std::string> indic_triggers;
    std::vector<bool> indic_state;
    SrcNode src;
    QSqlDatabase* db;

    Executrix() {
        _exe_code = 0;
        _show_lexer_out = "IMP LEXING\nTYPE\t\tTEXT\n";
        _show_parser_out = "IMP PARSING\n";
    }
    ~Executrix() {}

    void set_db(QSqlDatabase* database) {
        db = database;
    }

    IMPAstNode replace_this_pointer(int index, IMPAstNode n) {
        if (n.value.text == "this") {
            n.value.type = tokenTypes.Decimal();
            n.value.text = std::to_string(index);
            return n;
        }
        for (int i = 0; i < n.childs.size(); i++) {
            n.childs[i] = replace_this_pointer(index,n.childs[i]);
        }
        return n;
    }

    IMPAstNode replace_func(int index, IMPFunc fnc, std::vector<IMPAstNode> args, std::vector<IMPEnv> lscope) {
        if (fnc.args.size() != args.size()) {
            errors.push_back(imperr::message(imperr::exe::invalid_number_of_args,"Invalid number of arguments",std::to_string(args.size())));
            return args[0];
        }
        IMPEnv scp("scp");
        for (int i = 0; i < fnc.args.size(); i++) {
            Calc clc(lscope);
            if (fnc.args[i].type == dataTypes.Int()) {
                scp.int_ents[i] = IMPEntityInt(clc.calcIntEntity(args[i]));
            }
            else if (fnc.args[i].type == dataTypes.Byte()) {
                scp.byte_ents[i] = IMPEntityByte(clc.calcByteEntity(args[i]));
            }
            else if (fnc.args[i].type == dataTypes.Word()) {
                scp.word_ents[i] = IMPEntityWord(clc.calcWordEntity(args[i]));
            }
            else if (fnc.args[i].type == dataTypes.DWord()) {
                scp.dword_ents[i] = IMPEntityDWord(clc.calcDWordEntity(args[i]));
            }
            else if (fnc.args[i].type == dataTypes.Float()) {
                scp.float_ents[i] = IMPEntityFloat(clc.calcFloatEntity(args[i]));
            }
            else if (fnc.args[i].type == dataTypes.Char()) {
                scp.char_ents[i] = IMPEntityChar(clc.calcCharEntity(args[i]));
            }
            else if (fnc.args[i].type == dataTypes.Bool()) {
                scp.bool_ents[i] = IMPEntityBool(clc.calcBoolEntity(args[i]));
            }
            scp.idents.push_back(fnc.args[i]);
            for (imperr::message msg : clc.errors) errors.push_back(msg);
        }
        std::vector<IMPEnv> fake_scope = lscope;
        fake_scope.push_back(scp);
        Calc ret_clc(fake_scope);
        if (fnc.type == dataTypes.Int()) {
            int res = ret_clc.calcIntEntity(replace_this_pointer(index,fnc.data));
            return IMPAstNode(IMPToken(tokenTypes.Decimal(),std::to_string(res),0,0));
        }
        else if (fnc.type == dataTypes.Byte()) {
            int res = ret_clc.calcByteEntity(replace_this_pointer(index,fnc.data));
            return IMPAstNode(IMPToken(tokenTypes.Decimal(),std::to_string(res),0,0));
        }
        else if (fnc.type == dataTypes.Word()) {
            int res = ret_clc.calcWordEntity(replace_this_pointer(index,fnc.data));
            return IMPAstNode(IMPToken(tokenTypes.Decimal(),std::to_string(res),0,0));
        }
        else if (fnc.type == dataTypes.DWord()) {
            int res = ret_clc.calcDWordEntity(replace_this_pointer(index,fnc.data));
            return IMPAstNode(IMPToken(tokenTypes.Decimal(),std::to_string(res),0,0));
        }
        else if (fnc.type == dataTypes.Float()) {
            int res = ret_clc.calcFloatEntity(replace_this_pointer(index,fnc.data));
            return IMPAstNode(IMPToken(tokenTypes.Decimal(),std::to_string(res),0,0));
        }
        else if (fnc.type == dataTypes.Char()) {
            std::string res = ret_clc.calcCharEntity(replace_this_pointer(index,fnc.data));
            return IMPAstNode(IMPToken(tokenTypes.String(),res,0,0));
        }
        else if (fnc.type == dataTypes.Bool()) {
            bool res = ret_clc.calcBoolEntity(replace_this_pointer(index,fnc.data));
            if (res) {
                return IMPAstNode(IMPToken(tokenTypes.KwTrue(),"true",0,0));
            }
            return IMPAstNode(IMPToken(tokenTypes.KwFalse(),"false",0,0));
        }
        for (imperr::message msg : ret_clc.errors) errors.push_back(msg);
        return args[0];
    }

    IMPAstNode replace_calls(IMPAstNode node, std::vector<IMPEnv> lscope) {
        IMPAstNode ret_node(node);

        if (ret_node.value.type == tokenTypes.Colon()) {
            if (ret_node.childs[0].value.type == tokenTypes.OP_Index()) {
                ret_node.childs[0].childs[1] = replace_calls(node.childs[0].childs[1],lscope);
                int env_i = findId(ret_node.childs[0].childs[0].value.text,lscope);
                int mx_i = lscope[env_i].findId(ret_node.childs[0].childs[0].value.text);
                if (ret_node.childs[1].value.type == tokenTypes.OP_Args()) {
                    int func_i = lscope[env_i].matrixes[mx_i].findId(ret_node.childs[1].childs[0].value.text);
                    std::vector<IMPAstNode> fargs;
                    for (int i = 1; i < ret_node.childs[1].childs.size(); i++) {
                        fargs.push_back(replace_calls(ret_node.childs[1].childs[i],lscope));
                    }
                    Calc clc(lscope);
                    return replace_func(clc.calcIntEntity(ret_node.childs[0].childs[1]),lscope[env_i].matrixes[mx_i]._funcs[func_i],fargs,lscope);
                }
            }
            else if (ret_node.childs[0].value.type == tokenTypes.Ident()) {
                int env_i = findId(ret_node.childs[0].value.text,lscope);
                int mx_i = lscope[env_i].findId(ret_node.childs[0].value.text);
                if (ret_node.childs[1].value.type == tokenTypes.OP_Args()) {
                    if (ret_node.childs[1].childs[0].value.text == "size") {
                        if (lscope[env_i].matrixes[mx_i]._idents.size() < 1) {
                            return IMPAstNode(IMPToken(tokenTypes.Decimal(),"0",0,0));
                        }
                        else {
                            IMPDataType fdt = lscope[env_i].matrixes[mx_i]._idents[0].type;
                            IMPAstNode retn(IMPToken(tokenTypes.Decimal(),"0",0,0));
                            if (fdt == dataTypes.Int()) {
                                retn.value.text = std::to_string(lscope[env_i].matrixes[mx_i]._fields_int[0].size());
                            }
                            else if (fdt == dataTypes.Byte()) {
                                retn.value.text = std::to_string(lscope[env_i].matrixes[mx_i]._fields_byte[0].size());
                            }
                            else if (fdt == dataTypes.Word()) {
                                retn.value.text = std::to_string(lscope[env_i].matrixes[mx_i]._fields_word[0].size());
                            }
                            else if (fdt == dataTypes.DWord()) {
                                retn.value.text = std::to_string(lscope[env_i].matrixes[mx_i]._fields_dword[0].size());
                            }
                            else if (fdt == dataTypes.Float()) {
                                retn.value.text = std::to_string(lscope[env_i].matrixes[mx_i]._fields_float[0].size());
                            }
                            else if (fdt == dataTypes.Char()) {
                                retn.value.text = std::to_string(lscope[env_i].matrixes[mx_i]._fields_char[0].size());
                            }
                            else if (fdt == dataTypes.Bool()) {
                                retn.value.text = std::to_string(lscope[env_i].matrixes[mx_i]._fields_bool[0].size());
                            }
                            return retn;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < node.childs.size(); i++) ret_node.childs[i] = replace_calls(node.childs[i],lscope);

        if (ret_node.value.type == tokenTypes.OP_Args()) {
            int env_i;
            int proc_i;
            IMPProc prc;
            std::vector<IMPAstNode> pargs;
            if (ret_node.childs[0].value.text == "sql")
            {
                for (int i = 1; i < ret_node.childs.size(); i++) pargs.push_back(ret_node.childs[i]);
                exeVoidProc(ret_node.childs[0].value.text,pargs,lscope);
                ret_node.childs.clear();
                ret_node.value.type = tokenTypes.Null();
                return ret_node;
            }
            env_i = findId(ret_node.childs[0].value.text,lscope);
            proc_i = lscope[env_i].findId(ret_node.childs[0].value.text);
            prc = lscope[env_i].proc[proc_i];
            for (int i = 1; i < ret_node.childs.size(); i++) pargs.push_back(ret_node.childs[i]);
            if (prc.type == dataTypes.Void()) {
                exeVoidProc(ret_node.childs[0].value.text,pargs,lscope);
                ret_node.childs.clear();
                ret_node.value.type = tokenTypes.Null();
            }
            else if (prc.type == dataTypes.Int()) {
                int res = exeIntProc(ret_node.childs[0].value.text,pargs,lscope);
                ret_node.childs.clear();
                ret_node.value.type = tokenTypes.Decimal();
                ret_node.value.text = std::to_string(res);
            }
            else if (prc.type == dataTypes.Byte()) {
                uint8_t res = exeByteProc(ret_node.childs[0].value.text,pargs,lscope);
                ret_node.childs.clear();
                ret_node.value.type = tokenTypes.Decimal();
                ret_node.value.text = std::to_string(res);
            }
            else if (prc.type == dataTypes.Word()) {
                uint16_t res = exeWordProc(ret_node.childs[0].value.text,pargs,lscope);
                ret_node.childs.clear();
                ret_node.value.type = tokenTypes.Decimal();
                ret_node.value.text = std::to_string(res);
            }
            else if (prc.type == dataTypes.DWord()) {
                uint32_t res = exeDWordProc(ret_node.childs[0].value.text,pargs,lscope);
                ret_node.childs.clear();
                ret_node.value.type = tokenTypes.Decimal();
                ret_node.value.text = std::to_string(res);
            }
            else if (prc.type == dataTypes.Float()) {
                double res = exeFloatProc(ret_node.childs[0].value.text,pargs,lscope);
                ret_node.childs.clear();
                ret_node.value.type = tokenTypes.Decimal();
                ret_node.value.text = std::to_string(res);
            }
            else if (prc.type == dataTypes.Char()) {
                std::string res = exeCharProc(ret_node.childs[0].value.text,pargs,lscope);
                ret_node.childs.clear();
                ret_node.value.type = tokenTypes.String();
                ret_node.value.text = res;
            }
            else if (prc.type == dataTypes.Bool()) {
                bool res = exeBoolProc(ret_node.childs[0].value.text,pargs,lscope);
                ret_node.childs.clear();
                if (res) {
                    ret_node.value.type = tokenTypes.KwTrue();
                    ret_node.value.text = "true";
                }
                else {
                    ret_node.value.type = tokenTypes.KwFalse();
                    ret_node.value.text = "false";
                }
            }
        }
        return ret_node;
    }

    void exeStdMxProc(IMPEnv& lscope, IMPAstNode op) {
        std::string mx_name = op.childs[0].value.text;
        std::string proc_name = op.childs[1].childs[0].value.text;
        int env_i = findId(mx_name,src.envs);
        int mx_i = src.envs[env_i].findId(mx_name);
        std::vector<IMPAstNode> args;
        for (int i = 1; i < op.childs[1].childs.size(); i++) args.push_back(op.childs[1].childs[i]);
        std::vector<IMPID> needy_args;
        for (IMPID narg : src.envs[env_i].matrixes[mx_i]._idents) if (narg.type != dataTypes.Func()) needy_args.push_back(narg);
        if (proc_name == "push") {
            if (args.size() == needy_args.size()) {
                std::vector<IMPEnv> llscope = src.envs;
                llscope.push_back(lscope);
                Calc clc(llscope);
                for (int i = 0; i < src.envs[env_i].matrixes[mx_i].size(); i++) {
                    if (src.envs[env_i].matrixes[mx_i]._idents[i].type == dataTypes.Int()) {
                        src.envs[env_i].matrixes[mx_i]._fields_int[i].add(clc.calcIntEntity(replace_calls(args[i],llscope)));
                    }
                    else if (src.envs[env_i].matrixes[mx_i]._idents[i].type == dataTypes.Byte()) {
                        src.envs[env_i].matrixes[mx_i]._fields_byte[i].add(clc.calcByteEntity(args[i]));
                    }
                    else if (src.envs[env_i].matrixes[mx_i]._idents[i].type == dataTypes.Word()) {
                        src.envs[env_i].matrixes[mx_i]._fields_word[i].add(clc.calcWordEntity(args[i]));
                    }
                    else if (src.envs[env_i].matrixes[mx_i]._idents[i].type == dataTypes.DWord()) {
                        src.envs[env_i].matrixes[mx_i]._fields_dword[i].add(clc.calcDWordEntity(args[i]));
                    }
                    else if (src.envs[env_i].matrixes[mx_i]._idents[i].type == dataTypes.Float()) {
                        src.envs[env_i].matrixes[mx_i]._fields_float[i].add(clc.calcFloatEntity(args[i]));
                    }
                    else if (src.envs[env_i].matrixes[mx_i]._idents[i].type == dataTypes.Char()) {
                        src.envs[env_i].matrixes[mx_i]._fields_char[i].add(clc.calcCharEntity(args[i]));
                    }
                    else if (src.envs[env_i].matrixes[mx_i]._idents[i].type == dataTypes.Bool()) {
                        src.envs[env_i].matrixes[mx_i]._fields_bool[i].add(clc.calcBoolEntity(args[i]));
                    }
                }
            }
        }
        else if (proc_name == "pop") {
            if (args.size() == 0) {
                for (int i = 0; i < src.envs[env_i].matrixes[mx_i].size(); i++) {
                    if (src.envs[env_i].matrixes[mx_i]._idents[i].type == dataTypes.Int()) {
                        src.envs[env_i].matrixes[mx_i]._fields_int[i].pop();
                    }
                    else if (src.envs[env_i].matrixes[mx_i]._idents[i].type == dataTypes.Byte()) {
                        src.envs[env_i].matrixes[mx_i]._fields_byte[i].pop();
                    }
                    else if (src.envs[env_i].matrixes[mx_i]._idents[i].type == dataTypes.Word()) {
                        src.envs[env_i].matrixes[mx_i]._fields_word[i].pop();
                    }
                    else if (src.envs[env_i].matrixes[mx_i]._idents[i].type == dataTypes.DWord()) {
                        src.envs[env_i].matrixes[mx_i]._fields_dword[i].pop();
                    }
                    else if (src.envs[env_i].matrixes[mx_i]._idents[i].type == dataTypes.Float()) {
                        src.envs[env_i].matrixes[mx_i]._fields_float[i].pop();
                    }
                    else if (src.envs[env_i].matrixes[mx_i]._idents[i].type == dataTypes.Char()) {
                        src.envs[env_i].matrixes[mx_i]._fields_char[i].pop();
                    }
                    else if (src.envs[env_i].matrixes[mx_i]._idents[i].type == dataTypes.Bool()) {
                        src.envs[env_i].matrixes[mx_i]._fields_bool[i].pop();
                    }
                }
            }
        }
    }

    IMPAstNode exeInstructions(IMPEnv& local_scope, std::vector<IMPAstNode> ops, std::vector<IMPEnv>& ret_scope) {
        bool next_else_exe = false;
        for (int i = 0; i < ops.size(); i++) {
            std::vector<IMPEnv> fake_scope = src.envs;
            fake_scope.push_back(local_scope);
            if (ops[i].value.type == tokenTypes.Assign()) {
                next_else_exe = false;
                buildVarSet(local_scope,src.envs,replace_calls(ops[i],fake_scope));
            }
            else if (ops[i].value.type == tokenTypes.Colon()) {
                next_else_exe = false;
                exeStdMxProc(local_scope,ops[i]);
            }
            else if (ops[i].value.type == tokenTypes.OP_Args()) {
                next_else_exe = false;
                replace_calls(ops[i],fake_scope);
            }
            else if (ops[i].value.type == tokenTypes.KwReturn()) {
                next_else_exe = false;
                fake_scope.clear();
                fake_scope = src.envs;
                fake_scope.push_back(local_scope);
                if (ret_scope.size() < 1) ret_scope = fake_scope;
                return replace_calls(ops[i],fake_scope);
            }
            else if (ops[i].value.type == tokenTypes.KwIf()) {
                next_else_exe = false;
                Calc ccond(fake_scope);
                bool condition = ccond.calcBoolEntity(replace_calls(ops[i].childs[1],fake_scope));
                for (imperr::message msg : ccond.errors) errors.push_back(msg);
                if (errors.size() > 0) return IMPAstNode(IMPToken(NULL_TOKEN,"",0,0));
                if (condition) {
                    std::vector<IMPAstNode> local_ops;
                    for (int p = 4; p < ops[i].childs.size(); p++) {
                        if (ops[i].childs[p].value.type == tokenTypes.BrClCurly()) break;
                        else local_ops.push_back(ops[i].childs[p]);
                    }
                    IMPAstNode rnode = exeInstructions(local_scope,local_ops,ret_scope);
                    if (rnode.value.type == tokenTypes.KwReturn()) {
                        return replace_calls(rnode,fake_scope);
                    }
                }
                else next_else_exe = true;
            }
            else if (ops[i].value.type == tokenTypes.KwElif()) {
                if (!next_else_exe) continue;
                Calc ccond(fake_scope);
                bool condition = ccond.calcBoolEntity(replace_calls(ops[i].childs[1],fake_scope));
                for (imperr::message msg : ccond.errors) errors.push_back(msg);
                if (errors.size() > 0) return IMPAstNode(IMPToken(NULL_TOKEN,"",0,0));
                if (condition) {
                    std::vector<IMPAstNode> local_ops;
                    for (int p = 4; p < ops[i].childs.size(); p++) {
                        if (ops[i].childs[p].value.type == tokenTypes.BrClCurly()) break;
                        else local_ops.push_back(ops[i].childs[p]);
                    }
                    IMPAstNode rnode = exeInstructions(local_scope,local_ops,ret_scope);
                    if (rnode.value.type == tokenTypes.KwReturn()) {
                        return replace_calls(rnode,fake_scope);
                    }
                    next_else_exe = false;
                }
                else next_else_exe = true;
            }
            else if (ops[i].value.type == tokenTypes.KwElse()) {
                if (!next_else_exe) continue;
                std::vector<IMPAstNode> local_ops;
                for (int p = 1; p < ops[i].childs.size(); p++) {
                    if (ops[i].childs[p].value.type == tokenTypes.BrClCurly()) break;
                    else local_ops.push_back(ops[i].childs[p]);
                }
                IMPAstNode rnode = exeInstructions(local_scope,local_ops,ret_scope);
                if (rnode.value.type == tokenTypes.KwReturn()) {
                        fake_scope.clear();
                        fake_scope = src.envs;
                        fake_scope.push_back(local_scope);
                        if (ret_scope.size() < 1) ret_scope = fake_scope;
                        return replace_calls(rnode,fake_scope);
                    }
                next_else_exe = false;
            }
            else if (ops[i].value.type == tokenTypes.KwWhile()) {
                next_else_exe = false;
                Calc ccond(fake_scope);
                bool condition = ccond.calcBoolEntity(replace_calls(ops[i].childs[1],fake_scope));
                for (imperr::message msg : ccond.errors) errors.push_back(msg);
                if (errors.size() > 0) return IMPAstNode(IMPToken(NULL_TOKEN,"",0,0));
                std::vector<IMPAstNode> local_ops;
                for (int p = 4; p < ops[i].childs.size(); p++) {
                    if (ops[i].childs[p].value.type == tokenTypes.BrClCurly()) break;
                    else local_ops.push_back(ops[i].childs[p]);
                }
                while (condition) {
                    IMPAstNode rnode = exeInstructions(local_scope,local_ops,ret_scope);
                    for (imperr::message msg : ccond.errors) errors.push_back(msg);
                    if (errors.size() > 0) return IMPAstNode(IMPToken(NULL_TOKEN,"",0,0));
                    if (rnode.value.type == tokenTypes.KwReturn()) {
                        return replace_calls(rnode,fake_scope);
                    }
                    fake_scope.clear();
                    fake_scope = src.envs;
                    fake_scope.push_back(local_scope);
                    ccond.scope = fake_scope;
                    condition = ccond.calcBoolEntity(ops[i].childs[1]);
                }
            }
            else if (dataTypes.get(ops[i].value.type)!=dataTypes.Null()) {
                next_else_exe = false;
                buildVarDefinition(local_scope,fake_scope,ops[i]);
            }
            fake_scope.clear();
        }
        return IMPAstNode(IMPToken(NULL_TOKEN,"",0,0));
    }
    
    int exeIntProc(std::string procedure, std::vector<IMPAstNode> args, std::vector<IMPEnv> cxt) {
        int proc_env_i = findId(procedure,cxt);
        if (proc_env_i == nfind) {
            errors.push_back(imperr::message(imperr::exe::unknown_procedure,"Unknown procedure",procedure));
            return 0;
        }
        int proc_i = cxt[proc_env_i].findId(procedure);
        IMPProc proc = cxt[proc_env_i].proc[proc_i];
        if (proc.type != dataTypes.Int()) {
            errors.push_back(imperr::message(imperr::exe::incorrect_procedure_return_type,"Incorrect procedure return type",proc.type.name));
        }
        if (proc.args.size() != args.size()) {
            errors.push_back(imperr::message(imperr::exe::invalid_number_of_args,"Invalid number of arguments",std::to_string(args.size())));
            return 0;
        }
        IMPEnv scp("scp");
        for (int i = 0; i < proc.args.size(); i++) {
            Calc clc(cxt);
            if (proc.args[i].type == dataTypes.Int()) {
                scp.int_ents[i] = IMPEntityInt(clc.calcIntEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Byte()) {
                scp.byte_ents[i] = IMPEntityByte(clc.calcByteEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Word()) {
                scp.word_ents[i] = IMPEntityWord(clc.calcWordEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.DWord()) {
                scp.dword_ents[i] = IMPEntityDWord(clc.calcDWordEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Float()) {
                scp.float_ents[i] = IMPEntityFloat(clc.calcFloatEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Char()) {
                scp.char_ents[i] = IMPEntityChar(clc.calcCharEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Bool()) {
                scp.bool_ents[i] = IMPEntityBool(clc.calcBoolEntity(args[i]));
            }
            scp.idents.push_back(proc.args[i]);
            for (imperr::message msg : clc.errors) errors.push_back(msg);
        }
        if (errors.size()>0) {
            return 0;
        }
        std::vector<IMPEnv> ret_scope;
        IMPAstNode ret_node = exeInstructions(scp,proc.ops,ret_scope);
        Calc ret_clc(ret_scope);
        int ret_result = ret_clc.calcIntEntity(ret_node.childs[0]);
        for (imperr::message msg : ret_clc.errors) errors.push_back(msg);
        return ret_result;
    }

    uint8_t exeByteProc(std::string procedure, std::vector<IMPAstNode> args, std::vector<IMPEnv> cxt) {
        int proc_env_i = findId(procedure,cxt);
        if (proc_env_i == nfind) {
            errors.push_back(imperr::message(imperr::exe::unknown_procedure,"Unknown procedure",procedure));
            return 0;
        }
        int proc_i = cxt[proc_env_i].findId(procedure);
        IMPProc proc = cxt[proc_env_i].proc[proc_i];
        if (proc.type != dataTypes.Byte()) {
            errors.push_back(imperr::message(imperr::exe::incorrect_procedure_return_type,"Incorrect procedure return type",proc.type.name));
        }
        if (proc.args.size() != args.size()) {
            errors.push_back(imperr::message(imperr::exe::invalid_number_of_args,"Invalid number of arguments",std::to_string(args.size())));
            return 0;
        }
        IMPEnv scp("scp");
        for (int i = 0; i < proc.args.size(); i++) {
            Calc clc(cxt);
            if (proc.args[i].type == dataTypes.Int()) {
                scp.int_ents[i] = IMPEntityInt(clc.calcIntEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Byte()) {
                scp.byte_ents[i] = IMPEntityByte(clc.calcByteEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Word()) {
                scp.word_ents[i] = IMPEntityWord(clc.calcWordEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.DWord()) {
                scp.dword_ents[i] = IMPEntityDWord(clc.calcDWordEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Float()) {
                scp.float_ents[i] = IMPEntityFloat(clc.calcFloatEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Char()) {
                scp.char_ents[i] = IMPEntityChar(clc.calcCharEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Bool()) {
                scp.bool_ents[i] = IMPEntityBool(clc.calcBoolEntity(args[i]));
            }
            scp.idents.push_back(proc.args[i]);
            for (imperr::message msg : clc.errors) errors.push_back(msg);
        }
        if (errors.size()>0) {
            return 0;
        }
        std::vector<IMPEnv> ret_scope;
        IMPAstNode ret_node = exeInstructions(scp,proc.ops,ret_scope);
        Calc ret_clc(ret_scope);
        uint8_t ret_result = ret_clc.calcByteEntity(ret_node.childs[0]);
        for (imperr::message msg : ret_clc.errors) errors.push_back(msg);
        return ret_result;
    }

    uint16_t exeWordProc(std::string procedure, std::vector<IMPAstNode> args, std::vector<IMPEnv> cxt) {
        int proc_env_i = findId(procedure,cxt);
        if (proc_env_i == nfind) {
            errors.push_back(imperr::message(imperr::exe::unknown_procedure,"Unknown procedure",procedure));
            return 0;
        }
        int proc_i = cxt[proc_env_i].findId(procedure);
        IMPProc proc = cxt[proc_env_i].proc[proc_i];
        if (proc.type != dataTypes.Word()) {
            errors.push_back(imperr::message(imperr::exe::incorrect_procedure_return_type,"Incorrect procedure return type",proc.type.name));
        }
        if (proc.args.size() != args.size()) {
            errors.push_back(imperr::message(imperr::exe::invalid_number_of_args,"Invalid number of arguments",std::to_string(args.size())));
            return 0;
        }
        IMPEnv scp("scp");
        for (int i = 0; i < proc.args.size(); i++) {
            Calc clc(cxt);
            if (proc.args[i].type == dataTypes.Int()) {
                scp.int_ents[i] = IMPEntityInt(clc.calcIntEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Byte()) {
                scp.byte_ents[i] = IMPEntityByte(clc.calcByteEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Word()) {
                scp.word_ents[i] = IMPEntityWord(clc.calcWordEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.DWord()) {
                scp.dword_ents[i] = IMPEntityDWord(clc.calcDWordEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Float()) {
                scp.float_ents[i] = IMPEntityFloat(clc.calcFloatEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Char()) {
                scp.char_ents[i] = IMPEntityChar(clc.calcCharEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Bool()) {
                scp.bool_ents[i] = IMPEntityBool(clc.calcBoolEntity(args[i]));
            }
            scp.idents.push_back(proc.args[i]);
            for (imperr::message msg : clc.errors) errors.push_back(msg);
        }
        if (errors.size()>0) {
            return 0;
        }
        std::vector<IMPEnv> ret_scope;
        IMPAstNode ret_node = exeInstructions(scp,proc.ops,ret_scope);
        Calc ret_clc(ret_scope);
        uint16_t ret_result = ret_clc.calcWordEntity(ret_node.childs[0]);
        for (imperr::message msg : ret_clc.errors) errors.push_back(msg);
        return ret_result;
    }

    uint32_t exeDWordProc(std::string procedure, std::vector<IMPAstNode> args, std::vector<IMPEnv> cxt) {
        int proc_env_i = findId(procedure,cxt);
        if (proc_env_i == nfind) {
            errors.push_back(imperr::message(imperr::exe::unknown_procedure,"Unknown procedure",procedure));
            return 0;
        }
        int proc_i = cxt[proc_env_i].findId(procedure);
        IMPProc proc = cxt[proc_env_i].proc[proc_i];
        if (proc.type != dataTypes.DWord()) {
            errors.push_back(imperr::message(imperr::exe::incorrect_procedure_return_type,"Incorrect procedure return type",proc.type.name));
        }
        if (proc.args.size() != args.size()) {
            errors.push_back(imperr::message(imperr::exe::invalid_number_of_args,"Invalid number of arguments",std::to_string(args.size())));
            return 0;
        }
        IMPEnv scp("scp");
        for (int i = 0; i < proc.args.size(); i++) {
            Calc clc(cxt);
            if (proc.args[i].type == dataTypes.Int()) {
                scp.int_ents[i] = IMPEntityInt(clc.calcIntEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Byte()) {
                scp.byte_ents[i] = IMPEntityByte(clc.calcByteEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Word()) {
                scp.word_ents[i] = IMPEntityWord(clc.calcWordEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.DWord()) {
                scp.dword_ents[i] = IMPEntityDWord(clc.calcDWordEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Float()) {
                scp.float_ents[i] = IMPEntityFloat(clc.calcFloatEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Char()) {
                scp.char_ents[i] = IMPEntityChar(clc.calcCharEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Bool()) {
                scp.bool_ents[i] = IMPEntityBool(clc.calcBoolEntity(args[i]));
            }
            scp.idents.push_back(proc.args[i]);
            for (imperr::message msg : clc.errors) errors.push_back(msg);
        }
        if (errors.size()>0) {
            return 0;
        }
        std::vector<IMPEnv> ret_scope;
        IMPAstNode ret_node = exeInstructions(scp,proc.ops,ret_scope);
        Calc ret_clc(ret_scope);
        uint32_t ret_result = ret_clc.calcDWordEntity(ret_node.childs[0]);
        for (imperr::message msg : ret_clc.errors) errors.push_back(msg);
        return ret_result;
    }

    double exeFloatProc(std::string procedure, std::vector<IMPAstNode> args, std::vector<IMPEnv> cxt) {
        int proc_env_i = findId(procedure,cxt);
        if (proc_env_i == nfind) {
            errors.push_back(imperr::message(imperr::exe::unknown_procedure,"Unknown procedure",procedure));
            return 0;
        }
        int proc_i = cxt[proc_env_i].findId(procedure);
        IMPProc proc = cxt[proc_env_i].proc[proc_i];
        if (proc.type != dataTypes.Float()) {
            errors.push_back(imperr::message(imperr::exe::incorrect_procedure_return_type,"Incorrect procedure return type",proc.type.name));
        }
        if (proc.args.size() != args.size()) {
            errors.push_back(imperr::message(imperr::exe::invalid_number_of_args,"Invalid number of arguments",std::to_string(args.size())));
            return 0;
        }
        IMPEnv scp("scp");
        for (int i = 0; i < proc.args.size(); i++) {
            Calc clc(cxt);
            if (proc.args[i].type == dataTypes.Int()) {
                scp.int_ents[i] = IMPEntityInt(clc.calcIntEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Byte()) {
                scp.byte_ents[i] = IMPEntityByte(clc.calcByteEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Word()) {
                scp.word_ents[i] = IMPEntityWord(clc.calcWordEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.DWord()) {
                scp.dword_ents[i] = IMPEntityDWord(clc.calcDWordEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Float()) {
                scp.float_ents[i] = IMPEntityFloat(clc.calcFloatEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Char()) {
                scp.char_ents[i] = IMPEntityChar(clc.calcCharEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Bool()) {
                scp.bool_ents[i] = IMPEntityBool(clc.calcBoolEntity(args[i]));
            }
            scp.idents.push_back(proc.args[i]);
            for (imperr::message msg : clc.errors) errors.push_back(msg);
        }
        if (errors.size()>0) {
            return 0;
        }
        std::vector<IMPEnv> ret_scope;
        IMPAstNode ret_node = exeInstructions(scp,proc.ops,ret_scope);
        Calc ret_clc(ret_scope);
        double ret_result = ret_clc.calcFloatEntity(ret_node.childs[0]);
        for (imperr::message msg : ret_clc.errors) errors.push_back(msg);
        return ret_result;
    }

    std::string exeCharProc(std::string procedure, std::vector<IMPAstNode> args, std::vector<IMPEnv> cxt) {
        int proc_env_i = findId(procedure,cxt);
        if (proc_env_i == nfind) {
            errors.push_back(imperr::message(imperr::exe::unknown_procedure,"Unknown procedure",procedure));
            return 0;
        }
        int proc_i = cxt[proc_env_i].findId(procedure);
        IMPProc proc = cxt[proc_env_i].proc[proc_i];
        if (proc.type != dataTypes.Char()) {
            errors.push_back(imperr::message(imperr::exe::incorrect_procedure_return_type,"Incorrect procedure return type",proc.type.name));
        }
        if (proc.args.size() != args.size()) {
            errors.push_back(imperr::message(imperr::exe::invalid_number_of_args,"Invalid number of arguments",std::to_string(args.size())));
            return 0;
        }
        IMPEnv scp("scp");
        for (int i = 0; i < proc.args.size(); i++) {
            Calc clc(cxt);
            if (proc.args[i].type == dataTypes.Int()) {
                scp.int_ents[i] = IMPEntityInt(clc.calcIntEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Byte()) {
                scp.byte_ents[i] = IMPEntityByte(clc.calcByteEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Word()) {
                scp.word_ents[i] = IMPEntityWord(clc.calcWordEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.DWord()) {
                scp.dword_ents[i] = IMPEntityDWord(clc.calcDWordEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Float()) {
                scp.float_ents[i] = IMPEntityFloat(clc.calcFloatEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Char()) {
                scp.char_ents[i] = IMPEntityChar(clc.calcCharEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Bool()) {
                scp.bool_ents[i] = IMPEntityBool(clc.calcBoolEntity(args[i]));
            }
            scp.idents.push_back(proc.args[i]);
            for (imperr::message msg : clc.errors) errors.push_back(msg);
        }
        if (errors.size()>0) {
            return 0;
        }
        std::vector<IMPEnv> ret_scope;
        IMPAstNode ret_node = exeInstructions(scp,proc.ops,ret_scope);
        Calc ret_clc(ret_scope);
        std::string ret_result = ret_clc.calcCharEntity(ret_node.childs[0]);
        for (imperr::message msg : ret_clc.errors) errors.push_back(msg);
        return ret_result;
    }

    bool exeBoolProc(std::string procedure, std::vector<IMPAstNode> args, std::vector<IMPEnv> cxt) {
        int proc_env_i = findId(procedure,cxt);
        if (proc_env_i == nfind) {
            errors.push_back(imperr::message(imperr::exe::unknown_procedure,"Unknown procedure",procedure));
            return 0;
        }
        int proc_i = cxt[proc_env_i].findId(procedure);
        IMPProc proc = cxt[proc_env_i].proc[proc_i];
        if (proc.type != dataTypes.Bool()) {
            errors.push_back(imperr::message(imperr::exe::incorrect_procedure_return_type,"Incorrect procedure return type",proc.type.name));
        }
        if (proc.args.size() != args.size()) {
            errors.push_back(imperr::message(imperr::exe::invalid_number_of_args,"Invalid number of arguments",std::to_string(args.size())));
            return 0;
        }
        IMPEnv scp("scp");
        for (int i = 0; i < proc.args.size(); i++) {
            Calc clc(cxt);
            if (proc.args[i].type == dataTypes.Int()) {
                scp.int_ents[i] = IMPEntityInt(clc.calcIntEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Byte()) {
                scp.byte_ents[i] = IMPEntityByte(clc.calcByteEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Word()) {
                scp.word_ents[i] = IMPEntityWord(clc.calcWordEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.DWord()) {
                scp.dword_ents[i] = IMPEntityDWord(clc.calcDWordEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Float()) {
                scp.float_ents[i] = IMPEntityFloat(clc.calcFloatEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Char()) {
                scp.char_ents[i] = IMPEntityChar(clc.calcCharEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Bool()) {
                scp.bool_ents[i] = IMPEntityBool(clc.calcBoolEntity(args[i]));
            }
            scp.idents.push_back(proc.args[i]);
            for (imperr::message msg : clc.errors) errors.push_back(msg);
        }
        if (errors.size()>0) {
            return 0;
        }
        std::vector<IMPEnv> ret_scope;
        IMPAstNode ret_node = exeInstructions(scp,proc.ops,ret_scope);
        Calc ret_clc(ret_scope);
        bool ret_result = ret_clc.calcBoolEntity(ret_node.childs[0]);
        for (imperr::message msg : ret_clc.errors) errors.push_back(msg);
        return ret_result;
    }

    void exeVoidProc(std::string procedure, std::vector<IMPAstNode> args, std::vector<IMPEnv> cxt) {
        if (procedure == "sql")
        {
            if (args.size() == 1)
            {
                Calc clc(cxt);
                IMPEntityChar sql_query = IMPEntityChar(clc.calcCharEntity(args[0]));
                QSqlQuery q;
                if (!q.exec(sql_query.get().c_str())) {
                    qDebug() << sql_query.get().c_str();
                    qDebug() << q.lastError().text();
                }
                else {
                    qDebug() << sql_query.get().c_str();
                    qDebug() << "Executed successfuly";
                }
                return;
            }
        }

        int proc_env_i = findId(procedure,cxt);
        if (proc_env_i == nfind) {
            errors.push_back(imperr::message(imperr::exe::unknown_procedure,"Unknown procedure",procedure));
            return;
        }
        int proc_i = cxt[proc_env_i].findId(procedure);
        IMPProc proc = cxt[proc_env_i].proc[proc_i];
        if (proc.type != dataTypes.Void()) {
            errors.push_back(imperr::message(imperr::exe::incorrect_procedure_return_type,"Incorrect procedure return type",proc.type.name));
        }
        if (proc.args.size() != args.size()) {
            errors.push_back(imperr::message(imperr::exe::invalid_number_of_args,"Invalid number of arguments",std::to_string(args.size())));
            return;
        }
        IMPEnv scp("scp");
        for (int i = 0; i < proc.args.size(); i++) {
            Calc clc(cxt);
            if (proc.args[i].type == dataTypes.Int()) {
                scp.int_ents[i] = IMPEntityInt(clc.calcIntEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Byte()) {
                scp.byte_ents[i] = IMPEntityByte(clc.calcByteEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Word()) {
                scp.word_ents[i] = IMPEntityWord(clc.calcWordEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.DWord()) {
                scp.dword_ents[i] = IMPEntityDWord(clc.calcDWordEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Float()) {
                scp.float_ents[i] = IMPEntityFloat(clc.calcFloatEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Char()) {
                scp.char_ents[i] = IMPEntityChar(clc.calcCharEntity(args[i]));
            }
            else if (proc.args[i].type == dataTypes.Bool()) {
                scp.bool_ents[i] = IMPEntityBool(clc.calcBoolEntity(args[i]));
            }
            scp.idents.push_back(proc.args[i]);
            for (imperr::message msg : clc.errors) errors.push_back(msg);
        }
        if (errors.size()>0) {
            return;
        }
        std::vector<IMPEnv> nnn;
        exeInstructions(scp,proc.ops,nnn);
    }

    int execute(std::string main_procedure) {
        int main_env_i = findId(main_procedure,src.envs);
        if (main_env_i == nfind) {
            errors.push_back(imperr::message(imperr::exe::main_proc_not_found,"Procedure \"main\" not found"));
            _exe_code = errors.size();
            return _exe_code;
        }

        exeIntProc(main_procedure,{},src.envs);

        _exe_code = errors.size();
        return _exe_code;
    }

    void build_button_triggers(std::vector<std::string> trg) {
        button_triggers = trg;
    }

    void indic_button_triggers(std::vector<std::string> trg) {
        indic_triggers = trg;
    }

    void buildVarSet(IMPEnv& env, std::vector<IMPEnv>& scope, IMPAstNode nodes) {
        std::vector<IMPEnv> fake_scope = scope;
        fake_scope.push_back(env);
        if (nodes.value.type == tokenTypes.Assign()) {
            if (nodes.childs[0].value.type == tokenTypes.Colon()) {
                if (findId(nodes.childs[0].childs[0].childs[0].value.text,scope)!=nfind) {
                    int env_index = findId(nodes.childs[0].childs[0].childs[0].value.text,scope);
                    int mx_index = scope[env_index].findId(nodes.childs[0].childs[0].childs[0].value.text);
                    int fld_index = scope[env_index].matrixes[mx_index].findId(nodes.childs[0].childs[1].value.text);
                    Calc clc(fake_scope);
                    int ele_index = clc.calcIntEntity(nodes.childs[0].childs[0].childs[1]);
                    IMPID var_id = scope[env_index].matrixes[mx_index]._idents[fld_index];
                    if (var_id.type == dataTypes.Func()) {
                        errors.push_back(imperr::message(imperr::exe::cant_assign_a_value_to_func,"You cant assign a value to function",nodes.childs[0].childs[0].childs[1].value.text,nodes.childs[0].childs[0].childs[1].value.row,nodes.childs[0].childs[0].childs[1].value.col));
                        return;
                    }
                    if (var_id.type == dataTypes.Int()) {
                        scope[env_index].matrixes[mx_index]._fields_int[fld_index].set(ele_index,clc.calcIntEntity(nodes.childs[1]));
                    }
                    else if (var_id.type == dataTypes.Byte()) {
                        scope[env_index].matrixes[mx_index]._fields_byte[fld_index].set(ele_index,IMPEntityByte(clc.calcByteEntity(nodes.childs[1])));
                    }
                    else if (var_id.type == dataTypes.Word()) {
                        scope[env_index].matrixes[mx_index]._fields_word[fld_index].set(ele_index,IMPEntityWord(clc.calcWordEntity(nodes.childs[1])));
                    }
                    else if (var_id.type == dataTypes.DWord()) {
                        scope[env_index].matrixes[mx_index]._fields_dword[fld_index].set(ele_index,IMPEntityDWord(clc.calcDWordEntity(nodes.childs[1])));
                    }
                    else if (var_id.type == dataTypes.Float()) {
                        scope[env_index].matrixes[mx_index]._fields_float[fld_index].set(ele_index,IMPEntityFloat(clc.calcFloatEntity(nodes.childs[1])));
                    }
                    else if (var_id.type == dataTypes.Char()) {
                        scope[env_index].matrixes[mx_index]._fields_char[fld_index].set(ele_index,IMPEntityChar(clc.calcCharEntity(nodes.childs[1])));
                    }
                    else if (var_id.type == dataTypes.Bool()) {
                        scope[env_index].matrixes[mx_index]._fields_bool[fld_index].set(ele_index,IMPEntityBool(clc.calcBoolEntity(nodes.childs[1])));
                    }
                    for (imperr::message msg : clc.errors) errors.push_back(msg);
                }
                else if (env.findId(nodes.childs[0].childs[0].childs[0].value.text)!=nfind) {
                    int mx_index = env.findId(nodes.childs[0].childs[0].childs[0].value.text);
                    int fld_index = env.matrixes[mx_index].findId(nodes.childs[0].childs[1].value.text);
                    Calc clc(fake_scope);
                    int ele_index = clc.calcIntEntity(nodes.childs[0].childs[0].childs[1]);
                    IMPID var_id = env.matrixes[mx_index]._idents[fld_index];
                    if (var_id.type == dataTypes.Func()) {
                        errors.push_back(imperr::message(imperr::exe::cant_assign_a_value_to_func,"You cant assign a value to function",nodes.childs[0].childs[0].childs[1].value.text,nodes.childs[0].childs[0].childs[1].value.row,nodes.childs[0].childs[0].childs[1].value.col));
                        return;
                    }
                    if (var_id.type == dataTypes.Int()) {
                        env.matrixes[mx_index]._fields_int[fld_index].set(ele_index,IMPEntityInt(clc.calcIntEntity(nodes.childs[1])));
                    }
                    else if (var_id.type == dataTypes.Byte()) {
                        env.matrixes[mx_index]._fields_byte[fld_index].set(ele_index,IMPEntityByte(clc.calcByteEntity(nodes.childs[1])));
                    }
                    else if (var_id.type == dataTypes.Word()) {
                        env.matrixes[mx_index]._fields_word[fld_index].set(ele_index,IMPEntityWord(clc.calcWordEntity(nodes.childs[1])));
                    }
                    else if (var_id.type == dataTypes.DWord()) {
                        env.matrixes[mx_index]._fields_dword[fld_index].set(ele_index,IMPEntityDWord(clc.calcDWordEntity(nodes.childs[1])));
                    }
                    else if (var_id.type == dataTypes.Float()) {
                        env.matrixes[mx_index]._fields_float[fld_index].set(ele_index,IMPEntityFloat(clc.calcFloatEntity(nodes.childs[1])));
                    }
                    else if (var_id.type == dataTypes.Char()) {
                        env.matrixes[mx_index]._fields_char[fld_index].set(ele_index,IMPEntityChar(clc.calcCharEntity(nodes.childs[1])));
                    }
                    else if (var_id.type == dataTypes.Bool()) {
                        env.matrixes[mx_index]._fields_bool[fld_index].set(ele_index,IMPEntityBool(clc.calcBoolEntity(nodes.childs[1])));
                    }
                    for (imperr::message msg : clc.errors) errors.push_back(msg);
                }
                else {
                    errors.push_back(imperr::message(imperr::build::unknown_definition,"Unknown definiton",nodes.childs[0].value.text,nodes.childs[0].value.row,nodes.childs[0].value.col));
                }
                return;
            }
            if (nodes.childs[0].value.type != tokenTypes.Ident()) {
                errors.push_back(imperr::message(imperr::build::unexpected,"Unexpected",nodes.childs[0].value.text,nodes.childs[0].value.row,nodes.childs[0].value.col));
                return;
            }
            if (findId(nodes.childs[0].value.text,scope)!=nfind) {
                int env_index = findId(nodes.childs[0].value.text,scope);
                int var_index = scope[env_index].findId(nodes.childs[0].value.text);
                Calc clc(fake_scope);
                IMPID var_id = scope[env_index].idents[var_index];
                if (var_id.type == dataTypes.Int()) {
                    scope[env_index].int_ents[var_index] = IMPEntityInt(clc.calcIntEntity(nodes.childs[1]));
                }
                else if (var_id.type == dataTypes.Byte()) {
                    scope[env_index].byte_ents[var_index] = IMPEntityByte(clc.calcByteEntity(nodes.childs[1]));
                }
                else if (var_id.type == dataTypes.Word()) {
                    scope[env_index].word_ents[var_index] = IMPEntityWord(clc.calcWordEntity(nodes.childs[1]));
                }
                else if (var_id.type == dataTypes.DWord()) {
                    scope[env_index].dword_ents[var_index] = IMPEntityDWord(clc.calcDWordEntity(nodes.childs[1]));
                }
                else if (var_id.type == dataTypes.Float()) {
                    scope[env_index].float_ents[var_index] = IMPEntityFloat(clc.calcFloatEntity(nodes.childs[1]));
                }
                else if (var_id.type == dataTypes.Char()) {
                    scope[env_index].char_ents[var_index] = IMPEntityChar(clc.calcCharEntity(nodes.childs[1]));
                }
                else if (var_id.type == dataTypes.Bool()) {
                    scope[env_index].bool_ents[var_index] = IMPEntityBool(clc.calcBoolEntity(nodes.childs[1]));
                }
                for (imperr::message msg : clc.errors) errors.push_back(msg);
            }
            else if (env.findId(nodes.childs[0].value.text)!=nfind) {
                int var_index = env.findId(nodes.childs[0].value.text);
                Calc clc(fake_scope);
                IMPID var_id = env.idents[var_index];
                if (var_id.type == dataTypes.Int()) {
                    env.int_ents[var_index] = IMPEntityInt(clc.calcIntEntity(nodes.childs[1]));
                }
                else if (var_id.type == dataTypes.Byte()) {
                    env.byte_ents[var_index] = IMPEntityByte(clc.calcByteEntity(nodes.childs[1]));
                }
                else if (var_id.type == dataTypes.Word()) {
                    env.word_ents[var_index] = IMPEntityWord(clc.calcWordEntity(nodes.childs[1]));
                }
                else if (var_id.type == dataTypes.DWord()) {
                    env.dword_ents[var_index] = IMPEntityDWord(clc.calcDWordEntity(nodes.childs[1]));
                }
                else if (var_id.type == dataTypes.Float()) {
                    env.float_ents[var_index] = IMPEntityFloat(clc.calcFloatEntity(nodes.childs[1]));
                }
                else if (var_id.type == dataTypes.Char()) {
                    env.char_ents[var_index] = IMPEntityChar(clc.calcCharEntity(nodes.childs[1]));
                }
                else if (var_id.type == dataTypes.Bool()) {
                    env.bool_ents[var_index] = IMPEntityBool(clc.calcBoolEntity(nodes.childs[1]));
                }
                for (imperr::message msg : clc.errors) errors.push_back(msg);
            }
            else {
                errors.push_back(imperr::message(imperr::build::unknown_definition,"Unknown definiton",nodes.childs[0].value.text,nodes.childs[0].value.row,nodes.childs[0].value.col));
            }
        }
    }

    void buildProcDefinition(IMPEnv& env, std::vector<IMPEnv> scope, IMPAstNode nodes) {
        int ident_i = 0;
        IMPDataType ptype(dataTypes.Void());
        if (nodes.childs[1].value.type == tokenTypes.Ident()) {
            ptype = dataTypes.get(nodes.childs[0].value.type);
            ident_i = 1;
        }
        IMPID pid(dataTypes.Proc(),nodes.childs[ident_i].value.text);
        std::vector<IMPID> fargs;
        int instructions_begin = 0;
        for (int i = ident_i+2; i < nodes.childs.size(); i++) {
            if (nodes.childs[i].value.type != tokenTypes.BrClCircle()) {
                fargs.push_back(IMPID(dataTypes.get(nodes.childs[i].value.type),nodes.childs[i].childs[0].value.text));
            }
            else {
                instructions_begin = i+2;
                break;
            }
        }
        std::vector<IMPAstNode> ops;
        for (int i = instructions_begin; i < nodes.childs.size(); i++) {
            ops.push_back(nodes.childs[i]);
        }
        IMPProc prc(ptype,ops);
        prc.args = fargs;
        env.proc[env.idents.size()] = prc;
        env.idents.push_back(pid);
    }

    void buildFuncDefinition(IMPMatrix& mx, bool hide_enable, std::vector<IMPEnv> scope, IMPAstNode nodes) {
        IMPID fid(dataTypes.Func(),nodes.childs[1].value.text);
        std::vector<IMPID> fargs;
        int ret_i = 0;
        for (int i = 3; i < nodes.childs.size(); i++) {
            if (nodes.childs[i].value.type != tokenTypes.BrClCircle()) {
                fargs.push_back(IMPID(dataTypes.get(nodes.childs[i].value.type),nodes.childs[i].childs[0].value.text));
            }
            else {
                ret_i = i+1;
                break;
            }
        }
        IMPAstNode ret_expr = nodes.childs[ret_i].childs[0];
        mx.add_func(fid,dataTypes.get(nodes.childs[0].value.type),fargs,ret_expr,hide_enable);
        mx._funcs[mx._idents.size()-1].lscope = mx._idents;
    }

    void buildMatrixDefinition(IMPEnv& env, std::vector<IMPEnv> scope, IMPAstNode nodes) {
        if (nodes.childs[0].value.type == tokenTypes.Ident()) {
            if (findId(nodes.childs[0].value.text,scope)==nfind) {
                int mxsize = 0;
                std::vector<IMPEnv> tmp_sc = scope;
                tmp_sc.push_back(env);
                Calc iclc(tmp_sc);
                if (nodes.childs[2].value.type != tokenTypes.BrClSquare()) mxsize = iclc.calcIntEntity(nodes.childs[2]);
                IMPMatrix out_mx(mxsize);
                int begin_lscope = 0;
                if (nodes.childs[3].value.type == tokenTypes.BrOpCurly()) begin_lscope = 4;
                if (nodes.childs[4].value.type == tokenTypes.BrOpCurly()) begin_lscope = 5;
                std::vector<std::string> lscope;
                bool next_hide = false;
                for (int i = begin_lscope; i < nodes.childs.size(); i++) {
                    if (nodes.childs[i].value.type == tokenTypes.BrClCurly()) break;
                    else if (nodes.childs[i].value.type == std::vector<IMPTokenType>{tokenTypes.KwInt(),tokenTypes.KwByte(),tokenTypes.KwWord(),tokenTypes.KwDWord(),tokenTypes.KwFloat(),tokenTypes.KwChar(),tokenTypes.KwBool()}) {
                        for (std::string l : lscope) {
                            if (l == nodes.childs[i].childs[0].value.text) {
                                errors.push_back(imperr::message(imperr::build::overdefined_ident,"Overdefined id",nodes.childs[i].value.text,nodes.childs[i].value.row,nodes.childs[i].value.col));
                                return;
                            }
                        }
                        out_mx.add_field(IMPID(dataTypes.get(nodes.childs[i].value.type),nodes.childs[i].childs[0].value.text),next_hide);
                        lscope.push_back(nodes.childs[i].childs[0].value.text);
                        next_hide = false;
                    }
                    else if (nodes.childs[i].value.type == tokenTypes.KwFunc()) {
                        for (std::string l : lscope) {
                            if (l == nodes.childs[i].childs[1].value.text) {
                                errors.push_back(imperr::message(imperr::build::overdefined_ident,"Overdefined id",nodes.childs[i].value.text,nodes.childs[i].value.row,nodes.childs[i].value.col));
                                return;
                            }
                        }
                        buildFuncDefinition(out_mx,next_hide,scope,nodes.childs[i]);
                        next_hide = false;
                    }
                    else if (nodes.childs[i].value.type == tokenTypes.KwHide()) {
                        next_hide=true;
                    }
                }
                env.matrixes[env.idents.size()] = out_mx;
                env.idents.push_back(IMPID(dataTypes.Mx(),nodes.childs[0].value.text));
            }
            else {
                errors.push_back(imperr::message(imperr::build::overdefined_ident,"Overdefined id",nodes.childs[0].value.text,nodes.childs[0].value.row,nodes.childs[0].value.col));
            }
        }
    }

    void buildVarDefinition(IMPEnv& env, std::vector<IMPEnv> scope, IMPAstNode nodes) {
        if (nodes.childs.size()==0) {
            errors.push_back(imperr::message(imperr::build::definition_error,"Definition error",nodes.value.text,nodes.value.row,nodes.value.col));
            return;
        }
        
        if (nodes.childs[0].value.type == tokenTypes.Ident()) {
            if (findId(nodes.childs[0].value.text,scope)==nfind) {
                if (nodes.value.type == tokenTypes.KwInt()) {
                    env.int_ents[env.idents.size()] = IMPEntityInt(0);
                    env.idents.push_back(IMPID(dataTypes.Int(),nodes.childs[0].value.text));
                }
                else if (nodes.value.type == tokenTypes.KwByte()) {
                    env.byte_ents[env.idents.size()] = IMPEntityByte(0);
                    env.idents.push_back(IMPID(dataTypes.Byte(),nodes.childs[0].value.text));
                }
                else if (nodes.value.type == tokenTypes.KwWord()) {
                    env.word_ents[env.idents.size()] = IMPEntityWord(0);
                    env.idents.push_back(IMPID(dataTypes.Word(),nodes.childs[0].value.text));
                }
                else if (nodes.value.type == tokenTypes.KwDWord()) {
                    env.dword_ents[env.idents.size()] = IMPEntityDWord(0);
                    env.idents.push_back(IMPID(dataTypes.DWord(),nodes.childs[0].value.text));
                }
                else if (nodes.value.type == tokenTypes.KwFloat()) {
                    env.float_ents[env.idents.size()] = IMPEntityFloat(0);
                    env.idents.push_back(IMPID(dataTypes.Float(),nodes.childs[0].value.text));
                }
                else if (nodes.value.type == tokenTypes.KwChar()) {
                    env.char_ents[env.idents.size()] = IMPEntityChar("");
                    env.idents.push_back(IMPID(dataTypes.Char(),nodes.childs[0].value.text));
                }
                else if (nodes.value.type == tokenTypes.KwBool()) {
                    env.bool_ents[env.idents.size()] = IMPEntityBool(false);
                    env.idents.push_back(IMPID(dataTypes.Bool(),nodes.childs[0].value.text));
                }
            }
            else {
                errors.push_back(imperr::message(imperr::build::overdefined_ident,"Overdefined id",nodes.value.text,nodes.value.row,nodes.value.col));
            }
        }
        else if (nodes.childs[0].value.type == tokenTypes.Assign()) {
            if (nodes.childs[0].childs[0].value.type != tokenTypes.Ident()) {
                errors.push_back(imperr::message(imperr::build::unexpected,"Unexpected",nodes.childs[0].childs[0].value.text,nodes.childs[0].childs[0].value.row,nodes.childs[0].childs[0].value.col));
                return;
            }
            if (findId(nodes.childs[0].childs[0].value.text,scope)==nfind) {
                Calc clc(scope);
                if (nodes.value.type == tokenTypes.KwInt()) {
                    env.int_ents[env.idents.size()] = IMPEntityInt(clc.calcIntEntity(nodes.childs[0].childs[1]));
                    env.idents.push_back(IMPID(dataTypes.Int(),nodes.childs[0].childs[0].value.text));
                }
                else if (nodes.value.type == tokenTypes.KwByte()) {
                    env.byte_ents[env.idents.size()] = IMPEntityByte(clc.calcByteEntity(nodes.childs[0].childs[1]));
                    env.idents.push_back(IMPID(dataTypes.Byte(),nodes.childs[0].childs[0].value.text));
                }
                else if (nodes.value.type == tokenTypes.KwWord()) {
                    env.word_ents[env.idents.size()] = IMPEntityWord(clc.calcWordEntity(nodes.childs[0].childs[1]));
                    env.idents.push_back(IMPID(dataTypes.Word(),nodes.childs[0].childs[0].value.text));
                }
                else if (nodes.value.type == tokenTypes.KwDWord()) {
                    env.dword_ents[env.idents.size()] = IMPEntityDWord(clc.calcDWordEntity(nodes.childs[0].childs[1]));
                    env.idents.push_back(IMPID(dataTypes.DWord(),nodes.childs[0].childs[0].value.text));
                }
                else if (nodes.value.type == tokenTypes.KwFloat()) {
                    env.float_ents[env.idents.size()] = IMPEntityFloat(clc.calcFloatEntity(nodes.childs[0].childs[1]));
                    env.idents.push_back(IMPID(dataTypes.Float(),nodes.childs[0].childs[0].value.text));
                }
                else if (nodes.value.type == tokenTypes.KwChar()) {
                    env.char_ents[env.idents.size()] = IMPEntityChar(clc.calcCharEntity(nodes.childs[0].childs[1]));
                    env.idents.push_back(IMPID(dataTypes.Char(),nodes.childs[0].childs[0].value.text));
                }
                else if (nodes.value.type == tokenTypes.KwBool()) {
                    env.bool_ents[env.idents.size()] = IMPEntityBool(clc.calcBoolEntity(nodes.childs[0].childs[1]));
                    env.idents.push_back(IMPID(dataTypes.Bool(),nodes.childs[0].childs[0].value.text));
                }
                for (imperr::message msg : clc.errors) errors.push_back(msg);
            }
            else {
                errors.push_back(imperr::message(imperr::build::overdefined_ident,"Overdefined id",nodes.value.text,nodes.value.row,nodes.value.col));
            }
        }
    }

    void buildEnv(SrcNode& out, IMPAstNode env_node) {
        IMPEnv out_env(env_node.childs[0].value.text);
        if (env_node.childs[1].value.type != tokenTypes.BrOpCurly()) {
            errors.push_back(imperr::message(imperr::build::unexpected,"Unexpected",env_node.childs[1].value.text,env_node.childs[1].value.row,env_node.childs[1].value.col));
            return;
        }
        std::vector<IMPEnv> false_scope = out.envs;
        for (int i = 2; i < env_node.childs.size(); i++) {
            false_scope.push_back(out_env);
            if (env_node.childs[i].value.type == std::vector<IMPTokenType>{tokenTypes.KwInt(),tokenTypes.KwByte(),tokenTypes.KwWord(),tokenTypes.KwDWord(),tokenTypes.KwFloat(),tokenTypes.KwChar(),tokenTypes.KwBool()}) {
                buildVarDefinition(out_env,false_scope,env_node.childs[i]);
            }
            else if (env_node.childs[i].value.type == tokenTypes.KwMx()) {
                buildMatrixDefinition(out_env,false_scope,env_node.childs[i]);
            }
            else if (env_node.childs[i].value.type == tokenTypes.KwProc()) {
                buildProcDefinition(out_env,false_scope,env_node.childs[i]);
            }
            false_scope.pop_back();
        }
        out.envs.push_back(out_env);
    }

    SrcNode linkNode(archivarius::file export_file) {
        SrcNode out_node(export_file);
        out_node.code=out_node.file.read();
        if (out_node.file.geterr().code()!=imperr::file::all_ok) {
            errors.push_back(out_node.file.geterr());
            return out_node;
        }
        IMPLexer lexer(out_node.code,out_node.file.fpath());
        lexer.lex();
        for (imperr::message msg : lexer.errors) errors.push_back(msg);
        for (IMPToken token : lexer.tokens) {
            _show_lexer_out += token.type.name + (token.type.name.size()<8?"\t":"") + "\t" + (token.text.size()<8?token.text:token.text.substr(0,5)+"~"+token.text.back())
                + "\t" + std::to_string(token.row) + "\t" + std::to_string(token.col) + "\n";
        }
        if (lexer.errors.size() > 0) return out_node;
        IMPParser parser(lexer.tokens,out_node.file.fpath());
        parser.parse();
        for (imperr::message msg : parser.errors) errors.push_back(msg);
        for (IMPAstNode node : parser.nodes) {
            out_node.nodes.push_back(node);
            _show_parser_out += node.show() + "\n";
        }
        if (parser.errors.size() > 0) return out_node;
        for (std::string req_file : parser.required_files) {
            if (!always_included((export_file.path()!="" ? export_file.path()+"/" : "")+req_file,files)) {
                out_node.include.push_back(linkNode(archivarius::file((export_file.path()!="" ? export_file.path()+"/" : "")+req_file)));
                //for (archivarius::file c : out_node.include.back().contents) {
                //    if (!out_node.always_included(c.fpath())) out_node.contents.push_back(c.fpath());
                //}
                //for (archivarius::file c : files) {
                //    if (!out_node.always_included(c.fpath())) files.push_back(c.fpath());
                //}
                files.push_back((export_file.path()!="" ? export_file.path()+"/" : "")+req_file);
                for (IMPEnv i : out_node.include.back().envs) {
                    out_node.envs.push_back(i);
                }
            }
        }

        for (IMPAstNode n : out_node.nodes) {
            if (n.value.type == tokenTypes.KwEnv()) {
                buildEnv(out_node,n);
            }
        }

        return out_node;
    }

    void update_buttons_triggers(std::vector<std::string> trg, std::vector<bool> ttt) {
        for (int i = 0; i < trg.size(); i++) {
            for (int j = 0; j < src.envs.size(); j++) {
                int ti = src.envs[j].findId(trg[i]);
                if (src.envs[j].idents[ti].type == dataTypes.Bool()) {
                    src.envs[j].bool_ents[ti].set(ttt[i]);
                }
            }
        }
    }

    std::vector<std::string> update_indicators_triggers(std::vector<std::string> trg) {
        std::vector<std::string> out;
        for (int i = 0; i < trg.size(); i++) {
            for (int j = 0; j < src.envs.size(); j++) {
                int ti = src.envs[j].findId(trg[i]);
                if (src.envs[j].idents[ti].type == dataTypes.Bool()) {
                    if (src.envs[j].bool_ents[ti].get()) {
                        out.push_back(trg[i]);
                        break;
                    }
                }
            }
        }
        return out;
    }

    void update_sensors(std::vector<short> data) {
        for (int i = 0; i < data.size(); i++) {
            for (int j = 0; j < src.envs.size(); j++) {
                int ti = src.envs[j].findId("T"+std::to_string(i+1));
                if (src.envs[j].idents[ti].type == dataTypes.Int()) {
                    src.envs[j].int_ents[ti].set(data[i]);
                }
            }
        }
    }

    int build(std::string filename) {
        errors.clear();

        src=linkNode(filename);

        _exe_code = errors.size();
        return _exe_code;
    }

    std::string show_lexer_out()  { return _show_lexer_out; }
    std::string show_parser_out() { return _show_parser_out; }
    std::string show_errors() {
        std::string _show_errors = "";
        _show_errors += "\nERRORS: " + std::to_string(errors.size()) + "\n";
        for (imperr::message msg : errors) {
            _show_errors += msg.show() + "\n";
        }
        return _show_errors;
    }

    std::string show_file_system() {
        return src.show();
    }

    int get_exe_code() { return _exe_code; }
    
};

#endif //IMP_EXECUTRIX_H
