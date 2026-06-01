#ifndef EL_GAMAL_H
#define EL_GAMAL_H

#include <vector>
#include <utility>
#include <cstdint>
#include <string>

using namespace std;

// Проверка на простоту числа p
bool issimple(uint64_t p);

// Расширенный алгоритм Евклида для поиска коэффициента u
uint64_t gcd_euclidext(uint64_t a, uint64_t b, int64_t& u);

// (C1^x​)^(−1) mod p
uint64_t modinv(uint64_t c, uint64_t m);

// Возведение в степень по модулю
uint64_t mod_pow(uint64_t base, uint64_t exp, uint64_t mod);

// Генерация открытого ключа (p, g, y)
vector<uint64_t> keygen(uint64_t p, uint64_t g, uint64_t& x);

// Зашифровка сообщения;
pair<uint64_t, uint64_t> crypt(uint64_t m, const vector<uint64_t>& key);

// Расшифровка
uint64_t decrypt(pair<uint64_t, uint64_t> ctext, uint64_t x, const vector<uint64_t>& key);

// Преобразование строки в кодовые точки и обратно
vector<uint32_t> to_codes(const string& str);
string to_text(const vector<uint32_t>& codes);

#endif