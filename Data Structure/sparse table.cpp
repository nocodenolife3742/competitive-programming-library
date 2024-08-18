template<class T, T (*f)(T, T), T e>
struct sparse_table {
    int lv, n;
    vector<vector<T> > t;

    sparse_table(vector<T> &a) : lv(__lg(a.size()) + 1), n(a.size()) {
        t = vector(lv, a);
        for (int i = 1; i < lv; i++)
            for (int j = 0; j + (1 << i - 1) < n; j++)
                t[i][j] = f(t[i - 1][j], t[i - 1][j + (1 << i - 1)]);
    }

    T query(int l, int r) {
        T ret = e;
        for (int i = lv - 1; i >= 0; i--)
            if (r - l + 1 >= 1 << i)
                ret = f(ret, t[i][l]), l += 1 << i;
        return ret;
        // O(1) query : only works for specified operation
        // int i = __lg(r - l + 1);
        // return f(t[i][l], t[i][r - (1 << i) + 1]);
    }
};