// needed : fft
vector<i64> convolution(const vector<i64> &a, const vector<i64> &b) {
    if (a.empty() || b.empty()) return {};
    vector<i64> ret(a.size() + b.size() - 1);
    int n = 2 << __lg(ret.size());
    vector<complex<double> > in(n), out(n);
    for (int i = 0; i < a.size(); i++)
        in[i] = {1.0 * a[i], 1.0 * b[i]};
    fft(in);
    for (int i = 0; i < n; i++) in[i] *= in[i];
    for (int i = 0; i < n; i++)
        out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    for (int i = 0; i < ret.size(); i++)
        ret[i] = llround(imag(out[i]) / (4 * n));
    return ret;
}