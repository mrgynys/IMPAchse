#ifndef IMP_TOKEN_H
#define IMP_TOKEN_H

#include<vector>
#include<string>

#define NULL_TOKEN IMPTokenType()

bool returnFalse(std::string);

// IMP TOKEN TYPES

class IMPTokenType {
public:
    IMPTokenType() { name = ""; is = returnFalse; }
    IMPTokenType(std::string token_name, bool (*ident_func)(std::string)) {
        name = token_name;
        is = ident_func;
    }
    IMPTokenType(const IMPTokenType& imptt) {
        name = imptt.name;
        is = imptt.is;
    }
    ~IMPTokenType() {}

    std::string name;
    bool (*is)(std::string);

    bool operator==(const IMPTokenType& tokentype) { return this->name==tokentype.name; }
    bool operator==(const std::vector<IMPTokenType>& tokentype) {
        for (IMPTokenType type : tokentype) if (type.name == this->name) return true;
        return false;
    }
    bool operator!=(const IMPTokenType& tokentype) { return this->name!=tokentype.name; }
};

// IMP TOKEN

class IMPToken {
public:
    IMPToken(IMPTokenType token_type, std::string token_text, int rowpos, int colpos)
        : type(token_type),text(token_text),row(rowpos),col(colpos) {}
    ~IMPToken() {}

    IMPTokenType type;
    std::string text;
    int row;
    int col;
};

// TOKEN TYPE IDENTIFICATORS

bool isSpace(std::string word);
bool isDecimal(std::string word);
bool isHexidec(std::string word);
bool isBinary(std::string word);
bool isKwIf(std::string word);
bool isKwElif(std::string word);
bool isKwElse(std::string word);
bool isKwWhile(std::string word);
bool isKwInt(std::string word);
bool isKwByte(std::string word);
bool isKwWord(std::string word);
bool isKwDWord(std::string word);
bool isKwFloat(std::string word);
bool isKwChar(std::string word);
bool isKwBool(std::string word);
bool isKwHide(std::string word);
bool isKwMx(std::string word);
bool isKwEnv(std::string word);
bool isKwFunc(std::string word);
bool isKwProc(std::string word);
bool isKwReturn(std::string word);
bool isSWAdd(std::string word);
bool isKwTrue(std::string word);
bool isKwFalse(std::string word);
bool isBracketOpenCircle(std::string word);
bool isBracketCloseCircle(std::string word);
bool isBracketOpenSquare(std::string word);
bool isBracketCloseSquare(std::string word);
bool isBracketOpenCurly(std::string word);
bool isBracketCloseCurly(std::string word);
bool isComma(std::string word);
bool isColon(std::string word);
bool isSemicolon(std::string word);
bool isAssign(std::string word);
bool isPower(std::string word);
bool isMod(std::string word);
bool isMult(std::string word);
bool isDivide(std::string word);
bool isPlus(std::string word);
bool isMinus(std::string word);
bool isEqual(std::string word);
bool isNotEqual(std::string word);
bool isMoreOrE(std::string word);
bool isLessOrE(std::string word);
bool isMore(std::string word);
bool isLess(std::string word);
bool isNegative(std::string word);
bool isAnd(std::string word);
bool isOr(std::string word);
bool isXor(std::string word);
bool isBitAnd(std::string word);
bool isBitOr(std::string word);
bool isBitXor(std::string word);
bool isBitShiftLeft(std::string word);
bool isBitShiftRight(std::string word);
bool isString(std::string word);
bool isIdent(std::string word);

// IMP TTYPES

class TokenTypes {
public:
    IMPTokenType Space()    { return IMPTokenType("SPACE",isSpace); }
    IMPTokenType KwIf()     { return IMPTokenType("KW_IF",isKwIf); }
    IMPTokenType KwElif()   { return IMPTokenType("KW_ELIF",isKwElif); }
    IMPTokenType KwElse()   { return IMPTokenType("KW_ELSE",isKwElse); }
    IMPTokenType KwWhile()  { return IMPTokenType("KW_WHILE",isKwWhile); }
    IMPTokenType KwInt()    { return IMPTokenType("KW_INT",isKwInt); }
    IMPTokenType KwByte()   { return IMPTokenType("KW_BYTE",isKwByte); }
    IMPTokenType KwWord()   { return IMPTokenType("KW_WORD",isKwWord); }
    IMPTokenType KwDWord()  { return IMPTokenType("KW_DWORD",isKwDWord); }
    IMPTokenType KwFloat()  { return IMPTokenType("KW_FLOAT",isKwFloat); }
    IMPTokenType KwChar()   { return IMPTokenType("KW_CHAR",isKwChar); }
    IMPTokenType KwBool()   { return IMPTokenType("KW_BOOL",isKwBool); }
    IMPTokenType KwHide()   { return IMPTokenType("KW_HIDE",isKwHide); }
    IMPTokenType KwMx()     { return IMPTokenType("KW_MX",isKwMx); }
    IMPTokenType KwEnv()    { return IMPTokenType("KW_ENV",isKwEnv); }
    IMPTokenType KwFunc()   { return IMPTokenType("KW_FUNC",isKwFunc); }
    IMPTokenType KwProc()   { return IMPTokenType("KW_PROC",isKwProc); }
    IMPTokenType KwReturn() { return IMPTokenType("KW_RETURN",isKwReturn); }
    IMPTokenType SwAdd()    { return IMPTokenType("SW_ADD",isSWAdd); }
    IMPTokenType KwTrue()   { return IMPTokenType("KW_TRUE",isKwTrue); }
    IMPTokenType KwFalse()  { return IMPTokenType("KW_FALSE",isKwFalse); }
    IMPTokenType Decimal()  { return IMPTokenType("DECIMAL",isDecimal); }
    IMPTokenType Hexidec()  { return IMPTokenType("HEXIDEC",isHexidec); }
    IMPTokenType Binary()   { return IMPTokenType("BINARY",isBinary); }
    IMPTokenType BrOpCircle(){ return IMPTokenType("BRACKET_(",isBracketOpenCircle); }
    IMPTokenType BrClCircle(){ return IMPTokenType("BRACKET_)",isBracketCloseCircle); }
    IMPTokenType BrOpSquare(){ return IMPTokenType("BRACKET_[",isBracketOpenSquare); }
    IMPTokenType BrClSquare(){ return IMPTokenType("BRACKET_]",isBracketCloseSquare); }
    IMPTokenType BrOpCurly() { return IMPTokenType("BRACKET_{",isBracketOpenCurly); }
    IMPTokenType BrClCurly() { return IMPTokenType("BRACKET_}",isBracketCloseCurly); }
    IMPTokenType Assign()   { return IMPTokenType("ASSIGN",isAssign); }
    IMPTokenType Power()    { return IMPTokenType("POWER",isPower); }
    IMPTokenType Mod()      { return IMPTokenType("MOD",isMod); }
    IMPTokenType Mult()     { return IMPTokenType("MULT",isMult); }
    IMPTokenType Divide()   { return IMPTokenType("DIVIDE",isDivide); }
    IMPTokenType Plus()     { return IMPTokenType("PLUS",isPlus); }
    IMPTokenType Minus()    { return IMPTokenType("MINUS",isMinus); }
    IMPTokenType Equal()    { return IMPTokenType("EQUAL",isEqual); }
    IMPTokenType NotEqual() { return IMPTokenType("NOT_EQUAL",isNotEqual); }
    IMPTokenType MoreEqual(){ return IMPTokenType("MORE_OR_EQUAL",isMoreOrE); }
    IMPTokenType LessEqual(){ return IMPTokenType("LESS_OR_EQUAL",isLessOrE); }
    IMPTokenType More()     { return IMPTokenType("MORE",isMore); }
    IMPTokenType Less()     { return IMPTokenType("LESS",isLess); }
    IMPTokenType Negative() { return IMPTokenType("NEGATIVE",isNegative); }
    IMPTokenType And()      { return IMPTokenType("AND",isAnd); }
    IMPTokenType Or()       { return IMPTokenType("OR",isOr); }
    IMPTokenType Xor()      { return IMPTokenType("XOR",isXor); }
    IMPTokenType BitAnd()   { return IMPTokenType("BIT_AND",isBitAnd); }
    IMPTokenType BitOr()    { return IMPTokenType("BIT_OR",isBitOr); }
    IMPTokenType BitXor()   { return IMPTokenType("BIT_XOR",isBitXor); }
    IMPTokenType BitShiftLeft() { return IMPTokenType("BIT_SHIFT_LEFT",isBitShiftLeft); }
    IMPTokenType BitShiftRight(){ return IMPTokenType("BIT_SHIFT_RIGHT",isBitShiftRight); }
    IMPTokenType Comma()    { return IMPTokenType("COMMA",isComma); }
    IMPTokenType Colon()    { return IMPTokenType("COLON",isColon); }
    IMPTokenType Semicolon(){ return IMPTokenType("SEMICOLON",isSemicolon); }
    IMPTokenType String()   { return IMPTokenType("STRING",isString); }
    IMPTokenType Ident()    { return IMPTokenType("IDENT",isIdent); }
    IMPTokenType OP_Args()  { return IMPTokenType("ARGS",nullptr); }
    IMPTokenType OP_Index() { return IMPTokenType("INDEX",nullptr); }
    IMPTokenType ARGS_COUNT() { return IMPTokenType("ARGS_COUNT",nullptr); }
    IMPTokenType Error()    { return IMPTokenType("ERROR",nullptr); }
    IMPTokenType Null()     { return NULL_TOKEN; }
};

//TokenTypes tokenTypes;

#endif //IMP_TOKEN_H
