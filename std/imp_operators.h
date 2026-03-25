#ifndef IMP_OPERATORS_H
#define IMP_OPERATORS_H

#include<stdint.h>
#include<vector>
#include<cmath>

#include"../types/imp_error.h"
#include"../parser/imp_nodes.h"
#include"../executrix.h"

class Calc {
private:
    DataTypes dataTypes;
    TokenTypes tokenTypes;
public:
    Calc(std::vector<IMPEnv> id_scope) : scope(id_scope) {}
    ~Calc() {}

    std::vector<imperr::message> errors;
    std::vector<IMPEnv> scope;

    bool cant_calc() {
        return errors.size()>0;
    }

    int callIntFromMatrix(IMPAstNode n) {
        if (n.childs[0].value.type == tokenTypes.OP_Index()) {
            IMPAstNode indexing = n.childs[0];
            int envi = findId(indexing.childs[0].value.text,scope);
            if (envi != nfind) {
                int mxi = scope[envi].findId(indexing.childs[0].value.text);
                if (scope[envi].idents[mxi].type == dataTypes.Mx()) {
                    int idx = calcIntEntity(indexing.childs[1]);
                    int fii = scope[envi].matrixes[mxi].findId(n.childs[1].value.text);
                    if (fii != nfind) {
                        IMPDataType dt = scope[envi].matrixes[mxi]._idents[fii].type;
                        if (dt == dataTypes.Int()) {
                            return scope[envi].matrixes[mxi]._fields_int[fii].get(idx);
                        }
                        else if (dt == dataTypes.Byte()) {
                            return scope[envi].matrixes[mxi]._fields_byte[fii].get(idx);
                        }
                        else if (dt == dataTypes.Word()) {
                            return scope[envi].matrixes[mxi]._fields_word[fii].get(idx);
                        }
                        else if (dt == dataTypes.DWord()) {
                            return scope[envi].matrixes[mxi]._fields_dword[fii].get(idx);
                        }
                        else if (dt == dataTypes.Float()) {
                            return scope[envi].matrixes[mxi]._fields_float[fii].get(idx);
                        }
                        else {
                            //error
                        }
                    }
                    else {
                        //error
                    }
                }
                else {
                    //error
                }
            }
            else {
                //error
            }
        }
        //error
        return 0;
    }

    uint32_t callDWordFromMatrix(IMPAstNode n) {
        if (n.childs[0].value.type == tokenTypes.OP_Index()) {
            IMPAstNode indexing = n.childs[0];
            int envi = findId(indexing.childs[0].value.text,scope);
            if (envi != nfind) {
                int mxi = scope[envi].findId(indexing.childs[0].value.text);
                if (scope[envi].idents[mxi].type == dataTypes.Mx()) {
                    int idx = calcIntEntity(indexing.childs[1]);
                    int fii = scope[envi].matrixes[mxi].findId(n.childs[1].value.text);
                    if (fii != nfind) {
                        IMPDataType dt = scope[envi].matrixes[mxi]._idents[fii].type;
                        if (dt == dataTypes.Int()) {
                            return scope[envi].matrixes[mxi]._fields_int[fii].get(idx);
                        }
                        else if (dt == dataTypes.Byte()) {
                            return scope[envi].matrixes[mxi]._fields_byte[fii].get(idx);
                        }
                        else if (dt == dataTypes.Word()) {
                            return scope[envi].matrixes[mxi]._fields_word[fii].get(idx);
                        }
                        else if (dt == dataTypes.DWord()) {
                            return scope[envi].matrixes[mxi]._fields_dword[fii].get(idx);
                        }
                        else if (dt == dataTypes.Float()) {
                            return scope[envi].matrixes[mxi]._fields_float[fii].get(idx);
                        }
                        else {
                            //error
                        }
                    }
                    else {
                        //error
                    }
                }
                else {
                    //error
                }
            }
            else {
                //error
            }
        }
        //error
        return 0;
    }

    double callFloatFromMatrix(IMPAstNode n) {
        if (n.childs[0].value.type == tokenTypes.OP_Index()) {
            IMPAstNode indexing = n.childs[0];
            int envi = findId(indexing.childs[0].value.text,scope);
            if (envi != nfind) {
                int mxi = scope[envi].findId(indexing.childs[0].value.text);
                if (scope[envi].idents[mxi].type == dataTypes.Mx()) {
                    int idx = calcIntEntity(indexing.childs[1]);
                    int fii = scope[envi].matrixes[mxi].findId(n.childs[1].value.text);
                    if (fii != nfind) {
                        IMPDataType dt = scope[envi].matrixes[mxi]._idents[fii].type;
                        if (dt == dataTypes.Int()) {
                            return scope[envi].matrixes[mxi]._fields_int[fii].get(idx);
                        }
                        else if (dt == dataTypes.Byte()) {
                            return scope[envi].matrixes[mxi]._fields_byte[fii].get(idx);
                        }
                        else if (dt == dataTypes.Word()) {
                            return scope[envi].matrixes[mxi]._fields_word[fii].get(idx);
                        }
                        else if (dt == dataTypes.DWord()) {
                            return scope[envi].matrixes[mxi]._fields_dword[fii].get(idx);
                        }
                        else if (dt == dataTypes.Float()) {
                            return scope[envi].matrixes[mxi]._fields_float[fii].get(idx);
                        }
                        else {
                            //error
                        }
                    }
                    else {
                        //error
                    }
                }
                else {
                    //error
                }
            }
            else {
                //error
            }
        }
        //error
        return 0;
    }

    std::string callCharFromMatrix(IMPAstNode n) {
        if (n.childs[0].value.type == tokenTypes.OP_Index()) {
            IMPAstNode indexing = n.childs[0];
            int envi = findId(indexing.childs[0].value.text,scope);
            if (envi != nfind) {
                int mxi = scope[envi].findId(indexing.childs[0].value.text);
                if (scope[envi].idents[mxi].type == dataTypes.Mx()) {
                    int idx = calcIntEntity(indexing.childs[1]);
                    int fii = scope[envi].matrixes[mxi].findId(n.childs[1].value.text);
                    if (fii != nfind) {
                        IMPDataType dt = scope[envi].matrixes[mxi]._idents[fii].type;
                        if (dt == dataTypes.Char()) {
                            return scope[envi].matrixes[mxi]._fields_char[fii].get(idx);
                        }
                        else {
                            //error
                        }
                    }
                    else {
                        //error
                    }
                }
                else {
                    //error
                }
            }
            else {
                //error
            }
        }
        //error
        return 0;
    }

    bool callBoolFromMatrix(IMPAstNode n) {
        if (n.childs[0].value.type == tokenTypes.OP_Index()) {
            IMPAstNode indexing = n.childs[0];
            int envi = findId(indexing.childs[0].value.text,scope);
            if (envi != nfind) {
                int mxi = scope[envi].findId(indexing.childs[0].value.text);
                if (scope[envi].idents[mxi].type == dataTypes.Mx()) {
                    int idx = calcIntEntity(indexing.childs[1]);
                    int fii = scope[envi].matrixes[mxi].findId(n.childs[1].value.text);
                    if (fii != nfind) {
                        IMPDataType dt = scope[envi].matrixes[mxi]._idents[fii].type;
                        if (dt == dataTypes.Bool()) {
                            return scope[envi].matrixes[mxi]._fields_bool[fii].get(idx);
                        }
                        else {
                            //error
                        }
                    }
                    else {
                        //error
                    }
                }
                else {
                    //error
                }
            }
            else {
                //error
            }
        }
        //error
        return 0;
    }

    int callIntVar(IMPAstNode n) {
        int env_index = findId(n.value.text,scope);
        if (env_index != nfind) {
            int var_index = scope[env_index].findId(n.value.text);
            IMPID id = scope[env_index].idents[var_index];
            if (id.type == dataTypes.Int()) {
                return scope[env_index].int_ents[var_index].get();
            }
            else if (id.type == dataTypes.Byte()) {
                return scope[env_index].byte_ents[var_index].get();
            }
            else if (id.type == dataTypes.Word()) {
                return scope[env_index].word_ents[var_index].get();
            }
            else if (id.type == dataTypes.DWord()) {
                return scope[env_index].dword_ents[var_index].get();
            }
            else {
                errors.push_back(imperr::message(imperr::build::unsuitable_datatype,"Unsuitable datatype",scope[env_index].idents[var_index].type.name + scope[env_index].idents[var_index].name,n.value.row,n.value.col));
                return 0;
            }
        }
        else {
            errors.push_back(imperr::message(imperr::build::unknown_definition,"Unknown definition",n.value.text,n.value.row,n.value.col));
            return 0;
        }
    }

    double callFloatVar(IMPAstNode n) {
        int env_index = findId(n.value.text,scope);
        if (env_index != nfind) {
            int var_index = scope[env_index].findId(n.value.text);
            IMPID id = scope[env_index].idents[var_index];
            if (id.type == dataTypes.Int()) {
                return scope[env_index].int_ents[var_index].get();
            }
            else if (id.type == dataTypes.Float()) {
                return scope[env_index].float_ents[var_index].get();
            }
            else if (id.type == dataTypes.Byte()) {
                return scope[env_index].byte_ents[var_index].get();
            }
            else if (id.type == dataTypes.Word()) {
                return scope[env_index].word_ents[var_index].get();
            }
            else if (id.type == dataTypes.DWord()) {
                return scope[env_index].dword_ents[var_index].get();
            }
            else {
                errors.push_back(imperr::message(imperr::build::unsuitable_datatype,"Unsuitable datatype",scope[env_index].idents[var_index].type.name + scope[env_index].idents[var_index].name,n.value.row,n.value.col));
                return 0;
            }
        }
        else {
            errors.push_back(imperr::message(imperr::build::unknown_definition,"Unknown definition",n.value.text,n.value.row,n.value.col));
            return 0;
        }
    }

    IMPDataType getVarType(std::string name) {
        int index = findId(name,scope);
        if (index != nfind) {
            int i = scope[index].findId(name);
            return scope[index].idents[i].type;
        }
        return dataTypes.Null();
    }

    std::string callCharVar(IMPAstNode n) {
        int env_index = findId(n.value.text,scope);
        if (env_index != nfind) {
            int var_index = scope[env_index].findId(n.value.text);
            IMPID id = scope[env_index].idents[var_index];
            if (id.type == dataTypes.Int()) {
                return std::to_string(scope[env_index].int_ents[var_index].get());
            }
            else if (id.type == dataTypes.Float()) {
                return std::to_string(scope[env_index].float_ents[var_index].get());
            }
            else if (id.type == dataTypes.Byte()) {
                return std::to_string(scope[env_index].byte_ents[var_index].get());
            }
            else if (id.type == dataTypes.Word()) {
                return std::to_string(scope[env_index].word_ents[var_index].get());
            }
            else if (id.type == dataTypes.DWord()) {
                return std::to_string(scope[env_index].dword_ents[var_index].get());
            }
            else if (id.type == dataTypes.Char()) {
                return scope[env_index].char_ents[var_index].get();
            }
            else {
                errors.push_back(imperr::message(imperr::build::unsuitable_datatype,"Unsuitable datatype",scope[env_index].idents[var_index].type.name + scope[env_index].idents[var_index].name,n.value.row,n.value.col));
                return "";
            }
        }
        else {
            errors.push_back(imperr::message(imperr::build::unknown_definition,"Unknown definition",n.value.text,n.value.row,n.value.col));
            return "";
        }
    }

    bool callBoolVar(IMPAstNode n) {
        int env_index = findId(n.value.text,scope);
        if (env_index != nfind) {
            int var_index = scope[env_index].findId(n.value.text);
            IMPID id = scope[env_index].idents[var_index];
            if (id.type == dataTypes.Bool()) {
                return scope[env_index].bool_ents[var_index].get();
            }
            else {
                errors.push_back(imperr::message(imperr::build::unsuitable_datatype,"Unsuitable datatype",scope[env_index].idents[var_index].type.name + scope[env_index].idents[var_index].name,n.value.row,n.value.col));
                return false;
            }
        }
        else {
            errors.push_back(imperr::message(imperr::build::unknown_definition,"Unknown definition",n.value.text,n.value.row,n.value.col));
            return false;
        }
    }

    int getMod(IMPAstNode n1, IMPAstNode n2)        { return calcIntEntity(n1)%calcIntEntity(n2); }
    double getPower(IMPAstNode n1, IMPAstNode n2)   { return std::pow(calcFloatEntity(n1),calcFloatEntity(n2)); }
    double getMult(IMPAstNode n1, IMPAstNode n2)    { return calcFloatEntity(n1)*calcFloatEntity(n2); }
    double getDivide(IMPAstNode n1, IMPAstNode n2)  { return calcFloatEntity(n1)/calcFloatEntity(n2); }
    double getPlus(IMPAstNode n1, IMPAstNode n2)    { return calcFloatEntity(n1)+calcFloatEntity(n2); }
    double getMinus(IMPAstNode n1, IMPAstNode n2)   { return calcFloatEntity(n1)-calcFloatEntity(n2); }

    std::string getStrPlus(IMPAstNode n1, IMPAstNode n2) { return calcCharEntity(n1)+calcCharEntity(n2); }

    bool getEqual(IMPAstNode n1, IMPAstNode n2) {
        /*
            float   1
            char    2
            bool    0
        */
        int code1 = 0;
        int code2 = 0;
        if (n1.value.type == std::vector<IMPTokenType>{tokenTypes.Power(),tokenTypes.Mult(),tokenTypes.Divide(),tokenTypes.Plus(),tokenTypes.Minus(),tokenTypes.Decimal(),tokenTypes.Hexidec(),tokenTypes.Binary()}) code1=1;
        else if (isStringOperand(n1)) code1=2;
        else if (n1.value.type == tokenTypes.Ident()) {
            IMPDataType tt = getVarType(n1.value.text);
            if (tt != dataTypes.Null()) {
                if (tt == std::vector<IMPDataType>{dataTypes.Int(),dataTypes.Byte(),dataTypes.Word(),dataTypes.DWord(),dataTypes.Float()}) code1=1;
                else if (tt == dataTypes.Char()) code1=2;
            }
        }
        
        if (n1.value.type == std::vector<IMPTokenType>{tokenTypes.Power(),tokenTypes.Mult(),tokenTypes.Divide(),tokenTypes.Plus(),tokenTypes.Minus(),tokenTypes.Decimal(),tokenTypes.Hexidec(),tokenTypes.Binary()})code2=1;
        else if (isStringOperand(n2)) code2=2;
        else if (n1.value.type == tokenTypes.Ident()) {
            IMPDataType tt = getVarType(n1.value.text);
            if (tt != dataTypes.Null()) {
                if (tt == std::vector<IMPDataType>{dataTypes.Int(),dataTypes.Byte(),dataTypes.Word(),dataTypes.DWord(),dataTypes.Float()}) code2=1;
                else if (tt == dataTypes.Char()) code2=2;
            }
        }

        if (code1!=code2) {
            errors.push_back(imperr::message(imperr::build::incompatible_operands,"Incompatible operands",n1.value.type.name+"=="+n2.value.type.name,n1.value.row,n1.value.col));
            return false;
        }

        if (code1==1) return calcFloatEntity(n1)==calcFloatEntity(n2);
        if (code1==2) return calcCharEntity(n1)==calcCharEntity(n2);
        return calcBoolEntity(n1)==calcBoolEntity(n2);
    }

    bool isStringOperand(IMPAstNode n) {
        if (n.value.type == tokenTypes.String()) return true;
        for (IMPAstNode i : n.childs) {
            if (isStringOperand(i)) return true;
        }
        return false;
    }

    uint32_t getBitAnd(IMPAstNode n1, IMPAstNode n2) { return calcDWordEntity(n1)&calcDWordEntity(n2); };
    uint32_t getBitXor(IMPAstNode n1, IMPAstNode n2) { return calcDWordEntity(n1)^calcDWordEntity(n2); };
    uint32_t getBitOr(IMPAstNode n1, IMPAstNode n2)  { return calcDWordEntity(n1)|calcDWordEntity(n2); };
    uint32_t getBitShiftLeft(IMPAstNode n1, IMPAstNode n2)  { return calcDWordEntity(n1)<<calcDWordEntity(n2); };
    uint32_t getBitShiftRight(IMPAstNode n1, IMPAstNode n2) { return calcDWordEntity(n1)>>calcDWordEntity(n2); };

    double getDecimal(IMPAstNode n) { return std::stod(n.value.text); }
    uint8_t  getByteHexidec(IMPAstNode n) { return std::stoul("0x"+n.value.text,0,16); }
    uint16_t getWordHexidec(IMPAstNode n) { return std::stoul("0x"+n.value.text,0,16); }
    uint32_t getHexidec(IMPAstNode n) { return std::stoul("0x"+n.value.text,0,16); }
    uint8_t  getByteBinary(IMPAstNode n) { return std::stoul("0b"+n.value.text,0,2); }
    uint16_t getWordBinary(IMPAstNode n) { return std::stoul("0b"+n.value.text,0,2); }
    uint32_t getBinary(IMPAstNode n) { return std::stoul("0b"+n.value.text,0,2); }
    std::string getString(IMPAstNode n) {return n.value.text; }

    int calcIntEntity(IMPAstNode node) {
        if (node.value.type == tokenTypes.Decimal()) {
            return getDecimal(node);
        }
        else if (node.value.type == tokenTypes.Hexidec()) {
            return getHexidec(node);
        }
        else if (node.value.type == tokenTypes.Binary()) {
            return getBinary(node);
        }
        else if (node.value.type == tokenTypes.Power()) {
            return getPower(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Mult()) {
            return getMult(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Divide()) {
            return getDivide(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Mod()) {
            return getMod(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Plus()) {
            return getPlus(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Minus()) {
            return getMinus(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitAnd()) {
            return getBitAnd(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitXor()) {
            return getBitXor(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitOr()) {
            return getBitOr(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitShiftLeft()) {
            return getBitShiftLeft(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitShiftRight()) {
            return getBitShiftRight(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Ident()) {
            return callIntVar(node);
        }
        else if (node.value.type == tokenTypes.Colon()) {
            return callIntFromMatrix(node);
        }
        
        errors.push_back(imperr::message(imperr::build::unsuitable_datatype,"Unsuitable datatype",node.value.type.name,node.value.row,node.value.col));
        return 0;
    }

    double calcFloatEntity(IMPAstNode node) {
        if (node.value.type == tokenTypes.Decimal()) {
            return getDecimal(node);
        }
        else if (node.value.type == tokenTypes.Hexidec()) {
            return getHexidec(node);
        }
        else if (node.value.type == tokenTypes.Binary()) {
            return getBinary(node);
        }
        else if (node.value.type == tokenTypes.Power()) {
            return getPower(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Mult()) {
            return getMult(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Divide()) {
            return getDivide(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Mod()) {
            return getMod(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Plus()) {
            return getPlus(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Minus()) {
            return getMinus(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitAnd()) {
            return getBitAnd(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitXor()) {
            return getBitXor(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitOr()) {
            return getBitOr(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitShiftLeft()) {
            return getBitShiftLeft(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitShiftRight()) {
            return getBitShiftRight(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Ident()) {
            return callFloatVar(node);
        }
        else if (node.value.type == tokenTypes.Colon()) {
            return callFloatFromMatrix(node);
        }
        
        errors.push_back(imperr::message(imperr::build::unsuitable_datatype,"Unsuitable datatype",node.value.type.name,node.value.row,node.value.col));
        return 0;
    }

    std::string calcCharEntity(IMPAstNode node) {
        if (node.value.type == tokenTypes.String()) {
            return getString(node);
        }
        else if (node.value.type == tokenTypes.Decimal()) {
            return getString(node);
        }
        else if (node.value.type == tokenTypes.Plus()) {
            return getStrPlus(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Ident()) {
            return callCharVar(node);
        }
        else if (node.value.type == tokenTypes.Colon()) {
            return callCharFromMatrix(node);
        }

        errors.push_back(imperr::message(imperr::build::unsuitable_datatype,"Unsuitable datatype",node.value.type.name,node.value.row,node.value.col));
        return "";
    }

    bool calcBoolEntity(IMPAstNode node) {
        if (node.value.type == tokenTypes.KwTrue()) {
            return true;
        }
        else if (node.value.type == tokenTypes.KwFalse()) {
            return false;
        }
        else if (node.value.type == tokenTypes.Equal()) {
            return getEqual(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.NotEqual()) {
            return !getEqual(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Less()) {
            return calcFloatEntity(node.childs[0])<calcFloatEntity(node.childs[1]);
        }
        else if (node.value.type == tokenTypes.More()) {
            return calcFloatEntity(node.childs[0])>calcFloatEntity(node.childs[1]);
        }
        else if (node.value.type == tokenTypes.LessEqual()) {
            return calcFloatEntity(node.childs[0])<=calcFloatEntity(node.childs[1]);
        }
        else if (node.value.type == tokenTypes.MoreEqual()) {
            return calcFloatEntity(node.childs[0])>=calcFloatEntity(node.childs[1]);
        }
        else if (node.value.type == tokenTypes.And()) {
            return calcBoolEntity(node.childs[0]) and calcBoolEntity(node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Or()) {
            return calcBoolEntity(node.childs[0]) or calcBoolEntity(node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Xor()) {
            return calcBoolEntity(node.childs[0]) xor calcBoolEntity(node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Negative()) {
            return !calcBoolEntity(node.childs[0]);
        }
        else if (node.value.type == tokenTypes.Ident()) {
            return callBoolVar(node);
        }
        else if (node.value.type == tokenTypes.Colon()) {
            return callBoolFromMatrix(node);
        }

        errors.push_back(imperr::message(imperr::build::unsuitable_datatype,"Unsuitable datatype",node.value.type.name,node.value.row,node.value.col));
        return false;
    }

    uint8_t calcByteEntity(IMPAstNode node) {
        if (node.value.type == tokenTypes.Decimal()) {
            return getDecimal(node);
        }
        else if (node.value.type == tokenTypes.Hexidec()) {
            return getByteHexidec(node);
        }
        else if (node.value.type == tokenTypes.Binary()) {
            return getByteBinary(node);
        }
        else if (node.value.type == tokenTypes.Power()) {
            return getPower(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Mult()) {
            return getMult(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Divide()) {
            return getDivide(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Mod()) {
            return getMod(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Plus()) {
            return getPlus(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Minus()) {
            return getMinus(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitAnd()) {
            return getBitAnd(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitXor()) {
            return getBitXor(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitOr()) {
            return getBitOr(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitShiftLeft()) {
            return getBitShiftLeft(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitShiftRight()) {
            return getBitShiftRight(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Ident()) {
            return callFloatVar(node);
        }
        else if (node.value.type == tokenTypes.Colon()) {
            return callDWordFromMatrix(node);
        }

        errors.push_back(imperr::message(imperr::build::unsuitable_datatype,"Unsuitable datatype",node.value.type.name,node.value.row,node.value.col));
        return 0;
    }

    uint16_t calcWordEntity(IMPAstNode node) {
        if (node.value.type == tokenTypes.Decimal()) {
            return getDecimal(node);
        }
        else if (node.value.type == tokenTypes.Hexidec()) {
            return getWordHexidec(node);
        }
        else if (node.value.type == tokenTypes.Binary()) {
            return getWordBinary(node);
        }
        else if (node.value.type == tokenTypes.Power()) {
            return getPower(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Mult()) {
            return getMult(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Divide()) {
            return getDivide(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Mod()) {
            return getMod(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Plus()) {
            return getPlus(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Minus()) {
            return getMinus(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitAnd()) {
            return getBitAnd(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitXor()) {
            return getBitXor(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitOr()) {
            return getBitOr(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitShiftLeft()) {
            return getBitShiftLeft(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.BitShiftRight()) {
            return getBitShiftRight(node.childs[0],node.childs[1]);
        }
        else if (node.value.type == tokenTypes.Ident()) {
            return callFloatVar(node);
        }
        else if (node.value.type == tokenTypes.Colon()) {
            return callDWordFromMatrix(node);
        }

        errors.push_back(imperr::message(imperr::build::unsuitable_datatype,"Unsuitable datatype",node.value.type.name,node.value.row,node.value.col));
        return 0;
    }

    uint32_t calcDWordEntity(IMPAstNode node) {
        return calcIntEntity(node);
    }
};

#endif //IMP_OPERATORS_H
