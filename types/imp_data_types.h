#ifndef IMP_DATA_TYPES_H
#define IMP_DATA_TYPES_H

#include<vector>

#include"../lexer/imp_token.h"

#define nfind -1

class IMPDataType {
public:
    IMPDataType() : name("") {}
    IMPDataType(std::string type_name) : name(type_name) {}
    ~IMPDataType() {}

    std::string name;

    bool operator==(const IMPDataType& datatype) { return this->name==datatype.name; }
    bool operator==(const std::vector<IMPDataType>& datatype) {
        for (IMPDataType type : datatype) if (type.name == this->name) return true;
        return false;
    }
    bool operator!=(const IMPDataType& datatype) { return this->name!=datatype.name; }
};

class DataTypes {
private:
    TokenTypes tokenTypes;
public:
    std::vector<IMPDataType> types;
    DataTypes() {
        types.push_back(IMPDataType("NULL"));
        types.push_back(IMPDataType("VOID"));
        types.push_back(IMPDataType("INTEGER"));
        types.push_back(IMPDataType("BYTE"));
        types.push_back(IMPDataType("WORD"));
        types.push_back(IMPDataType("DWORD"));
        types.push_back(IMPDataType("FLOATING"));
        types.push_back(IMPDataType("CHARACTER"));
        types.push_back(IMPDataType("BOOLEAN"));
        types.push_back(IMPDataType("ENVIRONMENT"));
        types.push_back(IMPDataType("MATRIX"));
        types.push_back(IMPDataType("FUNCTION"));
        types.push_back(IMPDataType("PROCEDURE"));
    }
    ~DataTypes() {}

    IMPDataType Int()   { return IMPDataType("INTEGER"); }
    IMPDataType Byte()  { return IMPDataType("BYTE"); }
    IMPDataType Word()  { return IMPDataType("WORD"); }
    IMPDataType DWord() { return IMPDataType("DWORD"); }
    IMPDataType Float() { return IMPDataType("FLOATING"); }
    IMPDataType Char()  { return IMPDataType("CHARACTER"); }
    IMPDataType Bool()  { return IMPDataType("BOOLEAN"); }
    IMPDataType Env()   { return IMPDataType("ENVIRONMENT"); }
    IMPDataType Mx()    { return IMPDataType("MATRIX"); }
    IMPDataType Func()  { return IMPDataType("FUNCTION"); }
    IMPDataType Proc()  { return IMPDataType("PROCEDURE"); }
    IMPDataType Void()  { return IMPDataType("VOID"); }
    IMPDataType Null()  { return IMPDataType("NULL"); }

    IMPDataType get(IMPTokenType ttype) {
        if (ttype == tokenTypes.KwInt())        return Int();
        else if (ttype == tokenTypes.KwByte())  return Byte();
        else if (ttype == tokenTypes.KwWord())  return Word();
        else if (ttype == tokenTypes.KwDWord()) return DWord();
        else if (ttype == tokenTypes.KwFloat()) return Float();
        else if (ttype == tokenTypes.KwChar())  return Char();
        else if (ttype == tokenTypes.KwBool())  return Bool();
        else if (ttype == tokenTypes.KwEnv())   return Env();
        else if (ttype == tokenTypes.KwMx())    return Mx();
        else if (ttype == tokenTypes.KwFunc())  return Func();
        else if (ttype == tokenTypes.KwProc())  return Proc();
        else return Null();
    }
};

extern DataTypes dataTypes;

class IMPID {
public:
    IMPID(IMPDataType id_type, std::string id_name)
        : type(id_type), name(id_name), isHide(false) {}
    ~IMPID() {}
    
    IMPDataType type;
    std::string name;
    bool isHide;
};

#endif //IMP_DATA_TYPES_H
