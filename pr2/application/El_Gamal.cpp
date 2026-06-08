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
uint64_t elg_euclidext(uint64_t a, uint64_t b, int64_t& u) {
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
    uint64_t gcd = elg_euclidext(c, m, u);

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

// Выполнение
void runElGamal() {
    uint64_t x; 
    uint64_t p, g;
    cout << "---ШИФР ЭЛЬ ГАМАЛЯ---\n\n";
    cout << "Введите простое число p (должно быть > 10000 для поддержки кириллицы): ";
    while (true) {
        cin >> p;
        if (p <= 10000)
            cout << "Ошибка: p слишком мало. Для русских букв и знаков препинания нужно p > 10000. Введите заново: "; 
        else if (issimple(p) == false) 
            cout << "Ошибка: p не простое число. Введите заново: "; 
        else break;
    }

    cout << "Введите число g (2 ≤ g < " << p << "): ";
    while (true) {
        cin >> g;
        if (g < 2) 
            cout << "Ошибка: g должно быть >= 2. Введите заново: \n";
        else if (g >= p) 
            cout << "Ошибка: g должно быть < p (" << p << "). Введите заново: \n";
        else break;
    }

    vector<uint64_t> key = keygen(p, g, x);
    
    string message;
    char useFile;
    cout << "\nПрочитать сообщение из файла? (y/n): ";
    cin >> useFile;
    
    if (useFile == 'y' || useFile == 'Y') {
        string fname;
        cout << "Введите имя файла: ";
        cin >> fname;
        ifstream inFile(fname);
        if (!inFile.is_open()) {
            cerr << "Ошибка: файл '" << fname << "' не найден!\n";
            return;
        }
        // Читаем весь файл в строку (сохраняет UTF-8 байты, включая \n)
        message.assign(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>());
        inFile.close();
        cout << "Текст из файла загружен (" << message.size() << " байт).\n";
    } else {
        cin.ignore(); // очистка буфера после cin
        cout << "Введите сообщение: ";
        getline(cin, message);
    }

    if (message.empty()) {
        cout << "Ошибка: пустое сообщение\n";
        return;
    }

    vector<uint32_t> codes = to_codes(message);
    
    // все коды должны быть < p
    for (uint32_t cp : codes) {
        if (cp >= p) {
            cout << "Ошибка: код символа " << cp << " >= p (" << p << ")\n";
            cout << "Используйте большее простое число p!\n";
            return;
        }
    }

    // Шифруем каждый символ отдельно
    cout << "\n--ШИФРОВАНИЕ--\n\n";
    vector<pair<uint64_t, uint64_t>> ctext;
    for (size_t i = 0; i < codes.size(); ++i) {
        ctext.push_back(crypt(static_cast<uint64_t>(codes[i]), key));
    }

    cout << "Шифротекст:\n";
    for (size_t i = 0; i < ctext.size(); ++i) {
        cout << "( C1 = " << ctext[i].first << ", C2 = " << ctext[i].second << " )\n";
    }
    cout << "\n";

    // Расшифровываем каждый символ
    cout << "\n--РАСШИФРОВКА--\n\n";
    vector<uint32_t> dec_codes;
    for (size_t i = 0; i < ctext.size(); ++i) {
        uint64_t val = decrypt(ctext[i], x, key);
        dec_codes.push_back(static_cast<uint32_t>(val));
    }
    string decrypted = to_text(dec_codes);
    cout << "Расшифрованный текст: " << decrypted << "\n\n";
    
    string out;
    cin.ignore();
    cout << "\nВведите имя файла для сохранения шифротекста (или Enter чтобы пропустить): ";
    getline(cin, out);

    // Запись в файл шифротекста
    if (!out.empty()) {
        ofstream outFile(out);
        if (!outFile.is_open()) {
            cerr << "Ошибка: не удалось создать файл '" << out << "'!\n";
            return;
        }

        for (const auto& p : ctext) {
            outFile << p.first << " " << p.second << "\n";
        }
        outFile.close();
        cout << "Шифротекст сохранён в '" << out << "'\n";
    }

    cout << "Проверка на соответствие\n\n";

    cout << "Исходный текст: " << message << "\n\n";
    if (decrypted == message) 
        cout << "Расшифрованный текст соответствует исходному :)\n\n";
    else 
        cout << "Ошибка: расшифрованный текст не соответствует исходному :(\n";
}