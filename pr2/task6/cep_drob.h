#ifndef CEP_DROB
#define CEP_DROB

#include <iostream>
#include <stdint.h>
#include <vector>

using namespace std;

pair<int64_t, vector<int64_t>> gcd_euclidext(int64_t a, int64_t b, int64_t& u, int64_t& v);
pair<int64_t, int64_t> priv_sol(int64_t& d, int64_t& gcd, int64_t& u, int64_t& v);

#endif