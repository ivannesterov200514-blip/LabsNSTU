<<<<<<< HEAD
#include "task2.h"

int main() {
    setlocale(LC_ALL, "rus");
    int64_t c, m;
    cout << "Введите основание и модуль: ";
    cin >> c >> m;
    cout << "\n" << c << " * d mod " << m << " = 1\nРешаем через u и v\n";
    cout << "\nr - остаток от деления;\nd - коэффициент при " << c << "; v - коэффициент при " << m << "; q - целая часть от деления\n";
    int64_t d = check(c, m);
    if (d != -1) {
        cout << "d = " << d << "\n";
        cout << "Проверка: " << c << " * " << d << " mod " << m << " = " << (c * d) % m << "\n";
    }
    else cout << "Проверка: " << c << " * " << d << " mod " << m << " = " << (c * (d % m + m) % m) % m << "\n";
    return 0;
=======
#include "task2.h"

int main() {
    setlocale(LC_ALL, "rus");
    int64_t c, m;
    cout << "Введите основание и модуль: ";
    cin >> c >> m;
    cout << "\n" << c << " * d mod " << m << " = 1\nРешаем через u и v\n";
    cout << "\nr - остаток от деления;\nd - коэффициент при " << c << "; v - коэффициент при " << m << "; q - целая часть от деления\n";
    int64_t d = check(c, m);
    if (d != -1) {
        cout << "d = " << d << "\n";
        cout << "Проверка: " << c << " * " << d << " mod " << m << " = " << (c * d) % m << "\n";
    }
    else cout << "Проверка: " << c << " * " << d << " mod " << m << " = " << (c * (d % m + m) % m) % m << "\n";
    return 0;
>>>>>>> 05ec7888d741d95755c8845f0090f27b7e6d8528
}