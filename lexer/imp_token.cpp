#include"imp_token.h"

bool returnFalse(std::string) {return false;}

bool isSpace(std::string word) {
    for (char c : word) {
        if (c != ' ' and c != '\t' and c != '\n') return false;
    }
    return true;
}

bool isDecimal(std::string word) {
    std::string edges = "0123456789";
    char dot = '.';
    if (word.size()<1) return false;
    if ((edges.find(word[0])==std::string::npos) or (edges.find(word[word.size()-1])==std::string::npos)) return false;
    bool dot_found = false;
    for (int i = 1; i < word.size()-1; i++) {
        if (dot==word[i]) {
            if (dot_found) return false;
            else dot_found = true;
        } else if (edges.find(word[i])==std::string::npos) {
            return false;
        }
    }
    return true;
}

bool isHexidec(std::string word) {
    std::string digits = "0123456789ABCDEF";
    if(word.size()<3) return false;
    if(word[0]!='0' or word[1]!='x') return false;
    for (char c : word.substr(2,word.size()-2)) {
        if (digits.find(c)==std::string::npos) return false;
    }
    return true;
}

bool isBinary(std::string word) {
    std::string digits = "01";
    if(word.size()<3) return false;
    if(word[0]!='0' or word[1]!='b') return false;
    for (char c : word.substr(2,word.size()-2)) {
        if (digits.find(c)==std::string::npos) return false;
    }
    return true;
}

bool isKwIf(std::string word)               { return word=="if"; }
bool isKwElif(std::string word)             { return word=="elif"; }
bool isKwElse(std::string word)             { return word=="else"; }
bool isKwWhile(std::string word)            { return word=="while"; }
bool isKwInt(std::string word)              { return word=="int"; }
bool isKwByte(std::string word)             { return word=="byte"; }
bool isKwWord(std::string word)             { return word=="word"; }
bool isKwDWord(std::string word)            { return word=="dword"; }
bool isKwFloat(std::string word)            { return word=="float"; }
bool isKwChar(std::string word)             { return word=="char"; }
bool isKwBool(std::string word)             { return word=="bool"; }
bool isKwHide(std::string word)             { return word=="hide"; }
bool isKwMx(std::string word)               { return word=="mx"; }
bool isKwEnv(std::string word)              { return word=="env"; }
bool isKwFunc(std::string word)             { return word=="func"; }
bool isKwProc(std::string word)             { return word=="proc"; }
bool isKwReturn(std::string word)           { return word=="return"; }
bool isSWAdd(std::string word)              { return word=="~add"; }
bool isKwTrue(std::string word)             { return word=="true"; }
bool isKwFalse(std::string word)            { return word=="false"; }
bool isBracketOpenCircle(std::string word)  { return word=="("; }
bool isBracketCloseCircle(std::string word) { return word==")"; }
bool isBracketOpenSquare(std::string word)  { return word=="["; }
bool isBracketCloseSquare(std::string word) { return word=="]"; }
bool isBracketOpenCurly(std::string word)   { return word=="{"; }
bool isBracketCloseCurly(std::string word)  { return word=="}"; }
bool isComma(std::string word)              { return word==","; }
bool isColon(std::string word)              { return word==":"; }
bool isSemicolon(std::string word)          { return word==";"; }
bool isAssign(std::string word)             { return word=="="; }
bool isPower(std::string word)              { return word=="^"; }
bool isMod(std::string word)                { return word=="%"; }
bool isMult(std::string word)               { return word=="*"; }
bool isDivide(std::string word)             { return word=="/"; }
bool isPlus(std::string word)               { return word=="+"; }
bool isMinus(std::string word)              { return word=="-"; }
bool isEqual(std::string word)              { return word=="=="; }
bool isNotEqual(std::string word)           { return word=="<>"; }
bool isMoreOrE(std::string word)            { return (word==">=") or (word=="=>"); }
bool isLessOrE(std::string word)            { return (word=="<=") or (word=="=<"); }
bool isMore(std::string word)               { return word==">"; }
bool isLess(std::string word)               { return word=="<"; }
bool isNegative(std::string word)           { return word=="!"; }
bool isAnd(std::string word)                { return word=="&&"; }
bool isOr(std::string word)                 { return word=="||"; }
bool isXor(std::string word)                { return word=="##"; }
bool isBitAnd(std::string word)             { return word=="&"; }
bool isBitOr(std::string word)              { return word=="|"; }
bool isBitXor(std::string word)             { return word=="#"; }
bool isBitShiftLeft(std::string word)       { return word=="<<"; }
bool isBitShiftRight(std::string word)      { return word==">>"; }

bool isString(std::string word) {
    return word[0]=='\"' and word[word.size()-1]=='\"';
}

bool isIdent(std::string word) {
    std::string abc = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm_";
    std::string numeric = "0123456789";
    if (word.size()<1) return false;
    if (numeric.find(word[0])!=std::string::npos) return false;
    for (int i = 0; i < word.size(); i++) {
        if ((abc.find(word[i])==std::string::npos) and (numeric.find(word[i])==std::string::npos)) {
            return false;
        }
    }
    return true;
}
