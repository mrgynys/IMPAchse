#include"imp_project_manager.h"

bool returnFalse(QString) {
    return false;
}

bool qisSpace(QString word) {
    for (QChar c : word) {
        if (c != ' ' and c != '\t' and c != '\n') return false;
    }
    return true;
}

bool qisDecimal(QString word) {
    QString edges = "0123456789";
    char dot = '.';
    if (word.size()<1) return false;
    if ((edges.indexOf(word[0])==-1) or (edges.indexOf(word[word.size()-1])==-1)) return false;
    bool dot_found = false;
    for (int i = 1; i < word.size()-1; i++) {
        if (dot==word[i]) {
            if (dot_found) return false;
            else dot_found = true;
        } else if (edges.indexOf(word[i])==-1) {
            return false;
        }
    }
    return true;
}

bool qisAssign(QString word)             { return word=="="; }
bool qisBracketOpenCurly(QString word)   { return word=="{"; }
bool qisBracketCloseCurly(QString word)  { return word=="}"; }

bool qisString(QString word) {
    return word[0]=='\"' and word[word.size()-1]=='\"';
}

bool qisIdent(QString word) {
    QString abc = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm_";
    QString numeric = "0123456789";
    if (word.length()<1) return false;
    if (numeric.indexOf(word[0])!=-1) return false;
    for (int i = 0; i < word.length(); i++) {
        if ((abc.indexOf(word[i])==-1) and (numeric.indexOf(word[i])==-1)) {
            return false;
        }
    }
    return true;
}
