#include <iostream>

using namespace std;

int mod(int base, int power, int module) {
    base %= module;
    power %= module - 1;
    int result = 1;

    for (int i = 0; i < power; ++i) {
        result *= base;
        result %= module;
    }

    return result;
}

int main(){
    cout << mod(123, 4, 7) << endl;
}