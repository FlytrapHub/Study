//
// Created by Seonghwan Ju on 2024. 10. 29..
//

#ifndef ORGSTRUCTURE_H
#define ORGSTRUCTURE_H

#include <iostream>
#include <stack>

class OrgStructure {
public:
    struct Node {
        std::string position;
        Node *first;
        Node *second;
    };

    explicit OrgStructure(const std::string &pos);

    ~OrgStructure();

    Node *find(Node *root, const std::string &value);

    bool addSubordinate(const std::string &manager, const std::string &subordinate);

private:
    Node *root;
};


#endif //ORGSTRUCTURE_H
