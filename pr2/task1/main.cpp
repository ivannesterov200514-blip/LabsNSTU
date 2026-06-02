#include "powmod.h"

int main() {
    setlocale(LC_ALL, ".UTF8");
    int64_t base, power, modulo;

    cout << "Введите основание, степень и модуль: ";
    cin >> base >> power >> modulo;

    cout << base << "^" << power << " mod " << modulo << "\n\n";

    int64_t result1 = algferma(base, power, modulo);
    int64_t result2 = algbin(base, power, modulo);

    cout << "Сравнение результатов:\n";
    cout << "Метод 1: " << result1 << "\n";
    cout << "Метод 2: " << result2 << "\n";
    if (result1 == result2) {
        cout << "Результаты совпадают\n";
    }
    else {
        cout << "Результаты не совпадают\n";
    }

    return 0;
}
