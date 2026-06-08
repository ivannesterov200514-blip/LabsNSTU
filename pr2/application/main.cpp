#include "powmod.h"
#include "getd.h"
#include "invmod.h"
#include "El_Gamal.h"
#include "cep_drob.h"
#include <limits>
#include <map>

// Команды
enum class MenuOption {
    POWMOD,
    GETD,
    INVMOD,
    ELGAMAL,
    CEP,
    EXIT,
    UNKNOWN
};

// Приведение ввода в нижний регистр
string tolower(string str) {
    for (int i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

int main() {
    setlocale(LC_ALL, ".UTF8");
    map<string, MenuOption> cmdMap;
    cmdMap["powmod"] = MenuOption::POWMOD;
    cmdMap["getd"] = MenuOption::GETD;
    cmdMap["invmod"] = MenuOption::INVMOD;
    cmdMap["elgamal"] = MenuOption::ELGAMAL;
    cmdMap["cep"] = MenuOption::CEP;
    cmdMap["exit"] = MenuOption::EXIT;
    cmdMap["quit"] = MenuOption::EXIT;

    bool running = true;

    cout << "\nКриптография--\n";
    while(running) {
        cout << "   powmod - Возведение в степень по модулю\n";
        cout << "   getd - Вычисление множителя d\n";
        cout << "   invmod - Поиск обратного элемента по модулю\n";
        cout << "   elgamal - Шифр Эль-Гамаля\n";
        cout << "   cep - Цепная дробь\n";
        cout << "   exit/quit - Выход из программы\n";

        cout << "\n>> ";
        string input;
        cin >> input;
        input = tolower(input);
        
        MenuOption curr_cmd = MenuOption::UNKNOWN;
        if (cmdMap.find(input) != cmdMap.end()) curr_cmd = cmdMap[input];

        switch(curr_cmd) {
            case MenuOption::POWMOD:
            cout << "[POWMOD] Возведение в степень по модулю.\n";
                    // TODO: добавить ввод a, b, m и вызов функции powmod(a, b, m)
                    runpowmod();
                    cout << "\n";
                    break;

                case MenuOption::GETD:
                    cout << "[GETD] Вычисление множителя d.\n";
                    rungetd();
                    cout << "\n";
                    break;

                case MenuOption::INVMOD:
                    cout << "[INVMOD] Поиск обратного элемента.\n";
                    runinvmod();
                    cout << "\n";
                    break;

                case MenuOption::ELGAMAL:
                    cout << "[ELGAMAL] Криптопротокол Эль-Гамаля.\n";
                    runElGamal();
                    cout << "\n";
                    break;

                case MenuOption::CEP:
                    cout << "[CEP] Вычисление решения цепной дроби.\n";
                    runcepdrob();
                    cout << "\n";
                    break;

                case MenuOption::EXIT:
                    cout << "Завершение.\n";
                    running = false; // Выход из цикла
                    break;

                case MenuOption::UNKNOWN:
                    // если вводим команду не из списка в меню
                    cout << "Ошибка: Неизвестная команда '" << input << "\n\n";
                    break;
        }
    }
    
    return 0;
}