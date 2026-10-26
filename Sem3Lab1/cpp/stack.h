#pragma once
#include <iostream>
#include <string>

using namespace std;

struct STNode {
    string data;
    STNode* next;
    STNode(string val, STNode* t) : data(val), next(t) {}
};

struct Stack {
    STNode* top;
    int sz;
    Stack(STNode* n = nullptr) : top(n), sz(n ? 1 : 0) {}
    ~Stack() {
        while (top != nullptr) {
            STNode* v = top;
            top = top->next;
            delete v;
        }
    }
};

void st_push(Stack* s, string val);
void st_pop(Stack* s);
void st_print(Stack* s);