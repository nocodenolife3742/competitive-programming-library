template<typename T, typename C>
struct mcmf {
    struct edge {
        int u, v;
        T cap, flow = 0;
        C cost;

        edge(int u, int v, T cap, C cost) : u(u), v(v), cap(cap), cost(cost) {}
    };

    int n;
    vector<edge> e;
    vector<vector<int> > adj;
    vector<C> dis, pot;
    vector<int> par;
    const C INF = numeric_limits<C>::max();

    mcmf(int n) : n(n), adj(n), dis(n), pot(n), par(n) {}

    void add_edge(int u, int v, T cap, C cost) {
        adj[u].push_back(e.size());
        e.emplace_back(u, v, cap, cost);
        adj[v].push_back(e.size());
        e.emplace_back(v, u, 0, -cost);
    }

    bool dijkstra(int s, int t) {
        fill(dis.begin(), dis.end(), INF);
        dis[s] = 0;
        priority_queue<pair<C, int>, vector<pair<C, int> >, greater<> > q;
        q.push({0, s});
        while (!q.empty()) {
            auto [d, u] = q.top();
            q.pop();
            if (d > dis[u]) continue;
            for (int i: adj[u]) {
                auto &[u, v, cap, flow, cost] = e[i];
                if (flow < cap && dis[v] > dis[u] + cost + pot[u] - pot[v]) {
                    dis[v] = dis[u] + cost + pot[u] - pot[v];
                    par[v] = i;
                    q.push({dis[v], v});
                }
            }
        }
        return dis[t] != INF;
    }

    pair<T, C> flow(int s, int t, T lim = numeric_limits<T>::max()) {
        T flow = 0;
        C cost = 0;
        while (dijkstra(s, t) && lim - flow > 0) {
            for (int i = 0; i < n; i++)
                if (dis[i] < INF) pot[i] += dis[i];
            T d = lim - flow;
            for (int u = t; u != s; u = e[par[u]].u)
                d = min(d, e[par[u]].cap - e[par[u]].flow);
            for (int u = t; u != s; u = e[par[u]].u) {
                e[par[u] ^ 0].flow += d;
                e[par[u] ^ 1].flow -= d;
                cost += d * e[par[u]].cost;
            }
            flow += d;
        }
        return {flow, cost};
    }
};