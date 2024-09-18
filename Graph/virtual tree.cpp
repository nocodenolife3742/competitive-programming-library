// need : hld
vector<pair<int, int> > virtual_tree(hld &d, vector<int> p) {
    auto cmp = [&](int a, int b) {
        return d.pos[a] < d.pos[b];
    };
    sort(p.begin(), p.end(), cmp);
    for (int i = 1, n = p.size(); i < n; i++)
        p.push_back(d.lca(p[i - 1], p[i]));
    sort(p.begin(), p.end(), cmp);
    p.erase(unique(p.begin(), p.end()), p.end());
    vector<pair<int, int> > vt;
    for (int i = 1; i < p.size(); i++)
        vt.emplace_back(d.lca(p[i - 1], p[i]), p[i]);
    return vt;
}