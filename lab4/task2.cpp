#include <iostream>
#include <random>
#include <vector>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    setlocale(LC_ALL, ".UTF8");
    ranlux24_base gen(random_device{}());
    uniform_int_distribution<int> dist(150, 300);
    
    int a;
    cout << "Введите количество чисел в массиве: ";
    cin >> a;

    if (a < 10) {
        cout << "\nЧисло элементов должно превышать 10";
        return 1;
    }
    vector<int> n(a);

    cout << "\nИсходный массив: ";
    for (int i = 0; i < a; i++) {
        n[i] = dist(gen);
        cout << n[i] << " ";
    }
    cout << "\n";

    int maxl = 1;
    int currl = 1;
    int maxstart = 0;
    int start = 0;

    for (int i = 1; i < a; ++i) {
        if (n[i] < n[i - 1]) {
            currl++;
        } 
        else {
            if (currl > maxl) {
                maxl = currl;
                maxstart = start;
            }
            currl = 1;
            start = i;
        }
    }
    if (currl > maxl) {
        maxl = currl;
        maxstart = start;
    }

    cout << "\nРазмер самой длинной убывающей последовательности: " << maxl << "\n";
    cout << "Элементы последовательности: ";
    vector<int> result1(maxl);
    for (int i = 0; i < maxl; ++i) {
        result1[i] = n[maxstart + i];
        cout << result1[i] << " ";
    }
    cout << "\n" << "\n";

    double sum = 0.0;
    double sr;
    for (int x : n) {
        sum += x;
    }
    sr = sum / a;

    cout << "Среднее арифметическое исходного массива: " << sr << "\n";

    vector<int> res2;
    for (int x : n) {
        if (x < sr) {
            res2.push_back(x);
        }
    }
    cout << "Размер массива чисел меньших ср.арифм. значения: " << res2.size() << "\n";
    cout << "Элементы последовательности: ";
    for (int i = 0; i < res2.size(); ++i) {
        cout << res2[i] << " ";
    }
    cout << "\n" << "\n";
    
    cout << "Сдвиг исходного массива налево на 2 позиции: ";
    vector<int> res3(a);
    for (int i = 0; i < a; ++i) {
        res3[i] = n[(i+2) % a];
        cout << res3[i] << " ";
    }

    cout << "\n" << "\n";

    uniform_int_distribution<int> distt(100, 120);

    int f;
    cout << "Введите количество чисел в новом массиве: ";
    cin >> f;

    if (f < 20) {
        cout << "\nЧисло элементов должно превышать 20";
        return 1;
    }
    vector<int> h(f);

    cout << "\n Массив: ";
    for (int &x : h) { 
    x = distt(gen);
    cout << x << " ";
}
    cout << "\n";

    sort(h.begin(), h.end(), greater<int>());
    cout << "\nОтсортированный массив (по убыванию): ";
    for (int x : h) {
        cout << x << " ";
    }
    cout << "\n";

    map<int, int> freq;
    int maxcount = 0;
    int fr = h[0];

    for (int x : h) {
        freq[x]++;
        if (freq[x] > maxcount) {
            maxcount = freq[x];
            fr = x;
        }
    }

    cout << "\nНаиболее часто встречающееся число: " << fr << "\n";

    return 0;
}