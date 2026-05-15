#include <iostream>
#include <vector>

using namespace std;

int64_t prefsum(const vector<int>& nums, int start, int k) {
        int64_t a = 0;
        for (int i = 0; i < k; ++i) {
        a += nums[start + i];
        }
        return a;
}

int main(){
    setlocale(LC_ALL, ".UTF8");
    int n, m;
    
    cout << "Введите количество чисел в последовательности: \n";
    cin >> n;
    if (n < 5 || n > 50000) {
        cout << "Ошибка ввода\n";
        return 1;
    }

    cout << "По сколько максимум чисел они могут убрать? \n";
    cin >> m;
    
    cout << "Введите последовательность из " << n << " чисел: \n";

    vector<int> nums(n);

    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    bool pavmove = true;
    int64_t scores[2] = {0, 0}; // scores[0] - Павел, scores[1] - Вика
    int lastmv = -1;
    int64_t maxscore = INT64_MIN;
    int best_k = -1;
    int64_t currsc = 0;
    int start = 0;

    while (start < n) {
        int max_k = min(m, n - start);

        maxscore = INT64_MIN;
        best_k = -1;

        for (int k = 1; k <= max_k; ++k) {
            if (k == lastmv) continue;
            currsc = prefsum(nums, start, k);

            if (currsc > maxscore || (currsc == maxscore && k < best_k)) {
                maxscore = currsc;
                best_k = k;
            }
        }
        
        if (best_k == -1) break;

        if (pavmove) scores[0] += maxscore;
        else scores[1] += maxscore;

        start += best_k;
        lastmv = best_k;

        pavmove = !pavmove;
    }

    if (scores[0] > scores[1])
    cout << "Победил 1\n";
    else cout << "Победила 0\n";
    return 0;
}