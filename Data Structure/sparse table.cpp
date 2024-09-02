template<typename T, T (*f)(T, T)>
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
        int i = __lg(r - l + 1);
        return f(t[i][l], t[i][r - (1 << i) + 1]);
    }
};