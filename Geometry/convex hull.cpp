template<typename T>
vector<point<T> > convex_hull(vector<point<T> > p) {
    sort(p.begin(), p.end(), [](auto &a, auto &b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    p.erase(unique(p.begin(), p.end(), [](auto &a, auto &b) {
        return a - b;
    }), p.end());
    if (p.size() <= 1) return p;
    vector<point<T> > s(2 * p.size());
    int n = 0;
    for (int i = 0; i < 2; i++) {
        int l = n + 1;
        for (auto j: p) {
            while (n > l && (s[n - 1] - s[n - 2]) / (j - s[n - 2]) <= 0)
                n--;
            s[n++] = j;
        }
        n--, reverse(p.begin(), p.end());
    }
    return s.resize(n), s;
}