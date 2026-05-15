#include "source.h"

using namespace std;

int main() {
    setlocale(LC_ALL, ".UTF8");

    Good sklad[TOTALLOC];

    int index = 0;
    char zones[] = {'A', 'B', 'C'};  // Латинские буквы
    
    for (int z = 0; z < ZONES; ++z) {
        for (int s = 1; s <= STEL; ++s) {
            for (int sec = 1; sec <= SECTIONS; ++sec) {
                for (int sh = 1; sh <= SHELVES; ++sh) {
                    sklad[index].loc.zone = zones[z];
                    sklad[index].loc.stel = s;
                    sklad[index].loc.sec = sec;
                    sklad[index].loc.shelf = sh;
                    sklad[index].isEmpty = true;
                    sklad[index].quan = 0;
                    index++;
                }
            }
        }
    }

    int currload = 0;
    char command[20];

    while (true) {
        cout << "\n>>>";
        cin >> command;

        if (strcmp(command, "ADD") == 0 || strcmp(command, "add") == 0) {
            char name[50];
            int qt;
            char code[10];
            cin >> name >> qt >> code;
            additem(sklad, currload, name, qt, code);
        }
        else if (strcmp(command, "REMOVE") == 0 || strcmp(command, "remove") == 0) {
            char name[50];
            int qt;
            char code[10];
            cin >> name >> qt >> code;
            removeitem(sklad, currload, name, qt, code);
        }
        else if (strcmp(command, "INFO") == 0 || strcmp(command, "info") == 0) info(sklad, currload);
        else cout << "Неизвестная команда.";
    }
    return 0;
}