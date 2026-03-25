#ifndef IMP_NODES_H
#define IMP_NODES_H

#include<vector>

#include"../lexer/imp_token.h"


class IMPAstNode {
private:
    std::string show(int tab_num) {
        std::string tabs_str = "";
        for (int t = 0; t < tab_num; t++) {
            tabs_str += " ";
        }
        std::string temp = tabs_str + "\033[32m" + value.type.name + "\033[0m  \033[93m" + value.text + "\033[0m  " + std::to_string(value.row) + ":" + std::to_string(value.col) + "\n";
        for (int i = 0; i < childs.size(); i++) {
            temp += tabs_str + childs[i].show(tab_num+1);
        }
        return temp;
    }
public:
    IMPAstNode(IMPToken token) : value(token) {}
    IMPAstNode(IMPToken token, std::vector<IMPAstNode> nodes) : value(token), childs(nodes) {}
    ~IMPAstNode() {}
    IMPToken value;
    std::vector<IMPAstNode> childs;

    std::string show() {
        std::string temp = "\033[32m" + value.type.name + "\033[0m  \033[93m" + value.text + "\033[0m  " + std::to_string(value.row) + ":" + std::to_string(value.col) + "\n";
        for (int i = 0; i < childs.size(); i++) {
            temp += childs[i].show(1);
        }
        return temp;
    }
};

#endif //IMP_NODES_H