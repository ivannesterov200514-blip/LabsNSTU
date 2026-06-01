<<<<<<< HEAD
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <fstream>
#include "El_Gamal.h"

using namespace std;

int main() {
    setlocale(LC_ALL, ".UTF8");
    uint64_t x; 
    uint64_t p, g;
    cout << "---ШИФР ЭЛЬ ГАМАЛЯ---\n\n";
    cout << "Введите простое число p (должно быть > 10000 для поддержки кириллицы): ";
    while (true) {
        cin >> p;
        if (p <= 10000)
            cout << "Ошибка: p слишком мало. Для русских букв и знаков препинания нужно p > 10000. Введите заново: "; 
        else if (issimple(p) == false) 
            cout << "Ошибка: p не простое число. Введите заново: "; 
        else break;
    }

    cout << "Введите число g (2 ≤ g < " << p << "): ";
    while (true) {
        cin >> g;
        if (g < 2) 
            cout << "Ошибка: g должно быть >= 2. Введите заново: \n";
        else if (g >= p) 
            cout << "Ошибка: g должно быть < p (" << p << "). Введите заново: \n";
        else break;
    }

    vector<uint64_t> key = keygen(p, g, x);
    
    string message;
    char useFile;
    cout << "\nПрочитать сообщение из файла? (y/n): ";
    cin >> useFile;
    
    if (useFile == 'y' || useFile == 'Y') {
        string fname;
        cout << "Введите имя файла: ";
        cin >> fname;
        ifstream inFile(fname);
        if (!inFile.is_open()) {
            cerr << "Ошибка: файл '" << fname << "' не найден!\n";
            return 1;
        }
        // Читаем весь файл в строку (сохраняет UTF-8 байты, включая \n)
        message.assign(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>());
        inFile.close();
        cout << "Текст из файла загружен (" << message.size() << " байт).\n";
    } else {
        cin.ignore(); // очистка буфера после cin
        cout << "Введите сообщение: ";
        getline(cin, message);
    }

    if (message.empty()) {
        cout << "Ошибка: пустое сообщение\n";
        return 1;
    }

    vector<uint32_t> codes = to_codes(message);
    
    // все коды должны быть < p
    for (uint32_t cp : codes) {
        if (cp >= p) {
            cout << "Ошибка: код символа " << cp << " >= p (" << p << ")\n";
            cout << "Используйте большее простое число p!\n";
            return 1;
        }
    }

    // Шифруем каждый символ отдельно
    cout << "\n--ШИФРОВАНИЕ--\n\n";
    vector<pair<uint64_t, uint64_t>> ctext;
    for (size_t i = 0; i < codes.size(); ++i) {
        ctext.push_back(crypt(static_cast<uint64_t>(codes[i]), key));
    }

    cout << "Шифротекст:\n";
    for (size_t i = 0; i < ctext.size(); ++i) {
        cout << "( C1 = " << ctext[i].first << ", C2 = " << ctext[i].second << " )\n";
    }
    cout << "\n";

    // Расшифровываем каждый символ
    cout << "\n--РАСШИФРОВКА--\n\n";
    vector<uint32_t> dec_codes;
    for (size_t i = 0; i < ctext.size(); ++i) {
        uint64_t val = decrypt(ctext[i], x, key);
        dec_codes.push_back(static_cast<uint32_t>(val));
    }
    string decrypted = to_text(dec_codes);
    cout << "Расшифрованный текст: " << decrypted << "\n\n";
    
    string out;
    cin.ignore();
    cout << "\nВведите имя файла для сохранения шифротекста (или Enter чтобы пропустить): ";
    getline(cin, out);

    // Запись в файл шифротекста
    if (!out.empty()) {
        ofstream outFile(out);
        if (!outFile.is_open()) {
            cerr << "Ошибка: не удалось создать файл '" << out << "'!\n";
            return 1;
        }

        for (const auto& p : ctext) {
            outFile << p.first << " " << p.second << "\n";
        }
        outFile.close();
        cout << "Шифротекст сохранён в '" << out << "'\n";
    }

    cout << "Проверка на соответствие\n\n";

    cout << "Исходный текст: " << message << "\n\n";
    if (decrypted == message) 
        cout << "Расшифрованный текст соответствует исходному :)\n\n";
    else 
        cout << "Ошибка: расшифрованный текст не соответствует исходному :(\n";   
    return 0;
=======
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <fstream>
#include "El_Gamal.h"

using namespace std;

int main() {
    setlocale(LC_ALL, ".UTF8");
    uint64_t x; 
    uint64_t p, g;
    cout << "---ШИФР ЭЛЬ ГАМАЛЯ---\n\n";
    cout << "Введите простое число p (должно быть > 10000 для поддержки кириллицы): ";
    while (true) {
        cin >> p;
        if (p <= 10000)
            cout << "Ошибка: p слишком мало. Для русских букв и знаков препинания нужно p > 10000. Введите заново: "; 
        else if (issimple(p) == false) 
            cout << "Ошибка: p не простое число. Введите заново: "; 
        else break;
    }

    cout << "Введите число g (2 ≤ g < " << p << "): ";
    while (true) {
        cin >> g;
        if (g < 2) 
            cout << "Ошибка: g должно быть >= 2. Введите заново: \n";
        else if (g >= p) 
            cout << "Ошибка: g должно быть < p (" << p << "). Введите заново: \n";
        else break;
    }

    vector<uint64_t> key = keygen(p, g, x);
    
    string message;
    char useFile;
    cout << "\nПрочитать сообщение из файла? (y/n): ";
    cin >> useFile;
    
    if (useFile == 'y' || useFile == 'Y') {
        string fname;
        cout << "Введите имя файла: ";
        cin >> fname;
        ifstream inFile(fname);
        if (!inFile.is_open()) {
            cerr << "Ошибка: файл '" << fname << "' не найден!\n";
            return 1;
        }
        // Читаем весь файл в строку (сохраняет UTF-8 байты, включая \n)
        message.assign(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>());
        inFile.close();
        cout << "Текст из файла загружен (" << message.size() << " байт).\n";
    } else {
        cin.ignore(); // очистка буфера после cin
        cout << "Введите сообщение: ";
        getline(cin, message);
    }

    if (message.empty()) {
        cout << "Ошибка: пустое сообщение\n";
        return 1;
    }

    vector<uint32_t> codes = to_codes(message);
    
    // все коды должны быть < p
    for (uint32_t cp : codes) {
        if (cp >= p) {
            cout << "Ошибка: код символа " << cp << " >= p (" << p << ")\n";
            cout << "Используйте большее простое число p!\n";
            return 1;
        }
    }

    // Шифруем каждый символ отдельно
    cout << "\n--ШИФРОВАНИЕ--\n\n";
    vector<pair<uint64_t, uint64_t>> ctext;
    for (size_t i = 0; i < codes.size(); ++i) {
        ctext.push_back(crypt(static_cast<uint64_t>(codes[i]), key));
    }

    cout << "Шифротекст:\n";
    for (size_t i = 0; i < ctext.size(); ++i) {
        cout << "( C1 = " << ctext[i].first << ", C2 = " << ctext[i].second << " )\n";
    }
    cout << "\n";

    // Расшифровываем каждый символ
    cout << "\n--РАСШИФРОВКА--\n\n";
    vector<uint32_t> dec_codes;
    for (size_t i = 0; i < ctext.size(); ++i) {
        uint64_t val = decrypt(ctext[i], x, key);
        dec_codes.push_back(static_cast<uint32_t>(val));
    }
    string decrypted = to_text(dec_codes);
    cout << "Расшифрованный текст: " << decrypted << "\n\n";
    
    string out;
    cin.ignore();
    cout << "\nВведите имя файла для сохранения шифротекста (или Enter чтобы пропустить): ";
    getline(cin, out);

    // Запись в файл шифротекста
    if (!out.empty()) {
        ofstream outFile(out);
        if (!outFile.is_open()) {
            cerr << "Ошибка: не удалось создать файл '" << out << "'!\n";
            return 1;
        }

        for (const auto& p : ctext) {
            outFile << p.first << " " << p.second << "\n";
        }
        outFile.close();
        cout << "Шифротекст сохранён в '" << out << "'\n";
    }

    cout << "Проверка на соответствие\n\n";

    cout << "Исходный текст: " << message << "\n\n";
    if (decrypted == message) 
        cout << "Расшифрованный текст соответствует исходному :)\n\n";
    else 
        cout << "Ошибка: расшифрованный текст не соответствует исходному :(\n";   
    return 0;
>>>>>>> 05ec7888d741d95755c8845f0090f27b7e6d8528
}