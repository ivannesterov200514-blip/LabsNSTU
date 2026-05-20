#include "aes.h"
#include <locale>
#include <fstream>
#include <sstream>

int main() {
    locale::global(locale("ru_RU.UTF-8"));

    cout << "==AES123 CBC==\n\n";

    uint8_t key[16];
    uint8_t roundkeys[11][16];

    cout << "Загрузка ключа...\n";
    if (!load_key(key)) {
        cout << "Ключ не найден. Генерируем новый ключ..\n";
        generate_key(key);
    }
    else cout << "Ключ загружен из aeskey.bin\n";

    keyexpansion(key, roundkeys);
    cout << "Round Keys: \n";
    printroundkeys(roundkeys);

    uint8_t iv[16];
    generate_iv(iv);
    cout << "Вектор инициализации: \n";
    printstate(iv, "IV");

    cout << "\nВвод текста\n";
    string text;
    cout << "\nВыберите метод ввода текста: [1] Клавиатура, [2] Файл: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 2) {
        string fname;
        cout << "Введите имя файла (к примеру, input.txt): ";
        getline(cin, fname);
        ifstream in(fname, ios::binary);
        if (!in.is_open()) {
            throw runtime_error("Не удалось открыть файл: " + fname);
        }
        ostringstream ss;
        ss << in.rdbuf();
        text = ss.str();
        in.close();
        cout << "Файл прочитан.\n";
    }
    else {
        cout << "Введите текст для шифрования: ";
        getline(cin, text);
        if (text.empty()) {
            text = "Привет мир! Стандартный тест.";
            cout << "Используем текст по умолчанию.\n";
        }
    }

    vector<uint8_t> padded = pkcs7pad(text);
    
    cout << "ШИФРОВАНИЕ:\n";
    vector<uint8_t> ciphertext;
    cbcencrypt(roundkeys, iv, padded, ciphertext);

    cout << "\nШифротекст:\n";
    for (size_t i = 0; i < ciphertext.size(); ++i) {
        cout << hex << setw(2) << setfill('0') << (int)ciphertext[i] << " ";
        if ((i + 1) % 16 == 0) cout << "\n";
    }
    cout << dec << "\n\n";

    cout << "РАСШИФРОВКА:\n";
    vector<uint8_t> decryptedpadd;
    cbcdecrypt(roundkeys, iv, ciphertext, decryptedpadd);

    cout << "\nDecrypted bytes (hex):\n";
    for (size_t i = 0; i < decryptedpadd.size(); ++i) {
        cout << hex << setw(2) << setfill('0') << (int)decryptedpadd[i] << " ";
        if ((i + 1) % 16 == 0) cout << "\n";
    }
    cout << dec << "\n";

    cout << "Last 16 bytes: ";
    size_t start = (decryptedpadd.size() > 16) ? decryptedpadd.size() - 16 : 0;
    for (size_t i = start; i < decryptedpadd.size(); ++i) {
        cout << hex << setw(2) << setfill('0') << (int)decryptedpadd[i] << " ";
    }
    cout << dec << "\n";

    if (!decryptedpadd.empty()) {
        cout << "Last byte (padding value): " << (int)decryptedpadd.back() << "\n";
    }

    string result = pkcs7unpad(decryptedpadd);
    

    cout << "ПРОВЕРКА:\n\n";
    cout << "Исходный текст: \n" << text << "\n";
    cout << "Расшифр.: \n" << result << "\n";
    if (text == result) cout << "\nТексты совпадают\n";
    else {
        cout << "\nОшибка: тексты не совпадают\n";
        return 1;
    }
    return 0;
}