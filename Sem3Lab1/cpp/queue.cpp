#include "queue.h"

void q_push(Queue* q, string val) {
    QNode* n = new QNode{val, nullptr};
    if (q->tail == nullptr) {
        q->head = n;
        q->tail = n;
    } else {
        q->tail->next = n;
        q->tail = n;
    }
    q->sz++;
}

void q_pop(Queue* q) {
    if (q->head == nullptr) {
        cout << "Ошибка: Очередь пуста\n";
        return;
    }
    QNode* v = q->head;
    q->head = v->next;
    if (q->head == nullptr) {
        q->tail = nullptr;
    }
    cout << v->data << endl;
    delete v;
    q->sz--;
}

void q_print(Queue* q) {
    if (q->head == nullptr) {
        cout << "Очередь пуста\n";
        return;
    }
    cout << "Head: ";
    QNode* cur = q->head;
    while (cur != nullptr) {
        cout << cur->data << " -> ";
        cur = cur->next;
    }
    cout << ": Tail\n";
}
