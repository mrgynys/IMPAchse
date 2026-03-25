#ifndef IMP_FUNC_H
#define IMP_FUNC_H

#include"imp_data_types.h"
#include"../parser/imp_nodes.h"

class IMPFunc;

#define impfunc

class IMPFunc {
private:
    DataTypes dataTypes;
    TokenTypes tokenTypes;
public:
    IMPFunc() : type(dataTypes.Null()),data(IMPAstNode(IMPToken(tokenTypes.Null(),"",0,0))) {}
    IMPFunc(IMPDataType return_type, IMPAstNode return_data) : type(return_type),data(return_data) {}
    IMPFunc(const IMPFunc& func) : type(func.type),args(func.args),lscope(func.lscope),data(func.data) {}
    ~IMPFunc() {}

    IMPDataType type;
    std::vector<IMPID> args;
    std::vector<IMPID> lscope;
    IMPAstNode data;

    std::string show() {
        std::string temp = type.name + "(";
        for (int i = 0; i < args.size(); i++) {
            temp += args[i].type.name + " " + args[i].name;
            if (i < args.size()-1)  temp += ",";
        }
        temp += ")";
        return temp;
    }
};

#endif //IMP_FUNC_H
