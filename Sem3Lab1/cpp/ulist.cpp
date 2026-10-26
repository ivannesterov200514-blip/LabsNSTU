#include "ulist.h"

static Node* ul_find(UList* l, string key) {
    Node* cur = l->head;
    while (cur != nullptr && cur->data != key) {
        cur = cur->next;
    }
    return cur;
}

void ul_insert_head (UList* l, string val) {
    Node* n = new Node{val, l->head};
    l->head = n;
    l->sz++;
}

void ul_insert_tail (UList* l, string val) {
    Node* n = new Node{val, nullptr};
    if (l->head == nullptr) {
        l->head = n;
        l->sz++;
        return;
    }
    Node* cur = l->head;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    cur->next = n;
    l->sz++;
}

void ul_insert_before (UList* l, string key, string val) {
    if (l->head == nullptr) {
        cout << "Ошибка: Не найдено\n";
        return;
    }
    if (l->head->data == key) {
        ul_insert_head(l, val);
        return;
    }
    Node* cur = l->head;
    while (cur->next != nullptr && cur->next->data != key) {
        cur = cur->next;
    }
    if (cur->next == nullptr) {
        cout << "Ошибка: Не найдено\n";
        return;
    }
    Node* n = new Node{val, cur->next};
    cur->next = n;
    l->sz++;
}

void ul_insert_after (UList* l, string key, string val) {
    Node* cur = ul_find(l, key);
    if (cur == nullptr) {
        cout << "Ошибка: Не найдено\n";
        return;
    }
    Node* n = new Node{val, cur->next};
    cur->next = n;
    l->sz++;
}

void ul_delete_head (UList* l) {
    if (l->head == nullptr) {
        cout << "Ошибка: Список пуст\n";
        return;
    }
    if (l->head->next == nullptr) {
        cout << "Последний узел списка удален.\n";
    }
    Node* v = l->head;
    l->head = v->next;
    delete v;
    l->sz--;
}

void ul_delete_tail (UList* l) {
    if (l->head == nullptr) {
        cout << "Ошибка: Список пуст\n";
        return;
    }
    if (l->head->next == nullptr) {
        delete l->head;
        l->head = nullptr;
        l->sz--;
        cout << "Последний узел списка удален.\n";
        return;
    }
    Node* cur = l->head;
    while (cur->next->next != nullptr) {
        cur = cur->next;
    }
    delete cur->next;
    cur->next = nullptr;
    l->sz--;
}

void ul_delete_before (UList* l, string key) {
    if (l->head == nullptr || l->head->next == nullptr) {
        cout << "Ошибка: Не найдено\n";
        return;
    }
    if (l->head->data == key) {
        cout << "Ошибка: Перед элементом ничего нет\n";
        return;
    }
    if (l->head->next->data == key) {
        Node* v = l->head;
        l->head = v->next;
        delete v;
        l->sz--;
        return;
    }
    Node* cur = l->head;
    while (cur->next->next != nullptr && cur->next->next->data != key) {
        cur = cur->next;
    }
    if (cur->next->next == nullptr) {
        cout << "Ошибка: Не найдено\n";
        return;
    }
    Node* v = cur->next;
    cur->next = v->next;
    delete v;
    l->sz--;
}

void ul_delete_after (UList* l, string key) {
    Node* cur = ul_find(l, key);
    if (cur == nullptr) {
        cout << "Ошибка: Не найдено\n";
        return;
    }
    if (cur->next == nullptr) {
        cout << "Ошибка: После элемента ничего нет\n";
        return;
    }
    Node* v = cur->next;
    cur->next = v->next;
    delete v;
    l->sz--;
}

void ul_delete_key (UList* l, string key) {
    if (l->head == nullptr) {
        cout << "Ошибка: Не найдено\n";
        return;
    }
    if (l->head->data == key) {
        if (l->head->next == nullptr) {
            cout << "Последний узел списка удален.\n";
        }
        Node* v = l->head;
        l->head = v->next;
        delete v;
        l->sz--;
        return;
    }
    Node* cur = l->head;
    while (cur->next != nullptr && cur->next->data != key) {
        cur = cur->next;
    }
    if (cur->next == nullptr) {
        cout << "Ошибка: Не найдено\n";
        return;
    }
    Node* v = cur->next;
    cur->next = v->next;
    delete v;
    l->sz--;
}

string ul_search(UList* l, string key) {
    Node* cur = ul_find(l, key);
    if (cur == nullptr) {
        cout << "Ошибка: Не найдено\n";
        return "";
    }
    cout << cur->data << endl;
    return cur->data;
}

void ul_print_iter(UList* l) {
    if (l->head == nullptr) {
        cout << "Список пуст\n";
        return;
    }
    Node* cur = l->head;
    while (cur != nullptr) {
        cout << cur->data << " -> ";
        cur = cur->next;
    }
    cout << "nullptr\n";
}

static void printrecurs(Node* c) {
    if (c == nullptr) {
        cout << "nullptr\n";
        return;
    }
    cout << c->data << " -> ";
    printrecurs(c->next);
}

void ul_print_rec (UList* l) {
    if (l->head == nullptr) {
        cout << "Список пуст\n";
        return;
    }
    printrecurs(l->head);
}
