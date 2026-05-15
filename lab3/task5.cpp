#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

double korrel(const vector<double>& x, const vector<double>& y) {
    int n = x.size();
    double sum_x = 0, sum_y = 0;
    double srarf_x, srarf_y;
    double r;

    for (int i = 0; i < n; ++i) {
        sum_x += x[i];
        sum_y += y[i];
    }
    srarf_x = sum_x / n;
    srarf_y = sum_y / n;

    double numer = 0, var_x = 0, var_y = 0;
    for (int i = 0; i < n; ++i) {
        double dx = x[i] - srarf_x;
        double dy = y[i] - srarf_y;
        numer += dx * dy;
        var_x += dx * dx;
        var_y += dy * dy;
    }

    r = numer / sqrt(var_x * var_y);
    return r;
}

pair<double, double> aprox(const vector<double>& x, const vector<double>& y) {
    int n = x.size();
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    double a, b;

    for (int i = 0; i < n; ++i) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }

    a = (n * sum_xy - - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    b = (sum_y - a * sum_x) / n;
    pair<double, double> app = {a, b};
    return app;
}

void cofe(const vector<double>& tpoints, double tk, double tsr, double r) {
    vector<double> x;
    vector<double> y;
    cout << "+------------+---------------+ \n";
    cout << "| Время (минут) | Температура C |\n";
    cout << "+------------+---------------+\n";
    for (double j : tpoints) {
        double t;
        t = tk - (tsr - tk) * exp(-r * j);
        cout << "| " << setw(10) << fixed << setprecision(2) << j << " | " << setw(13) << setprecision(2) << t << " | " << "\n";
        x.push_back(j);
        y.push_back(t);
    }
    cout << "+------------+---------------+" << "\n" << "\n";
    
    pair<double, double> apr = aprox(x, y);
    cout << "Значения аппроксимирующей прямой: \n" << "a = " << apr.first << "\n" << "b = " << apr.second << "\n";

    cout << "\nКоэффициент детерминации: \n" << "r = " << korrel(x, y);
}

int main() {
    setlocale(LC_ALL, ".UTF8");
    double tk, tsr, r, t_max;
    int mes;
        
    cout << "==Моделирование охлаждения кофе==\n\n" << endl;
    cout << "Введите значение исходной температуры кофе: ";
    cin >> tk;
    cout << "Введите значение окружающей температуры: ";
    cin >> tsr;
    cout << "Введите значение коэффициента охлаждения: ";
    cin >> r;
    cout << "Введите количество измерений: ";
    cin >> mes;

    vector<double> tpoints(mes);
    cout << "Введите временные отметки (в минутах, разделённые пробелом): ";
    for (int i = 0; i < mes; ++i) {
        cin >> tpoints[i];
    }
    cofe(tpoints, tk, tsr, r);
    return 0;
}