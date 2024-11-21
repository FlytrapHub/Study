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

OrgStructure::Node *OrgStructure::find(const std::string &value) {
    return find(root, value);
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

// 전위 순회
// 현재 노드 먼저 방문 -> 현재 노드의 왼쪽 하위 노드 -> 현재 노드의 오른쪽 하위 노드
void OrgStructure::preOrderTraversal(const Node *start) {
    if (!start)
        return;

    std::cout << start->position << ", " << std::endl;

    preOrderTraversal(start->first);
    preOrderTraversal(start->second);
}

// 중위 순회
// 왼쪽 노드 -> 현재 노드 -> 오른쪽 노드
void OrgStructure::inOrderTraversal(const Node *start) {
    if (!start)
        return;

    inOrderTraversal(start->first);
    std::cout << start->position << ", " << std::endl;
    inOrderTraversal(start->second);
}

// 후위 순회
// 왼쪽 노드 -> 오른쪽 노드 -> 현재 노드
void OrgStructure::postOrderTraversal(const Node *start) {
    if (!start)
        return;

    postOrderTraversal(start->first);
    postOrderTraversal(start->second);
    std::cout << start->position << ", " << std::endl;
}

// 레벨 순회
// 트리의 맨 위 레벨부터 아래 헤벨까지, 왼쪽 노드에서 오른쪽 노드 순서로 방문
void OrgStructure::levelOrderTraversal(Node *start) {
    if (!start)
        return;

    std::queue<Node*> queue;
    queue.push(start);

    while (!queue.empty()) {
        int size = queue.size();
        for (int i = 0; i < size; i++) {
            Node* current = queue.front();
            queue.pop();

            std::cout << current->position << ", ";
            if (current->first)
                queue.push(current->first);
            if (current->second)
                queue.push(current->second);
        }
        std::cout << std::endl;
    }
}



int main() {
    //            CEO
    //             |
    //            부사장
    //          /      \
    //      IT부장       마케팅부장
    //     /    \       /     \
    // 보안팀장 앱개발팀장 물류팀장 홍보팀장

    OrgStructure *orgTree = new OrgStructure("CEO");

    orgTree->addSubordinate("CEO", "부사장");
    orgTree->addSubordinate("부사장", "IT부장");
    orgTree->addSubordinate("부사장", "마케팅부장");
    orgTree->addSubordinate("IT부장", "보안팀장");
    orgTree->addSubordinate("IT부장", "앱개발팀장");
    orgTree->addSubordinate("마케팅부장", "물류팀장");
    orgTree->addSubordinate("마케팅부장", "홍보팀장");
    orgTree->addSubordinate("부사장", "재무부장");
    std::cout << std::endl;

    OrgStructure::Node* root = orgTree->find("CEO");

    std::cout << "[전위 순회]" << std::endl;
    OrgStructure::preOrderTraversal(root);
    std::cout << std::endl;

    std::cout << "[중위 순회]" << std::endl;
    OrgStructure::inOrderTraversal(root);
    std::cout << std::endl;

    std::cout << "[후위 순회]" << std::endl;
    OrgStructure::postOrderTraversal(root);
    std::cout << std::endl;

    std::cout << "[레벨 순회]" << std::endl;
    OrgStructure::levelOrderTraversal(root);
    std::cout << std::endl;

    std::cout << "[메모리 해제하기]" << std::endl;

    delete orgTree;

    return 0;
}
