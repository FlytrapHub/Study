//
// Created by Seonghwan Ju on 2024. 10. 16..
//

#include "hand01_list.h"

// 생성자
Hand01List::Hand01List() : head(nullptr), tail(nullptr), size(0) {}

// 소멸자
Hand01List::~Hand01List() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

// 노드 추가
void Hand01List::add(const string& value) {
    Node* newNode = new Node(value);
    if (!head) {  // 리스트가 비어 있을 때
        head = tail = newNode;
    } else {      // 리스트에 노드가 있을 때
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

// 노드 삭제
void Hand01List::remove(int index) {
    if (index < 0 || index >= size) {
        cerr << "Index out of bounds!" << endl;
        return;
    }

    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    if (current->prev) {
        current->prev->next = current->next;
    } else {
        head = current->next;
    }

    if (current->next) {
        current->next->prev = current->prev;
    } else {
        tail = current->prev;
    }

    delete current;
    size--;
}

// 리스트 출력 (정방향)
void Hand01List::printForward() const {
    Node* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// 리스트 출력 (역방향)
void Hand01List::printBackward() const {
    Node* current = tail;
    while (current) {
        cout << current->data << " ";
        current = current->prev;
    }
    cout << endl;
}

// 특정 인덱스부터 개수만큼 출력
void Hand01List::print(int startIndex, int count) const {
    Node* current = head;
    for (int i = 0; i < startIndex; ++i) {
        current = current->next;
    }

    for (int i = 0; i < count; ++i) {
        if (!current) {
            current = head;
        }
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}
