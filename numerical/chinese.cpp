#pragma once
#include "number.h"
#include "modular.h"

/*
 * Solve the problem:
 * x = a (mod m)
 * x = b (mod n)
 * ...
 * Where a, b, m and n are valid modular numbers. A NoSolution is thrown if
 * there is no solution.
 */
Modular<int64> remainder(const vector<Modular<int64> > &eq) {
    typedef Modular<int64> M;

    M last = eq[0];

    for (nat i = 1; i < eq.size(); i++) {
        M curr = eq[i];

        /* Given the two currently first equations: */
        /* r = a (mod m) = b (mod n) */
        /* r = a + x*m = b + y*n */
        /* a - b = y*n - x*m */
        Dioph<int64> sol = diophantine(-last.modulo, curr.modulo, last.value - curr.value);
        int64 mod = lcm(last.modulo, curr.modulo);

        last = M(last.value, mod) + M(last.modulo, mod) * M(sol.x, mod);
    }

    return last;
}

