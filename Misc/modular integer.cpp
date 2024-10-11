template<int M>
struct mint {
    int v;
    explicit operator int() const { return v; }

    mint(): v(0) {}

    mint(long long x): v(x % M) { v += (v < 0) * M; }

    mint &operator+=(mint o) {
        if ((v += o.v) >= M) v -= M;
        return *this;
    }

    mint &operator-=(mint o) {
        if ((v -= o.v) < 0) v += M;
        return *this;
    }

    mint &operator*=(mint o) {
        v = 1ll * v * o.v % M;
        return *this;
    }

    mint &operator/=(mint o) {
        return *this *= inv(o);
    }

    friend mint pow(mint a, long long p) {
        assert(p >= 0);
        if (p >= M) p %= (M - 1);
        return p == 0 ? 1 : pow(a * a, p / 2) * (p & 1 ? a : 1);
    }

    friend mint inv(mint a) {
        assert(a.v != 0);
        return pow(a, M - 2);
    }

    friend int abs(mint a) { return a.v; }

    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
    friend mint operator/(mint a, mint b) { return a /= b; }
};