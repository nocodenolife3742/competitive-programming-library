// time complexity : O(V^2E)
template<typename T>
struct dinic {
    struct edge {
        int u, v;
        T cap, flow = 0;

        edge(int u, int v, T c) : u(u), v(v), cap(c) {}
    };

    int n;
    vector<edge> e;
    vector<vector<int> > adj;
    T bound;

    dinic(int n) : n(n), adj(n), bound(0) {}

    void add_edge(int u, int v, T c) {
        adj[u].push_back(e.size());
        e.emplace_back(u, v, c);
        adj[v].push_back(e.size());
        e.emplace_back(v, u, 0);
        bound += c;
    }

    T flow(int s, int t) {
        vector<int> lv(n), p(n);
        auto bfs = [&]() {
            fill_n(lv.begin(), n, -1), lv[s] = 0;
            queue<int> q({s});
            while (!q.empty()) {
                for (int i: adj[q.front()]) {
                    auto &[u, v, c, f] = e[i];
                    if (f >= c || lv[v] != -1) continue;
                    lv[v] = lv[u] + 1, q.push(v);
                }
                q.pop();
            }
            return lv[t] != -1;
        };
        function<T(int, T)> dfs = [&](int a, T up) {
            if (a == t) return up;
            T used = 0;
            for (int &i = p[a]; i < adj[a].size(); i++) {
                auto &[u, v, c, f] = e[adj[a][i]];
                if (f >= c || lv[u] + 1 != lv[v]) continue;
                T d = dfs(v, min(up - used, c - f));
                if (d == 0) continue;
                e[adj[u][i] ^ 0].flow += d;
                e[adj[u][i] ^ 1].flow -= d;
                used += d;
                if (used == up) break;
            }
            return used;
        };
        T ret = 0;
        while (bfs()) {
            fill_n(p.begin(), n, 0);
            while (T f = dfs(s, bound)) ret += f;
        }
        return ret;
    }
};
