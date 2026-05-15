#include <iostream>
#include <vector>
#include <cmath>

#define PI = 3,1415926535897932384626433832795
const double EPS = 1e-4;

using namespace std;

double func(double x) {
    return 2 * pow(x, 2) + cos(x) - 6;
}

double diffunc(double x) {
    return 4 * x - sin(x);
}

double ph(double x) { 
    return sqrt((6 - cos(x)) / 2.0); 
}

struct Iter {
    int n;
    double v1;
    double v2;
    double diff;
};

vector<Iter> halfmethod(double a, double b, vector<Iter> table) {
    double c;
    int k = 0;
    while (b - a > EPS) {
        c = (a + b) / 2.0;
        table.push_back({k, a, b, b - a});
        if (func(a) * func(c) < 0) b = c;
        else a = c;
        k++;
    }
    table.push_back({k, a, b, b - a});
    return table;
}

vector<Iter> newton(double x0, vector<Iter> table) {
    double xn = x0;
    int k = 0;
    while (true) {
        double xn1 = xn - func(xn) / diffunc(xn);
        table.push_back({k, xn, xn1, abs(xn1 - xn)});
        
        if (abs(xn1 - xn) <= EPS) break;
        xn = xn1;
        k++;
    }
    return table;
}

vector<Iter> simpleiter(double x0, vector<Iter> table) {
    double xn = x0;
    int k = 0;
    while (true) {
        double xn1 = ph(xn);
        table.push_back({k, xn, xn1, abs(xn1 - xn)});
        if (abs(xn1 - xn) <= EPS) break;
        xn = xn1;
        k++;
    }
    return table;
}

int main() {
    setlocale(LC_ALL, ".UTF8");
    vector<Iter> hlf, newt, iter;

    hlf = halfmethod(1.0, 2.0, hlf);
    newt = newton(2.0, newt);
    iter = simpleiter(1.5, iter);

    cout << "\nМетод половинного деления\n";
    cout << "N\tan\t\tbn\t\tbn - an\n";
    for (const auto& r : hlf) {
        cout << r.n << "\t" << r.v1 << "\t\t" << r.v2 << "\t\t" << r.diff << "\n";
    }

    cout << "\nМетод Ньютона\n";
    cout << "N\txn\t\txn+1\t\txn+1 - xn\n";
    for (const auto& r : newt) {
        cout << r.n << "\t" << r.v1 << "\t\t" << r.v2 << "\t\t" << r.diff << "\n";
    }
    
    cout << "\nМетод простых итераций\n";
    cout << "N\txn\t\txn+1\t\txn+1 - xn\n";
    for (const auto& r : iter) {
        cout << r.n << "\t" << r.v1 << "\t\t" << r.v2 << "\t\t" << r.diff << "\n";
    }
    return 0;
}