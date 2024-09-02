// needed : exgcd
pair<i64, i64> crt(const vector<pair<i64, i64> > &e) {
    i64 x = 0, l = 1;
    for (auto [r, m]: e) {
        r %= m;
        if (m > l) swap(x, r), swap(l, m);
        auto [a, b, g] = exgcd(l, m);
        if ((r - x) % g) return {0, 0};
        i64 n = m / g;
        x = (x + (r - x) / g * a % n * l) % (l * n);
        l *= n;
    }
    return {x < 0 ? x + l : x, l};
}