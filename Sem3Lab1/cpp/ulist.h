#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Node {
    string data;
    Node* next;
    Node(string val, Node* t) : data(val), next(t) {}
};

struct UList {
    Node* head;
    int sz;
    UList(Node* n = nullptr) : head(n), sz(n ? 1 : 0) {}
    ~UList() {
        while (head != nullptr) {
            Node* v = head;
            head = head->next;
            delete v;
        }
    }
};

void ul_insert_head (UList* l, string val);
void ul_insert_tail (UList* l, string val);
void ul_insert_before (UList* l, string key, string val);
void ul_insert_after (UList* l, string key, string val);

void ul_delete_head (UList* l);
void ul_delete_tail (UList* l);
void ul_delete_before (UList* l, string key);
void ul_delete_after (UList* l, string key);
void ul_delete_key (UList* l, string key);

string ul_search(UList* l, string key);
void ul_print_iter(UList* l);
void ul_print_rec(UList* l);