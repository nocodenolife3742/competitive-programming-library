template<typename T>
vector<int> lcp(T &s, const vector<int> &sa) {
    int n = s.size(), k = 0;
    vector<int> lcp(n), rk(n);
    for (int i = 0; i < n; i++) rk[sa[i]] = i;
    for (int i = 0; i < n; i++, k ? k-- : 0) {
        if (rk[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = sa[rk[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k])
            k++;
        lcp[rk[i]] = k;
    }
    return lcp[n - 1] = 0, lcp;
}