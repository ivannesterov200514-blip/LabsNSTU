#include <iostream>
#include <cmath>

using namespace std;

int main() { 
    setlocale(LC_ALL, ".UTF8");
    cout << "Enter a, b: \n";
    int a, b; 
    cin >> a >> b; 
    if (b == 1) { 
        cout << "infinity" << endl; 
        return 0; 
    }
    if (a > 10 || a < 1 || b > 10 || b < 1) {
        cout << "error";
        return 1;
    }
    double sum = 0.0; 
    for (int n = 1; n <= 100; n++) { 
        sum += (pow (n,a) / pow(b,n)); 
    }
    int min_num, min_den; 
    double min_dif = 999; 
    for (double num = 1; num <= 1000; num++) 
    {
        for (double den = 1; den <= 1000; den++) {
            long double dif = abs(sum - (num / den)); 
            if (min_dif > dif) { 
                min_dif = dif; 
                min_num = num; 
                min_den = den; 
            }
        }
    }
    cout << "Sum: " << min_num << "/" << min_den; 
    return 0; 
} 