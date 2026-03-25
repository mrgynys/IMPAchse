#include"imp_environment.h"

int findId(std::string name, std::vector<IMPEnv> scope) {
    for (int scopei = 0; scopei < scope.size(); scopei++) {
        for (IMPID iid : scope[scopei].idents) {
            if (iid.name == name) return scopei;
        }
    }
    return nfind;
}

int findId(std::string name, std::vector<IMPID> scope) {
    for (int i = 0; i < scope.size(); i++) {
        if (scope[i].name == name) return i;
    }
    return nfind;
}
