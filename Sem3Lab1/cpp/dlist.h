#pragma once
#include <iostream>
#include <string>

using namespace std;

struct SNode {
    string data;
    SNode* next;
    SNode* prev;
    SNode(string val, SNode* nx, SNode* pv) : data(val), next(nx), prev(pv) {}
};

struct DList {
    SNode* head;
    SNode* tail;
    int sz;
    DList(SNode* n = nullptr) : head(n), tail(n), sz(n ? 1 : 0) {}
    ~DList() {
        while (head != nullptr) {
            SNode* v = head;
            head = head->next;
            delete v;
        }
    }
};

void dl_insert_head (DList* l, string val);
void dl_insert_tail (DList* l, string val);
void dl_insert_before (DList* l, string key, string val);
void dl_insert_after (DList* l, string key, string val);

void dl_delete_head (DList* l);
void dl_delete_tail (DList* l);
void dl_delete_before (DList* l, string key);
void dl_delete_after (DList* l, string key);
void dl_delete_key (DList* l, string key);

string dl_search(DList* l, string key);
void dl_print_iter(DList* l);
void dl_print_rec(DList* l);