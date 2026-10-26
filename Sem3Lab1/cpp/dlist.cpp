#include "dlist.h"

static SNode* dl_find(DList* l, string key) {
    SNode* cur = l->head;
    while (cur != nullptr && cur->data != key) {
        cur = cur->next;
    }
    return cur;
}

static void dl_unlink(DList* l, SNode* v) {
    if (v->prev != nullptr) v->prev->next = v->next;
    else l->head = v->next;
    if (v->next != nullptr) v->next->prev = v->prev;
    else l->tail = v->prev;
    if (l->head == nullptr) l->tail = nullptr;
    delete v;
    l->sz--;
}

void dl_insert_head (DList* l, string val) {
    SNode* n = new SNode(val, l->head, nullptr);
    if (l->head != nullptr) l->head->prev = n;
    else l->tail = n;
    l->head = n;
    l->sz++;
}

void dl_insert_tail (DList* l, string val) {
    SNode* n = new SNode(val, nullptr, l->tail);
    if (l->tail != nullptr) l->tail->next = n;
    else l->head = n;
    l->tail = n;
    l->sz++;
}

void dl_insert_before (DList* l, string key, string val) {
    SNode* cur = dl_find(l, key);
    if (cur == nullptr) {
        cout << "Ошибка: Не найдено\n";
        return;
    }
    SNode* n = new SNode(val, cur, cur->prev);
    if (cur->prev != nullptr) cur->prev->next = n;
    else l->head = n;
    cur->prev = n;
    l->sz++;
}

void dl_insert_after (DList* l, string key, string val) {
    SNode* cur = dl_find(l, key);
    if (cur == nullptr) {
        cout << "Ошибка: Не найдено\n";
        return;
    }
    SNode* n = new SNode(val, cur->next, cur);
    if (cur->next != nullptr) cur->next->prev = n;
    cur->next = n;
    if (n->next == nullptr) l->tail = n;
    l->sz++;
}

void dl_delete_head (DList* l) {
    if (l->head == nullptr) {
        cout << "Ошибка: Список пуст\n";
        return;
    }
    if (l->head->next == nullptr) {
        cout << "Последний узел списка удален.\n";
    }
    dl_unlink(l, l->head);
}

void dl_delete_tail (DList* l) {
    if (l->tail == nullptr) {
        cout << "Ошибка: Список пуст\n";
        return;
    }
    if (l->head == l->tail) {
        cout << "Последний узел списка удален.\n";
    }
    dl_unlink(l, l->tail);
}

void dl_delete_before (DList* l, string key) {
    SNode* cur = dl_find(l, key);
    if (cur == nullptr) {
        cout << "Ошибка: Не найдено\n";
        return;
    }
    if (cur->prev == nullptr) {
        cout << "Ошибка: Перед элементом ничего нет\n";
        return;
    }
    dl_unlink(l, cur->prev);
}

void dl_delete_after (DList* l, string key) {
    SNode* cur = dl_find(l, key);
    if (cur == nullptr) {
        cout << "Ошибка: Не найдено\n";
        return;
    }
    if (cur->next == nullptr) {
        cout << "Ошибка: После элемента ничего нет\n";
        return;
    }
    dl_unlink(l, cur->next);
}

void dl_delete_key (DList* l, string key) {
    SNode* cur = dl_find(l, key);
    if (cur == nullptr) {
        cout << "Ошибка: Не найдено\n";
        return;
    }
    if (l->head->next == nullptr) {
        cout << "Последний узел списка удален.\n";
    }
    dl_unlink(l, cur);
}

string dl_search(DList* l, string key) {
    SNode* cur = dl_find(l, key);
    if (cur == nullptr) {
        cout << "Ошибка: Не найдено\n";
        return "";
    }
    cout << cur->data << endl;
    return cur->data;
}

void dl_print_iter(DList* l) {
    if (l->head == nullptr) {
        cout << "Список пуст\n";
        return;
    }
    SNode* cur = l->head;
    cout << "nullptr <-> ";
    while (cur != nullptr) {
        cout << cur->data << " <-> ";
        cur = cur->next;
    }
    cout << "nullptr\n";
}

static void printrecurs(SNode* c) {
    if (c == nullptr) {
        cout << "nullptr\n";
        return;
    }
    cout << c->data << " <-> ";
    printrecurs(c->next);
}

void dl_print_rec(DList* l) {
    if (l->head == nullptr) {
        cout << "Список пуст\n";
        return;
    }
    cout << "nullptr <-> ";
    printrecurs(l->head);
}
