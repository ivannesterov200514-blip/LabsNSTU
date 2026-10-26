#include "stack.h"

void st_push(Stack* s, string val) {
    STNode* n = new STNode{val, s->top};
    s->top = n;
    s->sz++;
}

void st_pop(Stack* s) {
    if (s->top == nullptr) {
        cout << "Ошибка: Стек пуст\n";
        return;
    }
    STNode* v = s->top;
    s->top = v->next;
    cout << v->data << endl;
    delete v;
    s->sz--;
}

void st_print(Stack* s) {
    if (s->top == nullptr) {
        cout << "Стек пуст\n";
        return;
    }
    STNode* curr = s->top;
    while (curr != nullptr) {
        cout << curr->data << endl;
        curr = curr->next;
    }
    cout << "nullptr\n";
}
