#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){
    cout.imbue(locale("C"));
    setlocale(LC_ALL, ".UTF8");
    cout << "==============================================\n";
    cout << setw(8) << "x" << " | " << setw(10) << "y" << " | " << "Formula\n";
    cout << "==============================================\n";
    
    double dx;
    cout << "Введите шаг dx: ";
    cin >> dx;

    // Проверка на корректность шага
    if (dx <= 0) {
        cout << "Ошибка: шаг должен быть строго больше нуля!" << endl;
        return 0;
    }
    for (double x = -7; x <= 5; x += dx) {
        double y;
        string formula;
        bool def = true;
        
        if (x >= -7 && x <= -6) {
            y = -2 * x - 14;
            formula = "y1 = -2x - 14";
        }
        else if (x > -6 && x <= -2) {
            double expr = 4 - pow(x + 4, 2);
            if (expr >= 0) {
                y = -2 + sqrt(expr);
                formula = "y2 = -2 + sqrt(4-(x+4)^2)";
            } 
            else {
                def = false;
            }
        }
        else if (x > -2 && x <= 2) {
            if (2 + x > 0) {
                y = log2(2 + x);
                formula = "y3 = log2(2+x)";
            } 
            else {
                def = false;
            }
        }
        else if (x > 2 && x <= 4) {
            double expr = 1 - pow(x - 3, 2);
            if (expr >= 0) {
                y = sqrt(expr);
                formula = "y4 = sqrt(1-(x-3)^2)";
            } 
            else {
                def = false;
            }
        }
        else if (x > 4 && x <= 5) {
            y = x;
            formula = "y5 = x";
        }
        else {
            def = false;
        }
        cout << setw(8) << x << " | ";
        if (def) {
            cout << setw(10) << y << " | ";
        } 
        else {
            cout << setw(10) << "N/A" << " | ";
        }
        cout << formula << endl;
    }
    cout << "==============================================\n";
    return 0;
}