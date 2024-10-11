template<typename T>
int gauss(vector<vector<T> > &a, int m = -1) {
    int n = a.size(), r = 0;
    if (m == -1) m = a[0].size();
    for (int c = 0; c < m && r < n; c++, r++) {
        int t = r;
        for (int i = r + 1; i < n; i++)
            if (abs(a[i][c]) > abs(a[t][c])) t = i;
        if (abs(a[t][c]) < 1e-9) continue;
        swap(a[t], a[r]);
        T s = T(1) / a[r][c];
        for (int i = 0; i < m; i++) a[r][i] *= s;
        for (int i = 0; i < n; i++)
            if (i != r) {
                T t = a[i][c];
                for (int j = 0; j < m; j++)
                    a[i][j] -= t * a[r][j];
            }
    }
    return r;
}

// bitset version
template<int sz>
int gauss(vector<bitset<sz> > &a, int m = -1) {
    if (a.empty()) return 0;
    int n = a.size(), r = 0;
    if (m == -1) m = sz;
    for (int c = 0; c < m && r < n; c++) {
        int t = r;
        for (int i = r + 1; i < n; i++)
            if (a[i][c]) {
                t = i;
                break;
            }
        if (!a[t][c]) continue;
        swap(a[t], a[r]);
        for (int i = 0; i < n; i++)
            if (i != r && a[i][c])
                a[i] ^= a[r];
        r++;
    }
    return r;
}