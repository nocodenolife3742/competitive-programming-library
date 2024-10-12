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