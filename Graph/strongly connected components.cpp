vector<vector<int> > scc(const vector<vector<int> > &adj) {
    int n = adj.size();
    vector<int> pos(n, -1), vis(n), stk;
    vector<vector<int> > res;
    function<int(int)> dfs = [&](int u) {
        int low = pos[u] = stk.size();
        stk.push_back(u);
        for (int v: adj[u])
            if (!vis[v])
                low = min(low, ~pos[v] ? pos[v] : dfs(v));
        if (low == pos[u]) {
            res.emplace_back(stk.begin() + low, stk.end());
            for (int v: res.back()) vis[v] = true;
            stk.resize(low);
        }
        return low;
    };
    for (int i = 0; i < n; i++) if (!vis[i]) dfs(i);
    return reverse(res.begin(), res.end()), res;
}