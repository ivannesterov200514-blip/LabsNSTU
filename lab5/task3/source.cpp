#include "source.h"

using namespace std;

Command getcom(const string& s) {
    if (s == "CREATE_PLANE") return Command::CREATE_PLANE;
    if (s == "PLANES_FOR_TOWN") return Command::PLANES_FOR_TOWN;
    if (s == "TOWNS_FOR_PLANE") return Command::TOWNS_FOR_PLANE;
    if (s == "PLANES") return Command::PLANES;
    return Command::INVALID;
}

void createplane(Schedule& s, string name, vector<string> towns) {
    if (s.planes.count(name)) {
        cout << "Ошибка: Самолёт с именем " << name << " уже создан\n";
        return;
    }
    if (towns.size() < 2) {
        cout << "Ошибка: Самолёт не может быть создан с одной остановкой\n";
        return;
    }

    set<string> unq(towns.begin(), towns.end());
    if (unq.size() != towns.size()) {
        cout << "Ошибка: Самолёт не может быть создан с одинаковыми остановками\n";
        return;
    }

    Plane p;
    p.name = name;
    p.towns = towns;
    s.planes[name] = p;

    for (auto t : towns) {
        s.townplanes[t].insert(name);
    }
    cout << "Самолёт " << name << " создан\n";
}

void planefortown(const Schedule& s, string town) {
    auto t = s.townplanes.find(town);
    if (t == s.townplanes.end()) {
        cout << "Ошибка: Город " << town << " не найден\n";
        return;
    }

    cout << "Самолёты в городе " << town << ": ";
    bool first = true;
    for (auto plane : t -> second) {
        if (!first) cout << ", ";
        cout << plane;
        first = false;
    }
    cout << "\n";
}

void townsforplane(const Schedule& s, string planename) {
    auto x = s.planes.find(planename);
    if (x == s.planes.end()) {
        cout << "Ошибка: Самолёт " << planename << " не найден\n";
        return;
    }

    cout << "Остановки самолёта " << planename << ":\n";
    for (auto town : x->second.towns) {
        cout << "Остановка " << town << ": ";

        auto townit = s.townplanes.find(town);
        bool found = false;
        bool first = true;

        if (townit != s.townplanes.end()) {
            for (auto p : townit -> second) {
                if (p != planename) {
                    if (!first) cout << ", ";
                    cout << p;
                    first = false;
                    found = true;
                }
            }
        }
        if (!found) cout << "->";
        cout << "\n";
    }
}

void planes(const Schedule& s) {
    if (s.planes.empty()) {
        cout << "Ошибка: Самолёты не найдены\n";
        return;
    }

    for (auto pair : s.planes) {
        cout << "Самолёт " << pair.second.name << ":";
        for (auto town : pair.second.towns) {
            cout << " " << town;
        }
        cout << "\n";
    }
}