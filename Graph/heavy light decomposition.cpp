struct hld {
    vector<vector<int> > adj;
    vector<int> dep, top, pos, par, hvy, sz;

    hld(int n) : adj(n), par(n, -1), hvy(n, -1), sz(n, 1) {
        dep = top = pos = vector<int>(n);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build(int root = 0) {
        function<void(int)> init = [&](int u) {
            for (int &v: adj[u]) {
                if (v == par[u]) continue;
                par[v] = u, dep[v] = dep[u] + 1;
                init(v), sz[u] += sz[v];
                if (!~hvy[u] || sz[v] > sz[hvy[u]])
                    hvy[u] = v;
            }
        };
        int t = 0;
        function<void(int, int)> sep = [&](int u, int h) {
            top[u] = h, pos[u] = t++;
            if (hvy[u] != -1) sep(hvy[u], h);
            for (int v: adj[u])
                if (v != par[u] && v != hvy[u])
                    sep(v, v);
        };
        init(root), sep(root, root);
    }

    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = par[top[u]];
        }
        return dep[u] > dep[v] ? v : u;
    }

    vector<pair<int, int> > find_path(int u, int v) {
        vector<pair<int, int> > l, r;
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]])
                l.emplace_back(u, top[u]), u = par[top[u]];
            else
                r.emplace_back(top[v], v), v = par[top[v]];
        }
        l.emplace_back(u, v);
        return l.insert(l.end(), r.rbegin(), r.rend()), l;
    }
};