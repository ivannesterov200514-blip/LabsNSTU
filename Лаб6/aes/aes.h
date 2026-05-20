#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <iomanip>

using namespace std;

void generate_key(uint8_t key[16]);
bool load_key(uint8_t key[16]);
void generate_iv(uint8_t iv[16]);

void keyexpansion(const uint8_t key[16], uint8_t roundkeys[11][16]);

void addroundkey(uint8_t block[16], const uint8_t roundkeys[11][16]);
void subbytes(uint8_t block[16]);
void invsubbytes(uint8_t block[16]);
void shiftrows(uint8_t block[16]);
void invshiftrows(uint8_t block[16]);
void mixcolumns(uint8_t block[16]);
void invmixcolumns(uint8_t block[16]);

void cryptblock(uint8_t block[16], const uint8_t roundkeys[11][16]);
void decryptblock(uint8_t block[16], const uint8_t roundkeys[11][16]);

void cbcencrypt(const uint8_t roundkeys[11][16], const uint8_t iv[16], const vector<uint8_t>& data, vector<uint8_t>& cipher);
void cbcdecrypt(const uint8_t roundkeys[11][16], const uint8_t iv[16], const vector<uint8_t>& cipher, vector<uint8_t>& data);

vector<uint8_t> pkcs7pad(const string& text);
string pkcs7unpad(const vector<uint8_t>& data);

void printstate(const uint8_t block[16], const string& label);
void printroundkeys(const uint8_t roundkeys[11][16]);