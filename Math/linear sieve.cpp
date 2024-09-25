vector<int> sieve(int n) {
    vector<int> d(n), l;
    for (int i = 2; i < n; i++) {
        if (d[i] == 0)
            d[i] = i, l.push_back(i);
        for (int &j: l) {
            if (1ll * i * j >= n) break;
            d[i * j] = j;
            if (j == d[i]) break;
        }
    }
    return d;
}