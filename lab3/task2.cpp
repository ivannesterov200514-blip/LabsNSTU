#include <iostream>
#include <random>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

vector<int> erat(int limit) {
    vector<bool> is_prime(limit + 1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;
    
    for (int p = 2; p * p <= limit; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= limit; i += p)
                is_prime[i] = false;
        }
    }
    
    for (int p = 2; p <= limit; p++)
        if (is_prime[p]) primes.push_back(p);
    return primes;
}

void prim(const vector<int>& primes) {
    cout << "Простые числа до 500 (Решето Эратосфена):\n";
    cout << "------------------------------------------\n";
    for (size_t i = 0; i < primes.size(); i++) {
        cout << setw(3) << primes[i];
        if ((i + 1) % 10 == 0) cout << "\n";
        else cout << " ";
    }
    cout << "\n\nВсего: " << primes.size() << " простых чисел\n";
    cout << "------------------------------------------\n";
}

double gen_psi () {
    random_device rd;                 
    mt19937 gen(rd());                
    uniform_real_distribution<double> dist(0.0, 1.0); 
    double eps = dist(gen);
    return eps;
}

uint64_t mulmod(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t res = 0;
    a %= m;
    while (b) {
        if (b & 1) {
            if ((res += a) >= m) res -= m;
        }
        if ((a <<= 1) >= m) a -= m;
        b >>= 1;
    }
    return res;
}

// Возведение в степень по модулю
uint64_t powmod(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1)
            result = mulmod(result, base, mod);
        base = mulmod(base, base, mod);
        exp >>= 1;
    }
    return result;
}

bool checkmod(uint64_t p, uint64_t N, uint64_t u) {
    if (powmod(2, p - 1, p) != 1) return false;
    if (powmod(2, N + u, p) == 1) return false;
    return true;
}

pair<uint64_t, int> gen_p (int q, int t){
    pair<uint64_t, int> res;
    uint64_t N, p, u;
    uint64_t step, fst, scn;
    int rejected = 0;
    do {
        double psi = gen_psi();
        step = 1ULL << (t-1);
        N = (step / q) + (step * psi / q);
        if (N % 2 != 0) N++;
        u = 0;
        while (1){
            p = (N + u) * q + 1;

            if (p > pow(2, t)) {
                rejected++;
                break;
            }

            if (checkmod(p, N, u)) {
                res.first = p;
                res.second = rejected;
                return res;
            }
            rejected++;
            u = u + 2;
        }       
    }
    while (1);
}

int main(){
    setlocale(LC_ALL, ".UTF8");
    
    vector<int> primes = erat(500);
    prim(primes);
    
    int q, t;
    cout << "Введите числа q и t (q должно быть из таблицы выше): \n";
    cin >> q >> t;
    
    if (find(primes.begin(), primes.end(), q) == primes.end()) {
        cout << "Ошибка: число " << q << " не является простым из таблицы.\n";
        return 1;
    }
    
    cout << "==============================================\n";
    cout << "Генерация простого числа по методу ГОСТ P.34.10-94: \n";
    cout << "==============================================\n";
    
    cout << "| №  | Простое число     | Количество отвергнутых чисел |\n";
    cout << "|----|-------------------|------------------------------|\n";

    for (int i = 1; i <= 10; ++i) {
        pair<uint64_t, int> go = gen_p(q, t);
        cout << "| " << setw(2) << i << " | " << setw(17) << go.first << " | " << setw(22) << go.second << " |\n";
    }
    return 0;
}