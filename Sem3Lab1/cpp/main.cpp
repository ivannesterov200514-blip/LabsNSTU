#include "array.h"
#include "queue.h"
#include "stack.h"
#include "dlist.h"
#include "ulist.h"
#include "avltree.h"

#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <cstring>
#include <cctype>

struct Db {
    map<string, Arr*> arrs;
    map<string, UList*> uls;
    map<string, DList*> dls;
    map<string, Stack*> sts;
    map<string, Queue*> qs;
    map<string, AVLTree*> trs;

    map<string, char> types;

    ~Db() {
        for (auto& p : arrs) delete p.second;
        for (auto& p : uls) delete p.second;
        for (auto& p : dls) delete p.second;
        for (auto& p : sts) delete p.second;
        for (auto& p : qs) delete p.second;
        for (auto& p : trs) delete p.second;
    }
};

template <class T>
static T* find_cont(map<string, T*>& m, const string& name) {
    auto it = m.find(name);
    if (it == m.end()) {
        cout << "Ошибка: Контейнер " << name << " не найден\n";
        return nullptr;
    }
    return it->second;
}

template <class T>
static T* get_or_create(Db& db, map<string, T*>& m, const string& name, char type) {
    auto tp = db.types.find(name);
    if (tp != db.types.end() && tp->second != type) {
        cout << "Ошибка: Имя " << name << " уже занято другой структурой\n";
        return nullptr;
    }
    auto it = m.find(name);
    if (it != m.end()) return it->second;
    T* c = new T();
    m[name] = c;
    db.types[name] = type;
    return c;
}

static bool to_int(const string& s, int& x) {
    bool ok = false;
    try {
        size_t pos = 0;
        x = stoi(s, &pos);
        ok = (pos == s.size());
    } catch (...) {}
    if (!ok) cout << "Ошибка: Индекс должен быть числом\n";
    return ok;
}

static bool to_key(const string& s, int& x) {
    bool ok = false;
    try {
        size_t pos = 0;
        x = stoi(s, &pos);
        ok = (pos == s.size());
    } catch (...) {}
    if (!ok) cout << "Ошибка: Ключ дерева должен быть целым числом\n";
    return ok;
}

static void tree_to_stream(TNode* root, ostream& out) {
    vector<TNode*> q;
    if (root != nullptr) q.push_back(root);
    for (size_t i = 0; i < q.size(); ++i) {
        out << " " << q[i]->key;
        if (q[i]->left != nullptr) q.push_back(q[i]->left);
        if (q[i]->right != nullptr) q.push_back(q[i]->right);
    }
}

static void save_db(Db& db, const string& file) {
    ofstream out(file);
    if (!out) {
        cout << "Ошибка: Не удалось записать файл " << file << "\n";
        return;
    }
    for (auto& p : db.arrs) {
        out << "M " << p.first;
        for (int i = 0; i < p.second->size; ++i) out << " " << p.second->data[i];
        out << "\n";
    }
    for (auto& p : db.uls) {
        out << "F " << p.first;
        for (Node* cur = p.second->head; cur != nullptr; cur = cur->next) out << " " << cur->data;
        out << "\n";
    }
    for (auto& p : db.dls) {
        out << "L " << p.first;
        for (SNode* cur = p.second->head; cur != nullptr; cur = cur->next) out << " " << cur->data;
        out << "\n";
    }
    for (auto& p : db.sts) {
        out << "S " << p.first;
        for (STNode* cur = p.second->top; cur != nullptr; cur = cur->next) out << " " << cur->data;
        out << "\n";
    }
    for (auto& p : db.qs) {
        out << "Q " << p.first;
        for (QNode* cur = p.second->head; cur != nullptr; cur = cur->next) out << " " << cur->data;
        out << "\n";
    }
    for (auto& p : db.trs) {
        out << "T " << p.first;
        tree_to_stream(p.second->root, out);
        out << "\n";
    }
}

static void load_db(Db& db, const string& file) {
    ifstream in(file);
    if (!in) return;

    string line;
    while (getline(in, line)) {
        istringstream ss(line);
        string type, name, tok;
        if (!(ss >> type >> name)) continue;
        vector<string> vals;
        while (ss >> tok) vals.push_back(tok);

        if (type == "M") {
            Arr* a = get_or_create(db, db.arrs, name, 'M');
            if (a == nullptr) continue;
            for (size_t i = 0; i < vals.size(); ++i) arr_insert_tail(a, vals[i]);
        } else if (type == "F") {
            UList* l = get_or_create(db, db.uls, name, 'F');
            if (l == nullptr) continue;
            for (size_t i = 0; i < vals.size(); ++i) ul_insert_tail(l, vals[i]);
        } else if (type == "L") {
            DList* l = get_or_create(db, db.dls, name, 'L');
            if (l == nullptr) continue;
            for (size_t i = 0; i < vals.size(); ++i) dl_insert_tail(l, vals[i]);
        } else if (type == "S") {
            Stack* s = get_or_create(db, db.sts, name, 'S');
            if (s == nullptr) continue;

            for (size_t i = vals.size(); i > 0; --i) st_push(s, vals[i - 1]);
        } else if (type == "Q") {
            Queue* q = get_or_create(db, db.qs, name, 'Q');
            if (q == nullptr) continue;
            for (size_t i = 0; i < vals.size(); ++i) q_push(q, vals[i]);
        } else if (type == "T") {
            AVLTree* t = get_or_create(db, db.trs, name, 'T');
            if (t == nullptr) continue;
            for (size_t i = 0; i < vals.size(); ++i) {
                int key;
                if (to_key(vals[i], key)) t_insert(t, key);
            }
        } else {
            cout << "Ошибка: Неизвестный тип структуры в файле: " << type << "\n";
        }
    }
}

static void print_any(Db& db, const string& name) {
    auto tp = db.types.find(name);
    if (tp == db.types.end()) {
        cout << "Ошибка: Контейнер " << name << " не найден\n";
        return;
    }
    switch (tp->second) {
        case 'M': arr_print(db.arrs[name]); break;
        case 'F': ul_print_iter(db.uls[name]); break;
        case 'L': dl_print_iter(db.dls[name]); break;
        case 'S': st_print(db.sts[name]); break;
        case 'Q': q_print(db.qs[name]); break;
        case 'T': t_print_wide(db.trs[name]); break;
    }
}

enum class Cmd {
    Print,
    MCreate, MPush, MInsert, MGet, MDel, MSet, MLen,
    FCreate, FPushHead, FPushTail, FPushBefore, FPushAfter,
    FDelHead, FDelTail, FDelBefore, FDelAfter, FDel, FGet, FPrintRec,
    LCreate, LPushHead, LPushTail, LPushBefore, LPushAfter,
    LDelHead, LDelTail, LDelBefore, LDelAfter, LDel, LGet, LPrintRec,
    SCreate, SPush, SPop,
    QCreate, QPush, QPop,
    TCreate, TInsert, TDel, TGet
};

struct CmdInfo {
    Cmd cmd;
    size_t argc;
    bool changes;
};

static const CmdInfo* find_cmd(const string& name) {
    static const map<string, CmdInfo> table = {
        {"PRINT", {Cmd::Print, 2, false}},

        {"MCREATE", {Cmd::MCreate, 2, true}},
        {"MPUSH", {Cmd::MPush, 3, true}},
        {"MINSERT", {Cmd::MInsert, 4, true}},
        {"MGET", {Cmd::MGet, 3, false}},
        {"MDEL", {Cmd::MDel, 3, true}},
        {"MSET", {Cmd::MSet, 4, true}},
        {"MLEN", {Cmd::MLen, 2, false}},

        {"FCREATE", {Cmd::FCreate, 2, true}},
        {"FPUSHHEAD", {Cmd::FPushHead, 3, true}},
        {"FPUSHTAIL", {Cmd::FPushTail, 3, true}},
        {"FPUSHBEFORE", {Cmd::FPushBefore, 4, true}},
        {"FPUSHAFTER", {Cmd::FPushAfter, 4, true}},
        {"FDELHEAD", {Cmd::FDelHead, 2, true}},
        {"FDELTAIL", {Cmd::FDelTail, 2, true}},
        {"FDELBEFORE", {Cmd::FDelBefore, 3, true}},
        {"FDELAFTER", {Cmd::FDelAfter, 3, true}},
        {"FDEL", {Cmd::FDel, 3, true}},
        {"FGET", {Cmd::FGet, 3, false}},
        {"FPRINTREC", {Cmd::FPrintRec, 2, false}},

        {"LCREATE", {Cmd::LCreate, 2, true}},
        {"LPUSHHEAD", {Cmd::LPushHead, 3, true}},
        {"LPUSHTAIL", {Cmd::LPushTail, 3, true}},
        {"LPUSHBEFORE", {Cmd::LPushBefore, 4, true}},
        {"LPUSHAFTER", {Cmd::LPushAfter, 4, true}},
        {"LDELHEAD", {Cmd::LDelHead, 2, true}},
        {"LDELTAIL", {Cmd::LDelTail, 2, true}},
        {"LDELBEFORE", {Cmd::LDelBefore, 3, true}},
        {"LDELAFTER", {Cmd::LDelAfter, 3, true}},
        {"LDEL", {Cmd::LDel, 3, true}},
        {"LGET", {Cmd::LGet, 3, false}},
        {"LPRINTREC", {Cmd::LPrintRec, 2, false}},

        {"SCREATE", {Cmd::SCreate, 2, true}},
        {"SPUSH", {Cmd::SPush, 3, true}},
        {"SPOP", {Cmd::SPop, 2, true}},

        {"QCREATE", {Cmd::QCreate, 2, true}},
        {"QPUSH", {Cmd::QPush, 3, true}},
        {"QPOP", {Cmd::QPop, 2, true}},

        {"TCREATE", {Cmd::TCreate, 2, true}},
        {"TINSERT", {Cmd::TInsert, 3, true}},
        {"TDEL", {Cmd::TDel, 3, true}},
        {"TGET", {Cmd::TGet, 3, false}},
        {"ISMEMBER", {Cmd::TGet, 3, false}},
    };
    auto it = table.find(name);
    if (it == table.end()) return nullptr;
    return &it->second;
}

static void run(Db& db, Cmd cmd, const vector<string>& t) {
    switch (cmd) {

        case Cmd::Print:
            print_any(db, t[1]);
            break;

        case Cmd::MCreate:
            get_or_create(db, db.arrs, t[1], 'M');
            break;
        case Cmd::MPush: {
            Arr* a = get_or_create(db, db.arrs, t[1], 'M');
            if (a) arr_insert_tail(a, t[2]);
            break;
        }
        case Cmd::MInsert: {
            int idx;
            Arr* a = find_cont(db.arrs, t[1]);
            if (a && to_int(t[2], idx)) arr_insert_idx(a, t[3], idx);
            break;
        }
        case Cmd::MGet: {
            int idx;
            Arr* a = find_cont(db.arrs, t[1]);
            if (a && to_int(t[2], idx)) {
                string v = arr_search(a, idx);
                if (idx >= 0 && idx < arr_getsz(a)) cout << v << endl;
            }
            break;
        }
        case Cmd::MDel: {
            int idx;
            Arr* a = find_cont(db.arrs, t[1]);
            if (a && to_int(t[2], idx)) arr_delete_idx(a, idx);
            break;
        }
        case Cmd::MSet: {
            int idx;
            Arr* a = find_cont(db.arrs, t[1]);
            if (a && to_int(t[2], idx)) arr_change_idx(a, t[3], idx);
            break;
        }
        case Cmd::MLen: {
            Arr* a = find_cont(db.arrs, t[1]);
            if (a) cout << arr_getsz(a) << endl;
            break;
        }

        case Cmd::FCreate:
            get_or_create(db, db.uls, t[1], 'F');
            break;
        case Cmd::FPushHead: {
            UList* l = get_or_create(db, db.uls, t[1], 'F');
            if (l) ul_insert_head(l, t[2]);
            break;
        }
        case Cmd::FPushTail: {
            UList* l = get_or_create(db, db.uls, t[1], 'F');
            if (l) ul_insert_tail(l, t[2]);
            break;
        }
        case Cmd::FPushBefore: {
            UList* l = find_cont(db.uls, t[1]);
            if (l) ul_insert_before(l, t[2], t[3]);
            break;
        }
        case Cmd::FPushAfter: {
            UList* l = find_cont(db.uls, t[1]);
            if (l) ul_insert_after(l, t[2], t[3]);
            break;
        }
        case Cmd::FDelHead: {
            UList* l = find_cont(db.uls, t[1]);
            if (l) ul_delete_head(l);
            break;
        }
        case Cmd::FDelTail: {
            UList* l = find_cont(db.uls, t[1]);
            if (l) ul_delete_tail(l);
            break;
        }
        case Cmd::FDelBefore: {
            UList* l = find_cont(db.uls, t[1]);
            if (l) ul_delete_before(l, t[2]);
            break;
        }
        case Cmd::FDelAfter: {
            UList* l = find_cont(db.uls, t[1]);
            if (l) ul_delete_after(l, t[2]);
            break;
        }
        case Cmd::FDel: {
            UList* l = find_cont(db.uls, t[1]);
            if (l) ul_delete_key(l, t[2]);
            break;
        }
        case Cmd::FGet: {
            UList* l = find_cont(db.uls, t[1]);
            if (l) ul_search(l, t[2]);
            break;
        }
        case Cmd::FPrintRec: {
            UList* l = find_cont(db.uls, t[1]);
            if (l) ul_print_rec(l);
            break;
        }

        case Cmd::LCreate:
            get_or_create(db, db.dls, t[1], 'L');
            break;
        case Cmd::LPushHead: {
            DList* l = get_or_create(db, db.dls, t[1], 'L');
            if (l) dl_insert_head(l, t[2]);
            break;
        }
        case Cmd::LPushTail: {
            DList* l = get_or_create(db, db.dls, t[1], 'L');
            if (l) dl_insert_tail(l, t[2]);
            break;
        }
        case Cmd::LPushBefore: {
            DList* l = find_cont(db.dls, t[1]);
            if (l) dl_insert_before(l, t[2], t[3]);
            break;
        }
        case Cmd::LPushAfter: {
            DList* l = find_cont(db.dls, t[1]);
            if (l) dl_insert_after(l, t[2], t[3]);
            break;
        }
        case Cmd::LDelHead: {
            DList* l = find_cont(db.dls, t[1]);
            if (l) dl_delete_head(l);
            break;
        }
        case Cmd::LDelTail: {
            DList* l = find_cont(db.dls, t[1]);
            if (l) dl_delete_tail(l);
            break;
        }
        case Cmd::LDelBefore: {
            DList* l = find_cont(db.dls, t[1]);
            if (l) dl_delete_before(l, t[2]);
            break;
        }
        case Cmd::LDelAfter: {
            DList* l = find_cont(db.dls, t[1]);
            if (l) dl_delete_after(l, t[2]);
            break;
        }
        case Cmd::LDel: {
            DList* l = find_cont(db.dls, t[1]);
            if (l) dl_delete_key(l, t[2]);
            break;
        }
        case Cmd::LGet: {
            DList* l = find_cont(db.dls, t[1]);
            if (l) dl_search(l, t[2]);
            break;
        }
        case Cmd::LPrintRec: {
            DList* l = find_cont(db.dls, t[1]);
            if (l) dl_print_rec(l);
            break;
        }

        case Cmd::SCreate:
            get_or_create(db, db.sts, t[1], 'S');
            break;
        case Cmd::SPush: {
            Stack* s = get_or_create(db, db.sts, t[1], 'S');
            if (s) {
                st_push(s, t[2]);
                cout << t[2] << endl;
            }
            break;
        }
        case Cmd::SPop: {
            Stack* s = find_cont(db.sts, t[1]);
            if (s) st_pop(s);
            break;
        }

        case Cmd::QCreate:
            get_or_create(db, db.qs, t[1], 'Q');
            break;
        case Cmd::QPush: {
            Queue* q = get_or_create(db, db.qs, t[1], 'Q');
            if (q) {
                q_push(q, t[2]);
                cout << t[2] << endl;
            }
            break;
        }
        case Cmd::QPop: {
            Queue* q = find_cont(db.qs, t[1]);
            if (q) q_pop(q);
            break;
        }

        case Cmd::TCreate:
            get_or_create(db, db.trs, t[1], 'T');
            break;
        case Cmd::TInsert: {
            AVLTree* tr = get_or_create(db, db.trs, t[1], 'T');
            int key;
            if (tr && to_key(t[2], key)) t_insert(tr, key);
            break;
        }
        case Cmd::TDel: {
            AVLTree* tr = find_cont(db.trs, t[1]);
            int key;
            if (tr && to_key(t[2], key)) t_delete(tr, key);
            break;
        }
        case Cmd::TGet: {
            AVLTree* tr = find_cont(db.trs, t[1]);
            int key;
            if (tr && to_key(t[2], key)) cout << (t_search(tr, key) ? "TRUE" : "FALSE") << endl;
            break;
        }
    }
}

int main(int argc, char* argv[]) {

    string file, query;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) file = argv[++i];
        else if (strcmp(argv[i], "--query") == 0 && i + 1 < argc) query = argv[++i];
    }
    if (file.empty() || query.empty()) {
        cout << "Использование: ./dbms --file file.data --query 'КОМАНДА имя [аргументы]'\n";
        return 1;
    }

    vector<string> t;
    istringstream ss(query);
    string tok;
    while (ss >> tok) t.push_back(tok);
    if (t.empty()) {
        cout << "Ошибка: Пустой запрос\n";
        return 1;
    }

    for (char& c : t[0]) c = toupper((unsigned char)c);

    const CmdInfo* info = find_cmd(t[0]);
    if (info == nullptr) {
        cout << "Ошибка: Неизвестная команда " << t[0] << "\n";
        return 1;
    }
    if (t.size() != info->argc) {
        cout << "Ошибка: Неверное число аргументов для " << t[0] << "\n";
        return 1;
    }

    Db db;
    load_db(db, file);
    run(db, info->cmd, t);

    if (info->changes) save_db(db, file);

    return 0;
}