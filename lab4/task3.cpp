#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main() {
    setlocale(LC_ALL, ".UTF8");
    int a, b, m, N;
    char op;
    cout << "\nВведите целые a и b: ";
    cin >> a >> b;

    cout << "\nВведите модуль: ";
    cin >> m;

    int n = max(a, b);

    cout << "\nВведите " << n << " начальных значений: ";
    vector<double> vars(n);
    for (int i = 0; i < n; ++i) {
        cin >> vars[i];
    }

    cout << "\nВведите количество генерируемых чисел N: ";
    cin >> N;

    cout << "\nВведите операцию +, -, * или ^: ";
    cin >> op;

    cout << "\nСгенерированная последовательность: ";
    for (int i = 0; i < N; ++i) {
        int left = vars[vars.size() - a];
        int right = vars[vars.size() - b];
        int next;

        if (op == '+') next = (left + right) % m;
        else if (op == '-') next = (left - right) % m;
        else if (op == '*') next = (left * right) % m;
        else if (op == '^') next = (left ^ right) % m;
        else {
            cout << "Input error";
            return 1;
        }

        if (next < 0) next += m;
        vars.push_back(next);
        cout << next << " ";
    }
    cout << "\n";
    return 0;
}