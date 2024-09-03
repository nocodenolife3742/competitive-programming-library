// needed : fft
template<int MOD = 998244353>
vector<i64> convolution(const vector<i64> &a, const vector<i64> &b) {
    if (a.empty() || b.empty()) return {};
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