struct phash {
    const int m = 1e9 + 7, b1 = 999999937, b2 = 999999929;
    vector<long long> h1{0}, h2{0}, p1{1}, p2{1};

    template<typename T>
    phash(const T &a) {
        for (int i = 0; i < a.size(); i++) {
            p1.emplace_back((p1.back() * b1) % m);
            p2.emplace_back((p2.back() * b2) % m);
            h1.emplace_back((h1.back() * b1 + a[i]) % m);
            h2.emplace_back((h2.back() * b2 + a[i]) % m);
        }
    }

    long long get_hash(int l, int r) {
        auto v1 = (h1[r + 1] - h1[l] * p1[r - l + 1]) % m;
        auto v2 = (h2[r + 1] - h2[l] * p2[r - l + 1]) % m;
        v1 = (v1 + m) % m, v2 = (v2 + m) % m;
        return (v1 << 31) + v2;
    }
};