#include "cep_drob.h"

// Расширенный алгоритм евклида для поиска коэф. Безу и цепной дроби
pair<int64_t, vector<int64_t>> gcd_euclidfordrob(int64_t a, int64_t b, int64_t& u, int64_t& v) {
    int64_t u_prev = 1, v_prev = 0, u_curr = 0, v_curr = 1;
    int64_t r1 = a, r2 = b;
    vector<int64_t> res;

    cout << "\nr\t\tu\t\tv\t\tq\n";
    cout << "-----------------------------------------------------------\n";
    cout << r1 << "\t\t" << u_prev << "\t\t" << v_prev << "\n";
    cout << r2 << "\t\t" << u_curr << "\t\t" << v_curr << "\n";

    while (r2 != 0) {
        int64_t q = r1 / r2;
        res.push_back(q);

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
    return { r1, res };
}

// Частное решение
pair<int64_t, int64_t> priv_sol(int64_t& d, int64_t& gcd, int64_t& u, int64_t& v) {
    int64_t s = d / gcd;
    int64_t a0 = u * s;
    int64_t b0 = v * s;
    return { a0, b0 };
}

void runcepdrob() {
    int64_t A = 1256;
    int64_t B = 847;
    int64_t D = 119;

    cout << "\n" << A << "a + " << B << "b = " << D << "\n";

    int64_t u, v;
    pair<int64_t, vector<int64_t>> nums = gcd_euclidfordrob(A, B, u, v);

    cout << "\nЦепная дробь A/B: [ ";
    for (int64_t q : nums.second) cout << q << " ";
    cout << "]\n";

    cout << "Тождество Безу: " << A << "*(" << u << ") + " << B << "*(" << v << ") = " << nums.first << "\n";

    // Проверка разрешимости
    if (D % nums.first != 0) {
        cout << "Уравнение не имеет решений в целых числах (НОД не делит D).\n";
        return;
    }

    pair<int64_t, int64_t> sol = priv_sol(D, nums.first, u, v);

    cout << "\nЧастное решение: a0 = " << sol.first << ", b0 = " << sol.second << "\n";
    cout << "Проверка: " << A << "*" << sol.first << " + " << B << "*" << sol.second << " = " << A * sol.first + B * sol.second << " (должно быть " << D << ")\n";

    // Общее решение
    cout << "\nОбщее решение:\n";
    cout << "a = " << sol.first << " + " << (B / nums.first) << "*t\n";
    cout << "b = " << sol.second << " - " << (A / nums.first) << "*t\n";
}