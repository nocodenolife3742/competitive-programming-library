template<typename T>
int gauss(vector<vector<T> > &a, int m = -1) {
    if (a.empty()) return 0;
    int n = a.size(), r = 0;
    if (m == -1) m = a[0].size();
    for (int c = 0; c < m && r < n; c++) {
        int t = r;
        for (int i = r + 1; i < n; i++)
            if (abs(a[i][c]) > abs(a[t][c])) t = i;
        if (abs(a[t][c]) == 0) continue;
        swap(a[t], a[r]);
        T s = 1.0 / a[r][c];
        for (int i = 0; i < m; i++) a[r][i] *= s;
        for (int i = 0; i < n; i++)
            if (i != r) {
                T t = a[i][c];
                for (int j = 0; j < m; j++)
                    a[i][j] -= t * a[r][j];
            }
        r++;
    }
    return r;
}