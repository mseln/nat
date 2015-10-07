/*
 * Find the greatest common divider of two positive numbers. T is an integral type.
 */
template <class T>
inline T gcd(T a, T b) {
    if (a < b) swap(a, b);

    while (b != 0) {
        T r = a % b;

        a = b;
        b = r;
    }

    return a;
}


/*
 * Find the least common multiple of two positive numbers. T is an integral type.
 */
template <class T>
inline T lcm(T a, T b) {
    return a * (b / gcd(a, b));
}

/*
 * Do the euclid's algorithm both forward and reverse, to find solutions to
 * diophantine equations. T shall be signed, as this algorithm will use negative
 * numbers internally.
 * Generates one integer solution to the equation a*x + b*y = sum, throws NoSolution
 * if none exists. "a" and "b" are assumed to be positive.
 */
template <class T>
struct Dioph {
    T x, y;

    Dioph(const T &x = T(), const T &y = T()) : x(x), y(y) {}
};

template <class T>
ostream &operator <<(ostream &to, const Dioph<T> &f) {
    return to << "{ x=" << f.x << ", y=" << f.y << "}";
}

template <class T>
Dioph<T> diophantine(T a, T b, T sum) {

    /* If b == 0, it is easy: */
    if (b == T()) {
        /* x = sum / a, iff sum % a != 0 */
        if (sum % a == 0)
            return Dioph<T>(sum / a, 0);
        else
            throw NoSolution();
    } else if (a == T()) {
        if (sum % b == 0)
            return Dioph<T>(sum / b, 0);
        else
            throw NoSolution();
    }

    /* Compute the form: a = z * b + r */
    /* We can also say: r = a - z*b */
    T z = a / b;
    T r = a % b;

    /* Solve the new equation, b*x + r*y = sum */
    Dioph<T> sol = diophantine(b, r, sum);

    /* We know: r = a - z*b */
    /* Substitution gives: b*x + (a - z*b)*y = sum */
    /* Which equals: b*x + a*y - z*b*y = sum <=> a*y + b*(x - z*y) */
    return Dioph<T>(sol.y, sol.x - sol.y*z);
}
