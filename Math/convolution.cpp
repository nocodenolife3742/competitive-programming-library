template<int MOD = 998244353>
vector<i64> convolution(const vector<i64> &a, const vector<i64> &b) {
    if (a.empty() || b.empty()) return {};
    auto fft = [](vector<complex<double> > &a) {
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
    };
    vector<i64> ret(a.size() + b.size() - 1);
    int n = 2 << __lg(ret.size()), cut = sqrt(MOD);
    vector<complex<double> > l(n), r(n), outs(n), outl(n);
    for (int i = 0; i < a.size(); i++)
        l[i] = {a[i] / cut, a[i] % cut};
    for (int i = 0; i < b.size(); i++)
        r[i] = {b[i] / cut, b[i] % cut};
    fft(l), fft(r);
    for (int i = 0; i < n; i++) {
        int j = -i & (n - 1);
        outl[j] = (l[i] + conj(l[j])) * r[i] / (2.0 * n);
        outs[j] = (l[i] - conj(l[j])) * r[i] / (2.0 * n) / 1i;
    }
    fft(outl), fft(outs);
    for (int i = 0; i < ret.size(); i++) {
        i64 av = llround(real(outl[i])), cv = llround(imag(outs[i]));
        i64 bv = llround(imag(outl[i])) + llround(real(outs[i]));
        ret[i] = ((av % MOD * cut + bv) % MOD * cut + cv) % MOD;
    }
    return ret;
}