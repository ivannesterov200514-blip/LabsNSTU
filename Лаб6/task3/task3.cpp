#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

void printMatrix(const vector<vector<double>>& m, const string& name) {
    cout << name << ":\n" << fixed << setprecision(4);
    for (auto& row : m) {
        cout << "| ";
        for (size_t j = 0; j < row.size(); j++) {
            if (j == row.size() - 1) cout << "| ";
            cout << setw(10) << row[j] << " ";
        }
        cout << "|\n";
    }
    cout << "\n";
}

vector<double> gauss(vector<vector<double>> A, vector<double> b) {
    int n = A.size();
    vector<vector<double>> aug(n, vector<double>(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) aug[i][j] = A[i][j];
        aug[i][n] = b[i];
    }

    printMatrix(aug, "Исходная расширенная матрица");

    for (int i = 0; i < n; i++) {
        int mr = i;
        for (int k = i + 1; k < n; k++)
            if (abs(aug[k][i]) > abs(aug[mr][i])) mr = k;
        if (mr != i) swap(aug[i], aug[mr]);

        for (int k = i + 1; k < n; k++) {
            double c = aug[k][i] / aug[i][i];
            for (int j = i; j <= n; j++) aug[k][j] -= c * aug[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        double d = aug[i][i];
        for (int j = i; j <= n; j++) aug[i][j] /= d;
    }

    printMatrix(aug, "Матрица после прямого хода (единичная диагональ)");

    vector<double> x(n);
    cout << "Результаты обратного хода:\n";
    for (int i = n - 1; i >= 0; i--) {
        x[i] = aug[i][n];
        for (int j = i + 1; j < n; j++) x[i] -= aug[i][j] * x[j];
        cout << "x" << i + 1 << " = " << x[i] << "\n";
    }
    return x;
}

void checkDiagonalDominance(const vector<vector<double>>& A) {
    cout << "\nПроверка диагонального преобладания:\n";

    bool ok = true;

    for (int i = 0; i < A.size(); i++) {

        double diag = abs(A[i][i]);
        double sum = 0;

        for (int j = 0; j < A.size(); j++) {
            if (i != j)
                sum += abs(A[i][j]);
        }

        cout << "Строка " << i + 1 << ": |a[" << i + 1 << "][" << i + 1 << "]| = " << diag << ", сумма остальных = " << sum;

        if (diag > sum) cout << "  -> OK\n";
        else {
            cout << "  -> НЕ выполняется\n";
            ok = false;
        }
    }

    if (ok) cout << "\nУсловие сходимости выполняется.\n";
    else cout << "\nУсловие сходимости НЕ выполняется.\n";
}

vector<double> seidel(const vector<vector<double>>& A, const vector<double>& b, double eps = 1e-3, int maxIter = 100)
{
    int n = A.size();
    vector<double> x(n, 0.0);
    vector<double> old(n);
    cout << "-------------------------------------------------------------\n";
    cout << " N        x1        x2        x3        x4        eps\n";
    cout << "-------------------------------------------------------------\n";

    for (int iter = 1; iter <= maxIter; iter++) {
        old = x;
        for (int i = 0; i < n; i++) {
            double sum = b[i];

            for (int j = 0; j < n; j++) {
                if (j < i) sum -= A[i][j] * x[j];
                else if (j > i) sum -= A[i][j] * old[j]; 
            }
            x[i] = sum / A[i][i];
        }

        double err = 0.0;

        for (int i = 0; i < n; i++) err = max(err, abs(x[i] - old[i]));
        cout << setw(2) << iter << " " << setw(10) << fixed << setprecision(4) << x[0] << setw(10) << x[1] << setw(10) << x[2] << setw(10) << x[3] << setw(12) << err << "\n";

        if (err < eps) break;
    }
    return x;
}


int main() {
    setlocale(LC_ALL, ".UTF8");
    double M = 0.89, N = 0.12, P = -1.15;

    vector<vector<double>> A = {
        {M,     -0.04,  0.21,  -1.16},
        {0.25,  -1.23,  N,     -0.09},
        {-0.21, N,      0.8,   -0.13},
        {0.15,  -1.31,  0.06,  P}
    };
    vector<double> B = { -1.24, P, 2.56, M };

    cout << "\nМетод Гаусса:\n";
    vector<double> Xg = gauss(A, B);
    cout << "\nРешение (Гаусс): x1=" << Xg[0] << ", x2=" << Xg[1] << ", x3=" << Xg[2] << ", x4=" << Xg[3] << "\n\n";

    checkDiagonalDominance(A);

    cout << "\nМетод Зейделя:\n";
    vector<double> Xs = seidel(A, B);
    cout << "\nРешение (Зейдель): x1=" << Xs[0] << ", x2=" << Xs[1] << ", x3=" << Xs[2] << ", x4=" << Xs[3] << "\n";

    return 0;
}