#include "avltree.h"
#include <algorithm>

static int getheight(TNode* t) {
    return t ? t->height : 0;
}

static int getbalance(TNode* t) {
    return t ? getheight(t->left) - getheight(t->right) : 0;
}

static TNode* rotate_right (TNode* y) {
    TNode* x = y->left;
    TNode* t = x->right;
    x->right = y;
    y->left = t;
    y->height = max(getheight(y->left), getheight(y->right)) + 1;
    x->height = max(getheight(x->left), getheight(x->right)) + 1;
    return x;
}

static TNode* rotate_left (TNode* x) {
    TNode* y = x->right;
    TNode* t = y->left;
    y->left = x;
    x->right = t;
    x->height = max(getheight(x->left), getheight(x->right)) + 1;
    y->height = max(getheight(y->left), getheight(y->right)) + 1;
    return y;
}

static TNode* t_insert_node(TNode* t, int val) {
    if (t == nullptr) 
        return new TNode(val);
    if (val < t->key)
        t->left = t_insert_node(t->left, val);
    else if (val > t->key)
        t->right = t_insert_node(t->right, val);
    else
        return t; 

    t->height = 1 + max(getheight(t->left), getheight(t->right));
    int balance = getbalance(t);

    if (balance > 1 && val < t->left->key)
        return rotate_right(t);

    if (balance < -1 && val > t->right->key)
        return rotate_left(t);

    if (balance > 1 && val > t->left->key) {
        t->left = rotate_left(t->left);
        return rotate_right(t);
    }

    if (balance < -1 && val < t->right->key) {
        t->right = rotate_right(t->right);
        return rotate_left(t);
    }
    return t;
}

void t_insert(AVLTree* t, int val) {
    t->root = t_insert_node(t->root, val);
}

static TNode* min_node(TNode* t) {
    while (t->left != nullptr) {
        t = t->left;
    }
    return t;
}

static TNode* t_delete_node(TNode* t, int val) {
    if (t == nullptr) return t;

    if (val < t->key) {
        t->left = t_delete_node(t->left, val);
    } else if (val > t->key) {
        t->right = t_delete_node(t->right, val);
    } else {
        if (t->left == nullptr || t->right == nullptr) {
            TNode* c = t->left ? t->left : t->right;
            delete t;
            return c;
        }
        TNode* m = min_node(t->right);
        t->key = m->key;
        t->right = t_delete_node(t->right, m->key);
    }

    t->height = 1 + max(getheight(t->left), getheight(t->right));
    int balance = getbalance(t);

    if (balance > 1 && getbalance(t->left) >= 0)
        return rotate_right(t);

    if (balance > 1 && getbalance(t->left) < 0) {
        t->left = rotate_left(t->left);
        return rotate_right(t);
    }

    if (balance < -1 && getbalance(t->right) <= 0)
        return rotate_left(t);

    if (balance < -1 && getbalance(t->right) > 0) {
        t->right = rotate_right(t->right);
        return rotate_left(t);
    }
    return t;
}

void t_delete(AVLTree* t, int val) {
    if (!t_search(t, val)) {
        cout << "Ошибка: Не найдено\n";
        return;
    }
    t->root = t_delete_node(t->root, val);
}

static bool t_search_node(TNode* t, int val) {
    if (t == nullptr) return false;
    if (val == t->key) return true;
    if (val < t->key) return t_search_node(t->left, val);
    return t_search_node(t->right, val);
}

bool t_search(AVLTree* t, int val) {
    return t_search_node(t->root, val);
}

static void print_level(TNode* t, int level) {
    if (t == nullptr) return;
    if (level == 1) {
        cout << t->key << " ";
        return;
    }
    print_level(t->left, level - 1);
    print_level(t->right, level - 1);
}

void t_print_wide(AVLTree* t) {
    if (t->root == nullptr) {
        cout << "Дерево пусто\n";
        return;
    }
    int h = getheight(t->root);
    for (int i = 1; i <= h; ++i) {
        cout << "Уровень " << i << ": ";
        print_level(t->root, i);
        cout << endl;
    }
}

static void t_free(TNode* t) {
    if (t == nullptr) return;
    t_free(t->left);
    t_free(t->right);
    delete t;
}

AVLTree::~AVLTree() {
    t_free(root);
}