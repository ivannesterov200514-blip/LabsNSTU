#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    setlocale(LC_ALL, ".UTF8");
    int n, k;

    cout << "Введите количество кандидатов (n): ";
    cin >> n;
    cout << "Введите количество избирателей (k): ";
    cin >> k;

    vector<string> names(n);
    vector<vector<int>> pref(k, vector<int>(n));
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;

    cout << "Имена кандидатов: ";
    for (int i = 0; i < n; i++) cin >> names[i];
    
    
    for (int i = 0; i < k; i++) {
        cout << "Голос " << (i+1) << ": ";
        for (int j = 0; j < n; j++) {
            cin >> pref[i][j];
            pref[i][j]--;
        }
    }

    vector<int> borda(n, 0);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            borda[pref[i][j]] += (n - 1 - j);
        }
    }

    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return borda[a] > borda[b];
    });

    cout << "\n====МЕТОД БОРДА====\n";
    for (int i = 0; i < n; i++) cout << (i+1) << ". " << names[idx[i]] << " - " << borda[idx[i]] << " баллов\n";

    vector<int> kondors(n, 0);
    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            if (a == b) continue;
            int c = 0;
            for (int i = 0; i < k; i++)
                for (int j = 0; j < n; j++) {
                    if (pref[i][j] == a) { 
                        c++; break; 
                    }
                    if (pref[i][j] == b) break;
                }
            if (c > k/2) kondors[a]++;
        }
    }

    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return kondors[a] > kondors[b];
    });

    cout << "\n====МЕТОД КОНДОРСЕ====\n";
    for (int i = 0; i < n; i++)
        cout << (i+1) << ". " << names[idx[i]] << "- " << kondors[idx[i]] << " побед\n";
    
    if (kondors[idx[0]] == n-1)
        cout << "Победитель: " << names[idx[0]] << "\n";
    else
        cout << "Победитель не определён (парадокс Кондорсе)\n";

    return 0;
}