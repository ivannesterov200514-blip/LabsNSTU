<<<<<<< HEAD
#include "cep_drob.h"

int main()
{
    setlocale(LC_ALL, "Rus");
    int64_t A = 1256;
    int64_t B = 847;
    int64_t D = 119;

    cout << "\n" << A << "a + " << B << "b = " << D << "\n";

    int64_t u, v;
    pair<int64_t, vector<int64_t>> nums = gcd_euclidext(A, B, u, v);

    cout << "\nЦепная дробь A/B: [ ";
    for (int64_t q : nums.second) cout << q << " ";
    cout << "]\n";

    cout << "Тождество Безу: " << A << "*(" << u << ") + " << B << "*(" << v << ") = " << nums.first << "\n";

    // Проверка разрешимости
    if (D % nums.first != 0) {
        cout << "Уравнение не имеет решений в целых числах (НОД не делит D).\n";
        return 0;
    }

    pair<int64_t, int64_t> sol = priv_sol(D, nums.first, u, v);

    cout << "\nЧастное решение: a0 = " << sol.first << ", b0 = " << sol.second << "\n";
    cout << "Проверка: " << A << "*" << sol.first << " + " << B << "*" << sol.second << " = " << A * sol.first + B * sol.second << " (должно быть " << D << ")\n";

    // Общее решение
    cout << "\nОбщее решение:\n";
    cout << "a = " << sol.first << " + " << (B / nums.first) << "*t\n";
    cout << "b = " << sol.second << " - " << (A / nums.first) << "*t\n";
    return 0;
=======
#include "cep_drob.h"

int main()
{
    setlocale(LC_ALL, "Rus");
    int64_t A = 1256;
    int64_t B = 847;
    int64_t D = 119;

    cout << "\n" << A << "a + " << B << "b = " << D << "\n";

    int64_t u, v;
    pair<int64_t, vector<int64_t>> nums = gcd_euclidext(A, B, u, v);

    cout << "\nЦепная дробь A/B: [ ";
    for (int64_t q : nums.second) cout << q << " ";
    cout << "]\n";

    cout << "Тождество Безу: " << A << "*(" << u << ") + " << B << "*(" << v << ") = " << nums.first << "\n";

    // Проверка разрешимости
    if (D % nums.first != 0) {
        cout << "Уравнение не имеет решений в целых числах (НОД не делит D).\n";
        return 0;
    }

    pair<int64_t, int64_t> sol = priv_sol(D, nums.first, u, v);

    cout << "\nЧастное решение: a0 = " << sol.first << ", b0 = " << sol.second << "\n";
    cout << "Проверка: " << A << "*" << sol.first << " + " << B << "*" << sol.second << " = " << A * sol.first + B * sol.second << " (должно быть " << D << ")\n";

    // Общее решение
    cout << "\nОбщее решение:\n";
    cout << "a = " << sol.first << " + " << (B / nums.first) << "*t\n";
    cout << "b = " << sol.second << " - " << (A / nums.first) << "*t\n";
    return 0;
>>>>>>> 05ec7888d741d95755c8845f0090f27b7e6d8528
}