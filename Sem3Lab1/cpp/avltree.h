#pragma once
#include <iostream>
#include <string>

using namespace std;

struct TNode {
    int key;
    TNode* left;
    TNode* right;
    int height;
    TNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

struct AVLTree {
    TNode* root;
    AVLTree(TNode* n = nullptr) : root(n) {}
    ~AVLTree();
};

void t_insert(AVLTree* t, int val);
void t_delete(AVLTree* t, int val);
bool t_search(AVLTree* t, int val);
void t_print_wide(AVLTree* t);