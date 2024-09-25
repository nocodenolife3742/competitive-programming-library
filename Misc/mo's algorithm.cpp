struct query {
    int l, r, idx;
};

template<int K, typename T, T (*add)(int), T (*sub)(int)>
vector<T> mo(vector<query> q) {
    sort(q.begin(), q.end(), [](query &a, query &b) {
        if (a.l / K == b.l / K)
            return a.l / K & 1 ? a.r < b.r : a.r > b.r;
        return a.l < b.l;
    });
    T val;
    int l = 0, r = -1;
    vector<T> ans(q.size());
    for (auto &[ql, qr, idx]: q) {
        while (l < ql) val = sub(l++);
        while (l > ql) val = add(--l);
        while (r < qr) val = add(++r);
        while (r > qr) val = sub(r--);
        ans[idx] = val;
    }
    return ans;
}