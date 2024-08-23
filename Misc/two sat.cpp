// needed : scc
struct two_sat {
    vector<vector<int> > adj;
    vector<bool> ans;

    two_sat(int n) : adj(2 * n), ans(n) {}

    void add_clause(int i, bool f, int j, bool g) {
        adj[2 * i + f].push_back(2 * j + !g);
        adj[2 * j + g].push_back(2 * i + !f);
    }

    bool vaild() {
        auto c = scc(adj);
        vector<int> id(adj.size());
        for (int i = 0; i < c.size(); i++)
            for (int j: c[i]) id[j] = i;
        for (int i = 0; i < ans.size(); i++) {
            if (id[i * 2] == id[i * 2 + 1])
                return false;
            ans[i] = id[i * 2] > id[i * 2 + 1];
        }
        return true;
    }
};