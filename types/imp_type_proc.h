#ifndef IMP_TYPE_PROC_H
#define IMP_TYPE_PROC_H

#include"imp_data_types.h"
#include"../parser/imp_nodes.h"

class IMPProc;

#define impproc

class IMPProc {
    DataTypes dataTypes;
public:
    IMPProc() : type(dataTypes.Null()) {}
    IMPProc(std::vector<IMPAstNode> instructions) : ops(instructions),type(dataTypes.Void()) {}
    IMPProc(IMPDataType return_type, std::vector<IMPAstNode> instructions) : ops(instructions),type(return_type) {}
    IMPProc(const IMPProc& proc) : ops(proc.ops),type(proc.type),args(proc.args),lscope(proc.lscope) {}
    ~IMPProc() {}

    std::vector<IMPAstNode> ops;
    std::vector<IMPID> args;
    std::vector<IMPID> lscope;
    IMPDataType type;

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


#endif //IMP_TYPE_PROC_H
