#ifndef IMP_PROJECT_MANAGER_H
#define IMP_PROJECT_MANAGER_H

#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<QTextCodec>
#include<string>
#include<vector>

namespace q_proj_filesystem {
    class path {
    private:
        QString _filepath;
        QString _parent_path;
        QString _stem;
        QString _extension;

    public:
        path(QString filepath) {
            _filepath = filepath;
            _parent_path = "";
            _stem = "";
            _extension = "";
            QString gstack = filepath;
            QString fstack = "";
            while (gstack.size() > 0) {
                QChar curc = gstack.back();
                if (curc == '/' or curc == '\\') {
                    gstack.chop(1);
                    _parent_path = gstack;
                    QString fnamestack = "";
                    bool write_extension = false;
                    while (fstack.size() > 0) {
                        QChar cc = fstack.back();
                        if (write_extension) {
                            _extension.push_back(fstack.back());
                            fstack.chop(1);
                        }
                        else if (cc == '.') {
                            _stem = fnamestack;
                            _extension.push_back(fstack.back());
                            fstack.chop(1);
                            write_extension = true;
                        }
                        else {
                            fnamestack.push_back(cc);
                            fstack.chop(1);
                        }
                    }
                    break;
                }
                else {
                    fstack.push_back(curc);
                    gstack.chop(1);
                }
            }
        }
        ~path() {}

        QString parent_path() { return _parent_path; }

        QString stem() { return _stem; }

        QString extension() { return _extension; }
    };
};

class ProjFile {
private:
    QString _path;
    QString _filename;
    QString _extension;
public:
    std::vector<QString> code;


    ProjFile() {
        _path = "";
        _filename = "untitled";
        _extension = ".impctrl";
    }

    ProjFile(QString path) {
        q_proj_filesystem::path p(path);
        _path = p.parent_path();
        _filename = p.stem();
        _extension = p.extension();
    }

    ProjFile(const ProjFile& _file_) {
        this->code = _file_.code;
        this->_path = _file_._path;
        this->_filename = _file_._filename;
        this->_extension = _file_._extension;
    }

    ~ProjFile() {}

    std::vector<QString> read() {
        QFile f(fpath());
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&f);
            in.setCodec("UTF-8");
            QString content = in.readAll();
            QString stack = "";
            for (QChar c : content) {
                if (c == '\n') {
                    code.push_back(stack);
                    stack.clear();
                }
                else {
                    stack.push_back(c);
                }
            }
            code.push_back(stack);
            f.close();
        }
        else {
            qDebug() << "cannot open file: " << fpath();
        }
        return code;
    }

    void write(std::vector<QString> ccode) {
        code=ccode;
        QFile f(fpath());
        if (f.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&f);
            out.setCodec(QTextCodec::codecForName("UTF-8"));
            for (QString c : code) {
                out << c << "\n";
            }
            f.close();
        }
    }

    QString fpath()     { return _path+(_path!="" ? "/" : "")+_filename+_extension; }
    QString path()      { return _path; }
    QString filename()  { return _filename; }
    QString ext()       { return _extension; }
};


bool returnFalse(QString);

class QTokenType {
public:
    QString name;
    bool (*is)(QString);

    QTokenType() { name = ""; is = returnFalse; }
    QTokenType(QString token_name, bool (*ident_func)(QString)) {
        name = token_name;
        if (ident_func==nullptr) {
            is = returnFalse;
        }
        else {
            is = ident_func;
        }
    }
    QTokenType(const QTokenType& imptt) {
        name = imptt.name;
        if (imptt.is==nullptr) {
            is = returnFalse;
        }
        else {
            is = imptt.is;
        }
    }
    ~QTokenType() {}


    bool operator==(const QTokenType& tokentype) { return this->name==tokentype.name; }
    bool operator==(const std::vector<QTokenType>& tokentype) {
        for (QTokenType type : tokentype) if (type.name == this->name) return true;
        return false;
    }
    bool operator!=(const QTokenType& tokentype) { return this->name!=tokentype.name; }
};

class QToken {
public:
    QToken(QTokenType token_type, QString token_text, int rowpos, int colpos)
        : type(token_type),text(token_text),row(rowpos),col(colpos) {}
    ~QToken() {}

    QTokenType type;
    QString text;
    int row;
    int col;
};

bool qisSpace(QString word);
bool qisDecimal(QString word);
bool qisAssign(QString word);
bool qisBracketOpenCurly(QString word);
bool qisBracketCloseCurly(QString word);
bool qisString(QString word);
bool qisIdent(QString word);

class QTokenTypes {
public:
    QTokenType Space()      { return QTokenType("SPACE",qisSpace); }
    QTokenType Decimal()    { return QTokenType("DECIMAL",qisDecimal); }
    QTokenType Assign()     { return QTokenType("ASSIGN",qisAssign); }
    QTokenType BrOpCurly()  { return QTokenType("BRACKET_{",qisBracketOpenCurly); }
    QTokenType BrClCurly()  { return QTokenType("BRACKET_}",qisBracketCloseCurly); }
    QTokenType String()     { return QTokenType("STRING",qisString); }
    QTokenType Ident()      { return QTokenType("IDENT",qisIdent); }
    QTokenType Error()      { return QTokenType("ERROR",nullptr); }
    QTokenType Null()       { return QTokenType(); }
};

class QProjLexer {
private:
    QTokenTypes tokenTypes;
    std::vector<QString> code;
    int row;
    int col;

    QToken lexToken(QString word, int rowpos, int colpos) {
        if (tokenTypes.Space().is(word))        return QToken(tokenTypes.Space(),word,rowpos,colpos);
        if (tokenTypes.Decimal().is(word))      return QToken(tokenTypes.Decimal(),word,rowpos,colpos);
        if (tokenTypes.Assign().is(word))       return QToken(tokenTypes.Assign(),word,rowpos,colpos);
        if (tokenTypes.BrOpCurly().is(word))    return QToken(tokenTypes.BrOpCurly(),word,rowpos,colpos);
        if (tokenTypes.BrClCurly().is(word))    return QToken(tokenTypes.BrClCurly(),word,rowpos,colpos);
        if (tokenTypes.String().is(word))       return QToken(tokenTypes.String(),word.remove(0,1).remove(word.length()-1,1),rowpos,colpos);
        if (tokenTypes.Ident().is(word))        return QToken(tokenTypes.Ident(),word,rowpos,colpos);
        return QToken(tokenTypes.Error(),word,rowpos,colpos);
    }
public:
    std::vector<QToken> tokens;

    QProjLexer(std::vector<QString> imp_code)
    : code(imp_code),row(0),col(0) {

    }
    ~QProjLexer() {}

    int lex() {
        if (code.size() < 1) return 0;

        QString splitters = "{}=";
        QString x_splitters = " \t\n";

        int cur_word_row = 0;
        int cur_word_col = 0;
        QString cur_word = "";

        bool string_begins = false;

        row = 0;

        for (QString str : code) {
            if (string_begins) {
                return -1;
                string_begins = false;
            }
            row++;
            cur_word_row = row;
            cur_word_col = 1;
            col = 0;
            if (str.size()<1) continue;
            while (col < str.size()) {
                col++;
                if (str[col-1]=='\"') {
                    if (string_begins) cur_word += str[col-1];
                    QToken cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                    if (cur_token.type.name!="SPACE") tokens.push_back(cur_token);
                    if (cur_token.type.name=="ERROR")
                        return -1;
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
                else if (x_splitters.indexOf(str[col-1])!=-1) {
                    QToken cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                    if (cur_token.type.name!="SPACE") tokens.push_back(cur_token);
                    if (cur_token.type.name=="ERROR")
                        return -1;
                    cur_word = "";
                    cur_word_col = col+1;
                }
                else if (splitters.indexOf(str[col-1])!=-1) {
                    QToken cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                    if (cur_token.type.name!="SPACE") tokens.push_back(cur_token);
                    if (cur_token.type.name=="ERROR")
                        return -1;
                    cur_word = str[col-1];
                    cur_word_col = col;
                    QToken new_cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                    if (new_cur_token.type.name!="SPACE") tokens.push_back(new_cur_token);
                    if (new_cur_token.type.name=="ERROR")
                        return -1;
                    cur_word = "";
                    cur_word_col = col+1;
                }
                else {
                    cur_word += str[col-1];
                }
            }
            if (cur_word != "") {
                QToken cur_token(lexToken(cur_word,cur_word_row,cur_word_col));
                if (cur_token.type.name!="SPACE") tokens.push_back(cur_token);
                if (cur_token.type.name=="ERROR")
                    return -1;
                cur_word = "";
                cur_word_col = col;
            }
        }
        return 0;
    }
};

class PropStr {
public:
    PropStr() {}
    PropStr(QString prop_name, QString prop_value) : name(prop_name),value(prop_value) {}
    ~PropStr() {}

    QString name;
    QString value;
};

class PropInt {
public:
    PropInt() {}
    PropInt(QString prop_name, int prop_value) : name(prop_name),value(prop_value) {}
    ~PropInt() {}

    QString name;
    int value;
};

class Obj {
private:
    QTokenTypes tokenTypes;
public:
    Obj() {}
    Obj(QString obj_name) : name(obj_name) {}
    ~Obj() {}

    QString name;
    std::vector<PropStr>    props_str;
    std::vector<PropInt>    props_int;
    std::vector<Obj>        objs;

    std::vector<QString> getCode() {
        std::vector<QString> code;
        for (PropStr i : props_str) {
            if (i.name != "null") {
                code.push_back(i.name+"=\""+i.value+"\"");
            }
        }
        for (PropInt i : props_int) {
            if (i.name != "null") {
                code.push_back(i.name+"="+QString(std::to_string(i.value).c_str()));
            }
        }
        for (Obj i : objs) {
            if (i.name != "null") {
                code.push_back(i.name);
                code.push_back("{");
                for (QString str : i.getCode()) {
                    code.push_back(str);
                }
                code.push_back("}");
            }
        }
        return code;
    }

    QString sfind(QString name) {
        for (PropStr p : props_str) {
            if (p.name == name) return p.value;
        }
        return "null";
    }

    int ifind(QString name) {
        for (PropInt p : props_int) {
            if (p.name == name) return p.value;
        }
        return -1;
    }

    Obj ofind(QString name) {
        for (Obj o : objs) {
            if (o.name == name) return o;
        }
        return Obj("null");
    }

    int oindex(QString name) {
        for (int i = 0; i < objs.size(); i++) {
            if (objs[i].name == name) return i;
        }
        return -1;
    }

    Obj* getpointer(int index) {
        for (int i = 0; i < objs.size(); i++) {
            if (i == index) return &(objs[i]);
        }
        return nullptr;
    }

    void sset(QString name, QString val) {
        for (int i = 0; i < props_str.size(); i++) {
            if (props_str[i].name == name) {
                props_str[i].value = val;
                return;
            }
        }
        props_str.push_back(PropStr(name,val));
    }

    void iset(QString name, int val) {
        for (int i = 0; i < props_int.size(); i++) {
            if (props_int[i].name == name) {
                props_int[i].value = val;
                return;
            }
        }
        props_int.push_back(PropInt(name,val));
    }

    void setobj(QString name, Obj obj) {
        for (int i = 0; i < objs.size(); i++) {
            if (objs[i].name == name) {
                objs[i] = obj;
                return;
            }
        }
        objs.push_back(obj);
    }

    void fillObj(std::vector<QToken> tokens) {
        int pos = 0;
        int bracket = 0;
        QString objname = "";
        std::vector<QToken> temp;
        while (pos < tokens.size()) {
            if (bracket > 0) {
                if (tokens[pos].type == tokenTypes.BrOpCurly()) {
                    bracket++;
                    if (bracket > 1) temp.push_back(tokens[pos]);
                    pos++;
                }
                else if (tokens[pos].type == tokenTypes.BrClCurly()) {
                    if (bracket > 1) temp.push_back(tokens[pos]);
                    pos++;
                    bracket--;
                    if (bracket == 0) {
                        Obj o(objname);
                        o.fillObj(temp);
                        temp.clear();
                        objs.push_back(o);
                    }
                }
                else {
                    temp.push_back(tokens[pos]);
                    pos++;
                }
            }
            else if (tokens[pos].type == tokenTypes.Ident()) {
                if (tokens[pos+1].type == tokenTypes.Assign()) {
                    if (tokens[pos+2].type == tokenTypes.String()) {
                        props_str.push_back(PropStr(tokens[pos].text,tokens[pos+2].text));
                        pos+=3;
                    }
                    else if (tokens[pos+2].type == tokenTypes.Decimal()) {
                        props_int.push_back(PropInt(tokens[pos].text,tokens[pos+2].text.toInt()));
                        pos+=3;
                    }
                }
                else if (tokens[pos+1].type == tokenTypes.BrOpCurly()) {
                    objname = tokens[pos].text;
                    bracket++;
                    pos+=2;
                }
            }
        }
    }
};

class IMPProj {
private:
    QTokenTypes tokenTypes;
public:
    IMPProj() : changes(0),path("") {}
    ~IMPProj() {}

    int changes;
    QString path;
    std::vector<PropStr>    props_str;
    std::vector<PropInt>    props_int;
    std::vector<Obj>        objs;

    std::vector<QString> getCode() {
        std::vector<QString> code;
        for (PropStr i : props_str) {
            if (i.name != "null") {
                code.push_back(i.name+"=\""+i.value+"\"");
            }
        }
        for (PropInt i : props_int) {
            if (i.name != "null") {
                code.push_back(i.name+"="+QString(std::to_string(i.value).c_str()));
            }
        }
        for (Obj i : objs) {
            if (i.name != "null") {
                code.push_back(i.name);
                code.push_back("{");
                for (QString str : i.getCode()) {
                    code.push_back(str);
                }
                code.push_back("}");
            }
        }
        return code;
    }

    QString sfind(QString name) {
        for (PropStr p : props_str) {
            if (p.name == name) return p.value;
        }
        return "null";
    }

    int ifind(QString name) {
        for (PropInt p : props_int) {
            if (p.name == name) return p.value;
        }
        return -1;
    }

    Obj ofind(QString name) {
        for (Obj o : objs) {
            if (o.name == name) return o;
        }
        return Obj("null");
    }

    Obj* getpointer(int index) {
        for (int i = 0; i < objs.size(); i++) {
            if (i == index) return &(objs[i]);
        }
        return nullptr;
    }

    int oindex(QString name) {
        for (int i = 0; i < objs.size(); i++) {
            if (objs[i].name == name) return i;
        }
        return -1;
    }

    void sset(QString name, QString val) {
        for (int i = 0; i < props_str.size(); i++) {
            if (props_str[i].name == name) {
                props_str[i].value = val;
                return;
            }
        }
        props_str.push_back(PropStr(name,val));
    }

    void iset(QString name, int val) {
        for (int i = 0; i < props_int.size(); i++) {
            if (props_int[i].name == name) {
                props_int[i].value = val;
                return;
            }
        }
        props_int.push_back(PropInt(name,val));
    }

    void setobj(QString name, Obj obj) {
        for (int i = 0; i < objs.size(); i++) {
            if (objs[i].name == name) {
                objs[i] = obj;
                return;
            }
        }
        objs.push_back(obj);
    }

    void fillProj(std::vector<QToken> tokens) {
        int pos = 0;
        int bracket = 0;
        QString objname = "";
        std::vector<QToken> temp;
        while (pos < tokens.size()) {
            if (bracket > 0) {
                if (tokens[pos].type == tokenTypes.BrOpCurly()) {
                    bracket++;
                    if (bracket > 1) temp.push_back(tokens[pos]);
                    pos++;
                }
                else if (tokens[pos].type == tokenTypes.BrClCurly()) {
                    if (bracket > 1) temp.push_back(tokens[pos]);
                    pos++;
                    bracket--;
                    if (bracket == 0) {
                        Obj o(objname);
                        o.fillObj(temp);
                        temp.clear();
                        objs.push_back(o);
                    }
                }
                else {
                    temp.push_back(tokens[pos]);
                    pos++;
                }
            }
            else if (tokens[pos].type == tokenTypes.Ident()) {
                if (tokens[pos+1].type == tokenTypes.Assign()) {
                    if (tokens[pos+2].type == tokenTypes.String()) {
                        props_str.push_back(PropStr(tokens[pos].text,tokens[pos+2].text));
                        pos+=3;
                    }
                    else if (tokens[pos+2].type == tokenTypes.Decimal()) {
                        props_int.push_back(PropInt(tokens[pos].text,tokens[pos+2].text.toInt()));
                        pos+=3;
                    }
                }
                else if (tokens[pos+1].type == tokenTypes.BrOpCurly()) {
                    objname = tokens[pos].text;
                    bracket++;
                    pos+=2;
                }
            }
        }
    }
};

#endif // IMP_PROJECT_MANAGER_H
