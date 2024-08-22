vector<vector<int> > becc(vector<vector<int> > &adj) {
    int n = adj.size(), t = 0;
    vector<int> dfn(n), low(n), stk;
    vector<vector<int> > res;
    function<void(int, int)> dfs = [&](int u, int p) {
        dfn[u] = low[u] = ++t;
        stk.push_back(u);
        for (int v: adj[u]) {
            if (v == p) { p = -1; continue; }
            if (dfn[v]) {
                low[u] = min(low[u], dfn[v]);
                continue;
            }
            dfs(v, u), low[u] = min(low[u], low[v]);
        }
        if (low[u] == dfn[u]) {
            res.push_back({});
            for (int w = -1; w != u; stk.pop_back())
                res.back().push_back(w = stk.back());
        }
    };
    for (int i = 0; i < n; i++) if (!dfn[i]) dfs(i, -1);
    return res;
}