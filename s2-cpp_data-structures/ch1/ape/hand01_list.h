//
// Created by Seonghwan Ju on 2024. 10. 16..
//

#ifndef HAND01LIST_H
#define HAND01LIST_H

#include <iostream>
#include <string>

using namespace std;

class Hand01List {
public:
    Hand01List();  // 생성자
    ~Hand01List(); // 소멸자

    void add(const string& value);    // 노드 추가
    void remove(int index);           // 노드 삭제
    void printForward() const;        // 리스트 출력 (정방향)
    void printBackward() const;       // 리스트 출력 (역방향)
    void print(int startIndex, int count) const; // 특정 인덱스부터 개수만큼 출력

private:
    struct Node { // 내부 구조체로 노드 정의
        string data;
        Node *next;
        Node *prev;
        explicit Node(string value) : data(move(value)), next(nullptr), prev(nullptr) {}
    };

    Node* head;  // 리스트의 시작점
    Node* tail;  // 리스트의 끝점
    size_t size; // 리스트의 크기
};

#endif // HAND01LIST_H

