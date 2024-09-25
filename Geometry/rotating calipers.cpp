// needed : convex hull
template<typename T>
auto rotating_calipers(vector<point<T> > &p) {
    auto h = convex_hull(p);
    auto nxt = [&](int v) { return (v + 1) % h.size(); };
    using info = pair<pair<point<T>, point<T> >, point<T> >;
    vector<info> ret(h.size());
    for (int i = 0, ptr = nxt(0); i < h.size(); i++) {
        while (abs((h[i] - h[nxt(i)]) / (h[nxt(i)] - h[ptr])) <
               abs((h[i] - h[nxt(i)]) / (h[nxt(i)] - h[nxt(ptr)])))
            ptr = nxt(ptr);
        ret[i] = {{h[i], h[nxt(i)]}, h[ptr]};
    }
    return ret;
}