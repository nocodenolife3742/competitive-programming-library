vector<vector<int> > bcc(const vector<vector<int> > &adj) {
    int n = adj.size();
    vector<int> pos(n, -1), stk;
    vector<vector<int> > res;
    function<int(int, int)> dfs = [&](int u, int p) {
        int low = pos[u] = stk.size(), mul = 0;
        stk.push_back(u);
        for (int v: adj[u]) {
            if (~pos[v]) {
                if (v != p || mul) low = min(low, pos[v]);
                else mul = 1;
                continue;
            }
            low = min(low, dfs(v, u));
        }
        if (low == pos[u]) {
            res.emplace_back(stk.begin() + low, stk.end());
            stk.resize(low);
        }
        return low;
    };
    for (int i = 0; i < n; i++) if (!~pos[i]) dfs(i, -1);
    return res;
}