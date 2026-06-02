#include "getd.h"

int64_t gcd_euclidext(int64_t a, int64_t b, int64_t& u, int64_t& v) {
    if (b == 0) {
        u = 1;
        v = 0;
        return a;
    }
    int64_t u_prev = 1, v_prev = 0, u_curr = 0, v_curr = 1;
    int64_t r1 = a;
    int64_t r2 = b;
    cout << "\nr\t\td\t\tv\t\tq\n";
    cout << "----------------------------------------------------------------\n";
    cout << r1 << "\t\t" << u_prev << "\t\t" << v_prev << "\n";
    cout << r2 << "\t\t" << u_curr << "\t\t" << v_curr << "\n";

    while (r2 != 0) {
        int64_t q = r1 / r2;

        int64_t temp = r2;
        r2 = r1 - r2 * q;
        r1 = temp;

        temp = u_curr;
        u_curr = u_prev - q * u_curr;
        u_prev = temp;

        temp = v_curr;
        v_curr = v_prev - q * v_curr;
        v_prev = temp;
        cout << r2 << "\t\t" << u_curr << "\t\t" << v_curr << "\t\t" << q << "\n";
    }
    u = u_prev;
    v = v_prev;
    return r1;
}

int64_t check(int64_t c, int64_t m) {
    int64_t u, v;
    int64_t gcd = gcd_euclidext(c, m, u, v);

    if (gcd != 1) return -1;
    return u;
}