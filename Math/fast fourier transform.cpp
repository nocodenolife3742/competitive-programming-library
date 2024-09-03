void fft(vector<complex<double> > &a) {
    static vector<complex<long double> > r(2, {1, 0});
    static vector<complex<double> > rt(2, {1, 0});
    int n = a.size(), l = 31 - __builtin_clz(n);
    for (static int k = 2; k < n; k *= 2) {
        r.resize(n), rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        for (int i = k; i < 2 * k; i++)
            rt[i] = r[i] = i & 1 ? r[i / 2] * x : r[i / 2];
    }
    vector<int> rev(n);
    for (int i = 0; i < n; i++) {
        rev[i] = (rev[i / 2] | (i & 1) << l) / 2;
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            for (int j = 0; j < k; j++) {
                auto z = rt[j + k] * a[i + j + k];
                a[i + j + k] = a[i + j] - z, a[i + j] += z;
            }
}