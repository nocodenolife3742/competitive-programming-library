template<typename T>
vector<int> manacher(const T &s) {
    if (s.empty()) return {};
    string t(s.size() * 2 + 1, '.');
    for (int i = 0; i < s.size(); i++)
        t[i * 2 + 1] = s[i];
    int n = t.size(), m = 0, r = 0;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = r > i ? min(r - i, p[2 * m - i]) : 1;
        while (0 <= i - p[i] && i + p[i] < n &&
               t[i - p[i]] == t[i + p[i]])
            p[i]++;
        if (i + p[i] > r) m = i, r = i + p[i];
    }
    for (int i = 0; i < n; i++) p[i]--;
    return p;
}