vector<vector<int> > bvcc(vector<vector<int> > &adj) {
    int n = adj.size(), t = 0;
    vector<int> dfn(n), low(n), stk;
    vector<vector<int> > res;
    function<void(int)> dfs = [&](int u) {
        dfn[u] = low[u] = t++;
        stk.push_back(u);
        if (adj[u].empty()) res.push_back({u});
        for (int v: adj[u]) {
            if (dfn[v]) {
                low[u] = min(low[u], dfn[v]);
                continue;
            }
            dfs(v), low[u] = min(low[u], low[v]);
            if (low[v] == dfn[u]) {
                res.push_back({u});
                for (int w = -1; w != v; stk.pop_back())
                    res.back().push_back(w = stk.back());
            }
        }
    };
    for (int i = 0; i < n; i++) if (!dfn[i]) dfs(i);
    return res;
}