#include "source.h"

int main() {
    setlocale(LC_ALL, "rus");

    Schedule schedule;
    string line;

    while (true) {
        cout << ">>> ";
        getline(cin, line);

        if (line.empty()) continue;
        
        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "CREATE_PLANE") {
            string planeName;
            int n;
            if (ss >> planeName >> n) {
                vector<string> towns(n);
                for (int i = 0; i < n; ++i) {
                    ss >> towns[i];
                }
                
                createplane(schedule, planeName, towns);
            } else {
                cout << "Ошибка: Неверный формат команды CREATE_PLANE\n";
            }

        }
        else if (command == "PLANES_FOR_TOWN") {
            string town;
            if (ss >> town) {
                planefortown(schedule, town);
            } else {
                cout << "Ошибка: Укажите город\n";
            }

        } 
        else if (command == "TOWNS_FOR_PLANE") {
            string planeName;
            if (ss >> planeName) {
                townsforplane(schedule, planeName);
            } else {
                cout << "Ошибка: Укажите имя самолета\n";
            }

        } 
        else if (command == "PLANES") {
            planes(schedule);

        } 
        else {
            cout << "Ошибка: Неизвестная команда\n";
        }
    }

    return 0;
}