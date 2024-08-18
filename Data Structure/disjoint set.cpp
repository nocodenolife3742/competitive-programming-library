struct dsu {
    vector<int> p;

    dsu(int n) : p(n, -1) {}

    int par(int x) {
        return p[x] < 0 ? x : p[x] = par(p[x]);
    }

    bool same(int a, int b) {
        return par(a) == par(b);
    }

    int size(int x) {
        return -p[par(x)];
    }

    bool unite(int x, int y) {
        x = par(x), y = par(y);
        if (x == y) return false;
        if (p[x] > p[y]) swap(x, y);
        p[x] += p[y], p[y] = x;
        return true;
    }
};