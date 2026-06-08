#include "invmod.h"

// Расширенный алгоритм Евклида
int64_t gcd_euclidextinv(int64_t a, int64_t b, int64_t& u, int64_t& v) {
    if (b == 0) {
        u = 1;
        v = 0;
        return a;
    }
    int64_t u_prev = 1, v_prev = 0, u_curr = 0, v_curr = 1;
    int64_t r1 = a;
    int64_t r2 = b;
    cout << "\nr\t\tu\t\tv\t\tq\n";
    cout << "----------------------------------------------------------------\n";
    cout << r1 << "\t\t" << u_prev << "\t\t" << v_prev << "\n";
    cout << r2 << "\t\t" << u_curr << "\t\t" << v_curr << "\n";

    while (r2 != 0) {
        int64_t q = r1 / r2;

        int64_t temp = r2;
        r2 = r1 - r2 * q;
        r1 = temp;

        temp = u_curr;
        u_curr = u_prev - q * u_curr;
        u_prev = temp;

        temp = v_curr;
        v_curr = v_prev - q * v_curr;
        v_prev = temp;
        cout << r2 << "\t\t" << u_curr << "\t\t" << v_curr << "\t\t" << q << "\n";
    }
    u = u_prev;
    v = v_prev;
    return r1;
}

// проверка на существование обратного
int64_t checkIfExists(int64_t c, int64_t m) {
    int64_t u, v;
    int64_t gcd = gcd_euclidextinv(c, m, u, v);

    if (gcd != 1) {
        cout << "Обратный элемент не существует\n";
        return -1;
    }
    int64_t d = (u % m + m) % m;
    return d;
}

void runinvmod() {
    int64_t c, m;
    cout << "Введите основание и модуль: ";
    cin >> c >> m;
    cout << "\n" << c << "^(-1) mod " << m << " = d\nИщем обратный элемент\n";

    cout << "\nr - остаток от деления;\nu - коэффициент при " << c << "; v - коэффициент при " << m << "; q - целая часть от деления\n";
    int64_t d = checkIfExists(c, m);
    if (d != -1) {
        cout << "\nd (mod m) = " << d << "\n";
        cout << "Проверка: " << c << " * " << d << " mod " << m << " = " << (c * d) % m << "\n";
    }
}