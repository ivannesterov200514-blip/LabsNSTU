#ifndef INVMOD_H
#define INVMOD_H

#include <iostream>
#include <stdint.h>
using namespace std;

int64_t gcd_euclidextinv(int64_t a, int64_t b, int64_t& u, int64_t& v);
int64_t checkIfExists(int64_t c, int64_t m);

void runinvmod();

#endif
