// time complexity : O(n lg^2 n)
template<typename T>
vector<int> suffix_array(T &s) {
    int n = s.size();
    vector<int> sa(n), rk = vector<int>(s.begin(), s.end()), tmp(n);
    iota(sa.begin(), sa.end(), 0);
    for (int k = 1; k < n; k *= 2) {
        auto cmp = [&](int x, int y) {
            if (rk[x] != rk[y]) return rk[x] < rk[y];
            int rx = x + k < n ? rk[x + k] : -1;
            int ry = y + k < n ? rk[y + k] : -1;
            return rx < ry;
        };
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        swap(tmp, rk);
    }
    return sa;
}