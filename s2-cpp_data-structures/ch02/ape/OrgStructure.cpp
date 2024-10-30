//
// Created by Seonghwan Ju on 2024. 10. 29..
//

#include "OrgStructure.h"

OrgStructure::OrgStructure(const std::string &pos) {
    Node *node = new Node; // 동적 할당
    node->position = pos;
    node->first = nullptr;
    node->second = nullptr;

    root = node;
}

OrgStructure::~OrgStructure() {
    // 모든 Node 포인터들을 할당 해제해줘야 함
    if (root == nullptr) return;

    std::stack<Node *> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()) {
        Node *node = nodeStack.top();
        nodeStack.pop();

        // 자식 노드를 스택에 추가
        if (node->first) nodeStack.push(node->first);
        if (node->second) nodeStack.push(node->second);

        // 현재 노드 삭제
        std::cout << node->position << " 메모리 해제" << std::endl;
        delete node;
    }
}

OrgStructure::Node *OrgStructure::find(
    Node *root,
    const std::string &value) {
    if (root == nullptr)
        return nullptr;

    // 가장 먼저 root 노드를 검사
    if (root->position == value)
        return root;

    // root에 없으면 왼쪽 노드 검사
    Node *firstFound = find(root->first, value);

    if (firstFound != nullptr)
        return firstFound;

    // 왼쪽에도 없으면 오른쪽 노드 검사
    return find(root->second, value);
}

bool OrgStructure::addSubordinate(
    const std::string &manager,
    const std::string &subordinate) {
    Node *managerNode = find(root, manager);

    if (!managerNode) {
        std::cout << manager << "을(를) 찾을 수 없습니다: " << std::endl;
        return false;
    }

    if (managerNode->first && managerNode->second) {
        std::cout << manager << " 아래에 " << subordinate << "를 추가할 수 없습니다." << std::endl;
        return false;
    }

    if (!managerNode->first)
        managerNode->first = new Node{subordinate, nullptr, nullptr};
    else if (!managerNode->second)
        managerNode->second = new Node{subordinate, nullptr, nullptr};

    std::cout << manager << " 아래에 " << subordinate << "를 추가했습니다." << std::endl;

    return true;
}

int main() {
    OrgStructure *orgTree = new OrgStructure("CEO");

    orgTree->addSubordinate("CEO", "부사장");
    orgTree->addSubordinate("부사장", "IT부장");
    orgTree->addSubordinate("부사장", "마케팅부장");
    orgTree->addSubordinate("IT부장", "보안팀장");
    orgTree->addSubordinate("IT부장", "앱개발팀장");
    orgTree->addSubordinate("마케팅부장", "물류팀장");
    orgTree->addSubordinate("마케팅부장", "홍보팀장");
    orgTree->addSubordinate("부사장", "재무부장");

    std::cout << "\n[메모리 해제하기]" << std::endl;

    delete orgTree;

    return 0;
}
