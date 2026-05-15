#include "source.h"

using namespace std;

Location parsecode(const char* code) {
    Location loc;
    loc.zone = code[0];
    loc.stel = (code[1] - '0') * 10 + (code[2] - '0');
    loc.sec = code[3] - '0';
    loc.shelf = code[4] - '0';
    return loc;
}

bool isvalidloc(const Location& loc) {
    bool zoneok;
    zoneok = (loc.zone == 'A' || loc.zone == 'B' || loc.zone == 'C');
    if (!zoneok) {
        cout << "\nОшибка ввода, зоны A или B или C.\n";
        return false;
    }
    if (loc.stel < 1 || loc.stel > STEL) {
        cout << "\nОшибка ввода, стеллажи от 1 до 14.\n";
        return false;
    }
    if (loc.sec < 1 || loc.sec > SECTIONS) {
        cout << "\nОшибка ввода, секции от 1 до 4.\n";
        return false;
    }
    if (loc.shelf < 1 || loc.shelf > SHELVES) {
        cout << "\nОшибка ввода, полки от 1 до 8.\n";
        return false;
    }
    return true;
}

void additem(Good* sklad, int& currload, const char* name, int qt, const char* code) {
    if (currload + qt > TOTAL) {
        cout << "Ошибка: Недостаточно места на складе.\n";
        return;
    }
    if (qt <= 0 || qt > 10) {
        cout << "Ошибка: Количество должно быть > 0 и <= 10.\n";
        return;
    }
    Location loc = parsecode(code);
    if (!isvalidloc(loc)) return;

    for (int i = 0; i < TOTALLOC; ++i) {
        if (!sklad[i].isEmpty && sklad[i].loc.zone == loc.zone && sklad[i].loc.stel == loc.stel && sklad[i].loc.sec == loc.sec && sklad[i].loc.shelf == loc.shelf) {
            if (strcmp(sklad[i].name, name) != 0) {
                cout << "Ошибка: Ячейка " << code << " занята товаром " << sklad[i].name << "\n";
                return;
            }
            if (sklad[i].quan + qt > 10) {
                cout << "Ошибка: Превышена вместимость ячейки (максимум 10)\n";
                return;
            }
            sklad[i].quan += qt;
            currload += qt;
            cout << "Обновлено: " << name << " теперь " << sklad[i].quan << " шт.\n";
            return;
        }
    }
    for (int i = 0; i < TOTALLOC; ++i) {
        if (sklad[i].isEmpty) {
            strcpy(sklad[i].name, name);
            sklad[i].quan = qt;
            sklad[i].loc = loc;
            sklad[i].isEmpty = false;
            currload += qt;
            cout << "Добавлено " << qt << " " << name << " в " << code << "\n";
            return;
        }
    }
    
    cout << "Ошибка: Все ячейки заняты" << "\n";
}

void removeitem(Good* sklad, int& currload, const char* name, int qt, const char* code) {
    if (qt <= 0 || qt > 10) {
        cout << "Ошибка: Количество должно быть > 0 и <= 10.\n";
        return;
    }
    Location loc = parsecode(code);
    if (!isvalidloc(loc)) return;

    for (int i = 0; i < TOTALLOC; ++i) {
        if (!sklad[i].isEmpty && sklad[i].loc.zone == loc.zone && sklad[i].loc.stel == loc.stel && sklad[i].loc.sec == loc.sec && sklad[i].loc.shelf == loc.shelf && strcmp(sklad[i].name, name) == 0) {
            if (sklad[i].quan < qt) {
                cout << "Ошибка: Недостаточно товаров для удаления. В ячейке: " << sklad[i].quan << "\n";
                return;
            }
                        
            sklad[i].quan -= qt;
            currload -= qt;
            cout << "Удалено " << qt << " " << sklad[i].name << " (остаток:" << sklad[i].quan << ")\n";
            return;
        }
    }  
    
    cout << "Ошибка: Товар " << name << "не найден в ячейке " << code << "\n";
    return;
}

void info(Good* sklad, int currload) {
    double loadperc;
    loadperc = (double)currload / TOTAL * 100;
    cout << "Загруженность склада: " << fixed << setprecision(2) << loadperc << " %\n";

    int loadA = 0, loadB = 0, loadV = 0;
    int perzone = STEL * SECTIONS * SHELVES * 10;

    for (int i = 0; i < TOTALLOC; ++i) {
        if (!sklad[i].isEmpty) {
            char z = sklad[i].loc.zone;
            if (z == 'A') loadA += sklad[i].quan;
            else if (z == 'B') loadB += sklad[i].quan;
            else if (z == 'C') loadV += sklad[i].quan;
        }
    }

    cout << "Загруженность зоны A: " << fixed << setprecision(2) << (double)loadA / perzone * 100 << " %\n";
    cout << "Загруженность зоны B: " << fixed << setprecision(2) << (double)loadB / perzone * 100 << " %\n";
    cout << "Загруженность зоны C: " << fixed << setprecision(2) << (double)loadV / perzone * 100 << " %\n";

    cout << "Заполненные ячейки:\n";
    int filled = 0;
    for (int i = 0; i < TOTALLOC; ++i) {
        if (!sklad[i].isEmpty) {
            cout << sklad[i].loc.zone << sklad[i].loc.stel << (sklad[i].loc.sec < 10 ? "" : "") << sklad[i].loc.sec << sklad[i].loc.shelf << ": " << sklad[i].name << " (" << sklad[i].quan << ")\n";
            filled++;
        }
    }
    if (filled == 0) cout << "Нет заполненных ячеек\n";

    cout << "Пустые ячейки:\n";
    int empty = 0;
    for (int i = 0; i < TOTALLOC; ++i) {
        if (sklad[i].isEmpty) {
            cout << sklad[i].loc.zone << sklad[i].loc.stel << (sklad[i].loc.sec < 10 ? "" : "") << sklad[i].loc.sec << sklad[i].loc.shelf << " ";
            empty++;
        }
    }
    if (empty == 0) cout << "Нет пустых ячеек\n";
}