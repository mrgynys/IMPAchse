#ifndef IMP_ENVIRONMENT_H
#define IMP_ENVIRONMENT_H

#include"imp_type_entity.h"
#include"imp_type_matrix.h"
#include"imp_type_proc.h"
#include"imp_data_types.h"

class IMPEnv {
    DataTypes dataTypes;
public:
    IMPEnv(std::string name) : id(dataTypes.Env(),name) {}
    ~IMPEnv() {}

    IMPID id;

    std::vector<IMPID> idents;
    std::map<int,IMPMatrix> matrixes;
    std::map<int,IMPEntityInt> int_ents;
    std::map<int,IMPEntityByte> byte_ents;
    std::map<int,IMPEntityWord> word_ents;
    std::map<int,IMPEntityDWord> dword_ents;
    std::map<int,IMPEntityFloat> float_ents;
    std::map<int,IMPEntityChar> char_ents;
    std::map<int,IMPEntityBool> bool_ents;
    std::map<int,IMPProc> proc;

    
    int findId(std::string name) {
        for (int i = 0; i < idents.size(); i++) {
            if (idents[i].name == name) return i;
        }
        return nfind;
    }
};

int findId(std::string name, std::vector<IMPEnv> scope);

int findId(std::string name, std::vector<IMPID> scope);

#endif // IMP_ENVIRONMENT_H
