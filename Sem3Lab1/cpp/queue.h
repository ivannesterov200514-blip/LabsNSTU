#pragma once
#include <iostream>
#include <string>

using namespace std;

struct QNode {
    string data;
    QNode* next;
    QNode(string val, QNode* t) : data(val), next(t) {}
};

struct Queue {
    QNode* head;
    QNode* tail;
    int sz;
    Queue(QNode* n = nullptr) : head(n), tail(n), sz(n ? 1 : 0) {}
    ~Queue() {
        while (head != nullptr) {
            QNode* v = head;
            head = head->next;
            delete v;
        }
    }
};

void q_push(Queue* q, string val);
void q_pop(Queue* q);
void q_print(Queue* q);