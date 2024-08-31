struct hld {
    vector<vector<int> > adj;
    vector<int> dep, par, top, pos, hvy;

    hld(int n) : dep(n), par(n), top(n), pos(n), hvy(n, -1) {
        adj.assign(n, {});
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build(int root = 0) {
        function<int(int)> init = [&](int u) {
            int sz = 1, mx = -1;
            for (int v: adj[u]) {
                if (v == par[u]) continue;
                par[v] = u, dep[v] = dep[u] + 1;
                int csz = init(v);
                sz += csz;
                if (csz > mx) mx = csz, hvy[u] = v;
            }
            return sz;
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
        l.insert(l.end(), r.rbegin(), r.rend());
        return l;
    }
};