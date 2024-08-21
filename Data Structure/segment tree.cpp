template<typename T, T (*f)(T, T), T (*e)()>
struct segtree {
    int n;
    vector<T> t;

    segtree(int n) : n(n), t(2 * n, e()) {}

    segtree(vector<T> &a) : n(a.size()), t(2 * n) {
        for (int i = 0; i < n; i++) t[i + n] = a[i];
        for (int i = n - 1; i > 0; i--)
            t[i] = f(t[i << 1], t[i << 1 | 1]);
    }

    void modify(int p, T val) {
        for (t[p += n] = val; p >>= 1;)
            t[p] = f(t[p << 1], t[p << 1 | 1]);
    }

    T query(int l, int r) {
        T ls = e(), rs = e();
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ls = f(ls, t[l++]);
            if (r & 1) rs = f(t[--r], rs);
        }
        return f(ls, rs);
    }
};