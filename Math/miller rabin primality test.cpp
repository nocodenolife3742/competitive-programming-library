static bool is_prime(u64 n) {
    if (n == 1 || n % 2 == 0) return n == 2;
    u64 d = (n - 1) >> __builtin_ctzll(n - 1);
    vector<u64> s{2, 325, 9375, 28178, 450775, 9780504};
    if (n < 4759123141ll) s = {2, 7, 61};
    for (auto &a: s) {
        if (n <= a) return true;
        u64 p = a % n;
        if (p == 0) continue;
        u64 x = 1;
        for (u64 e = d; e; e >>= 1) {
            if (1 & e) x = u128(x) * p % n;
            p = u128(p) * p % n;
        }
        if (x == 1) continue;
        for (u64 t = d; x != n - 1; t <<= 1) {
            x = u128(x) * x % n;
            if (x == 1 || t == n - 1) return false;
        }
    }
    return true;
}