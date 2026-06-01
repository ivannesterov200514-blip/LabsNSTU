#include <iostream>
#include <vector>
#include <random>
#include "El_Gamal.h"

using namespace std;

random_device rd;
mt19937_64 gen(rd());

// Проверка на простоту числа p
bool issimple(uint64_t p) {
    if (p == 2 || p == 3) return true;
    if (p <= 1 || p % 2 == 0 || p % 3 == 0) return false;
    
    for (uint64_t i = 5; i * i <= p; i += 6) {
        if (p % i == 0 || p % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

// Расширенный алгоритм Евклида для поиска коэффициента u
uint64_t gcd_euclidext(uint64_t a, uint64_t b, int64_t& u) {
    if (b == 0) {
        u = 1;
        return a;
    }
    int64_t u_prev = 1;
    int64_t u_curr = 0;
    uint64_t r1 = a;
    uint64_t r2 = b;
    while (r2 != 0) {
        uint64_t q = r1 / r2;
        uint64_t temp = r2;
        r2 = r1 - r2 * q;
        r1 = temp;
        int64_t utemp = u_curr;
        u_curr = u_prev - q * u_curr;
        u_prev = utemp;
    }
    u = u_prev;
    return r1;
}

// (C1^x​)^(−1) mod p
uint64_t modinv(uint64_t c, uint64_t m) {
    int64_t u;
    uint64_t gcd = gcd_euclidext(c, m, u);

    if (gcd != 1)  {
        cerr << "Обратный элемент не существует!\n";
        return 0;
    }
    if (u < 0) {
        u += (int64_t)m;
    }
    return (uint64_t)u;
}

// Возведение в степень по модулю
uint64_t mod_pow(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// Генерация открытого ключа (p, g, y)
vector<uint64_t> keygen(uint64_t p, uint64_t g, uint64_t& x) {
    uniform_int_distribution<uint64_t> dist(2, p - 2);
    x = dist(gen);
    cout << "\nСекретный ключ x: " << x << "\n";
    cout << "\nГенерируем открытый ключ\n";

    uint64_t y = mod_pow(g, x, p);
    vector<uint64_t> res = {p, g, y};
    cout << "Открытый ключ: ( ";
    for (auto t : res) {
        cout << t << " ";
    }
    cout << ")\n";
    return res;
}

// Зашифровка сообщения;
pair<uint64_t, uint64_t> crypt(uint64_t m, const vector<uint64_t>& key) {
    uniform_int_distribution<uint64_t> dist(1, key[0] - 2);
    uint64_t k = dist(gen);
    cout << "Сеансовый ключ k: " << k << "\n\n";
    
    pair<uint64_t, uint64_t> res;
    res.first = mod_pow(key[1], k, key[0]);
    res.second = (mod_pow(key[2], k, key[0]) * m) % key[0];
    return res;    
}

// Расшифровка
uint64_t decrypt(pair<uint64_t, uint64_t> text, uint64_t x, const vector<uint64_t>& key) {
    uint64_t s = mod_pow(text.first, x, key[0]);
    uint64_t s_inv = modinv(s, key[0]);
    cout << "(C1^x)^(-1) = " << s_inv << "\n";

    uint64_t mes = ((text.second % key[0]) * (s_inv % key[0])) % key[0];
    cout << "C2 * (C1^x)^(-1) mod " << key[0] << " = " << mes << "\n\n";
    
    return mes;
}

// Преобразование строки в кодовые точки и обратно
vector<uint32_t> to_codes(const string& str) {
    vector<uint32_t> codes;
    
    for (size_t i = 0; i < str.length(); ) {
        unsigned char c = str[i];
        if (c <= 0x7F) { // ASCII (1 байт) 0xxxxxxx
            codes.push_back(static_cast<uint32_t>(c));
            i += 1;
        } 
        else if ((c & 0xE0) == 0xC0 && i + 1 < str.length()) { // Кириллица (2 байта) 110xxxxx 10xxxxxx
            uint32_t code_point = ((str[i] & 0x1F) << 6) | (str[i + 1] & 0x3F); // Собираем код из 5 бит первого байта и 6 бит второго
            codes.push_back(code_point);
            i += 2;
        } 
        else 
            i += 1; // Неизвестный символ пропускаем
    }
    return codes;
}

string to_text(const vector<uint32_t>& codes) {
    string result;
    for (uint32_t cp : codes) {
        if (cp < 0x80) 
            result += static_cast<char>(cp);
        else {
            result += static_cast<char>(0xC0 | (cp >> 6));
            result += static_cast<char>(0x80 | (cp & 0x3F));
        }
    }
    return result;
}