#ifndef POWMOD_H
#define POWMOD_H

#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

bool isPrime(int64_t n);
int64_t algferma(int64_t base, int64_t power, int64_t modulo);
int64_t algbin(int64_t base, int64_t power, int64_t modulo);

#endif
