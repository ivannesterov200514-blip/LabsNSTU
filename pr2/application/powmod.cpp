#include "powmod.h"

// Проверка простоты
bool issimple(int64_t n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int64_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// теорема Ферма и свойств сравнений
int64_t algferma(int64_t base, int64_t power, int64_t modulo) {
    cout << "Теорема Ферма и свойства сравнений\n";

    // Приводим основание по модулю, обрабатывая отрицательные числа
    base = (base % modulo + modulo) % modulo;

    if (issimple(modulo)) {
        cout << "Модуль " << modulo << " является простым\n";
        // Условие теоремы Ферма
        if (base != 0) {
            cout << "Условия теоремы Ферма выполнены (НОД(base, p) = 1)\n";
            cout << "a^(p-1) = 1 (mod p). Сокращаем степень по модулю (p-1)\n";

            int64_t newpow = power % (modulo - 1);
            cout << "Новая степень: " << power << " mod " << (modulo - 1) << " = " << newpow << "\n";
            power = newpow;

            if (power == 0) {
                cout << "Результат: 1\n\n";
                return 1;
            }
        }
        else {
            cout << "Основание кратно модулю. Теорема Ферма неприменима\n";
            cout << "Результат: 0\n\n";
            return 0;
        }
    }
    else {
        cout << "Модуль не является простым. Теорема Ферма неприменима\n";
        cout << "Вычисляем напрямую через свойства сравнений (a*b mod p = (a mod p * b mod p) mod p)\n";
    }

    int64_t result = 1;
    int64_t step = 1;

    for (int64_t i = 0; i < power; i++) {
        result = (result * base) % modulo;
        cout << step++ << ": " << base << "^" << (i + 1) << " mod " << modulo << " = " << result << "\n";
    }
    cout << "Итоговый результат: " << result << "\n\n";
    return result;
}

// разложение степени в двоичный вид
int64_t algbin(int64_t base, int64_t power, int64_t modulo) {
    cout << "Бинарный алгоритм\n";

    base = (base % modulo + modulo) % modulo;
    int64_t result = 1;

    // Двоичное представление степени
    cout << "Степень " << power << " в двоичном виде: ";
    vector<int> bits;
    int64_t tempow = power;

    if (tempow == 0) {
        bits.push_back(0);
    }
    else {
        while (tempow > 0) {
            bits.push_back(tempow % 2);
            tempow /= 2;
        }
    }

    for (int i = bits.size() - 1; i >= 0; i--) {
        cout << bits[i];
    }
    cout << "\n";

    int step = 1;
    int64_t currpow = power;
    while (currpow > 0) {
        if (currpow % 2 == 1) {
            result = (result * base) % modulo;
            cout << step++ << ": бит = 1, result = " << result << "\n";
        }
        else {
            cout << step++ << ": бит = 0, не меняется.\n";
        }
        base = (base * base) % modulo;
        currpow /= 2;
    }

    cout << "Итоговый результат: " << result << "\n\n";
    return result;
}

void runpowmod() {
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
}
