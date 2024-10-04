template<typename T, bool get_min>
struct lichao {
    struct line {
        T a, b;

        line(T a, T b) : a(a), b(b) {}

        T operator()(T x) const { return a * x + b; }
    };

    int n;
    vector<line> fs;
    vector<T> xs;

    lichao(const vector<T> &x) : xs(x) {
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        n = xs.size();
        fs.assign(n << 1, line(0, numeric_limits<T>::max()));
    }

    void update(T a, T b, int l, int r) {
        if (!get_min) a = -a, b = -b;
        line g(a, b);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) descend(g, l++);
            if (r & 1) descend(g, --r);
        }
    }

    void descend(line g, int i) {
        int l = i, r = i + 1;
        while (l < n) l <<= 1, r <<= 1;
        while (l < r) {
            int c = (l + r) >> 1;
            T xl = xs[l - n], xc = xs[c - n], xr = xs[r - 1 - n];
            line &f = fs[i];
            if (f(xl) <= g(xl) && f(xr) <= g(xr)) return;
            if (f(xl) >= g(xl) && f(xr) >= g(xr))
                return f = g, void();
            if (f(xc) > g(xc)) swap(f, g);
            if (f(xl) > g(xl)) i = i << 1 | 0, r = c;
            else i = i << 1 | 1, l = c;
        }
    }

    void add_line(T a, T b) { update(a, b, 0, n); }

    void add_seg(T a, T b, T xl, T xr, bool closed = false) {
        int l = lower_bound(xs.begin(), xs.end(), xl) - xs.begin();
        int r = lower_bound(xs.begin(), xs.end(), xr) - xs.begin();
        if (closed) r = upper_bound(xs.begin(), xs.end(), xr) - xs.begin();
        update(a, b, l, r);
    }

    T get(T x) const {
        int i = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        assert(i != n && x == xs[i]);
        T y = numeric_limits<T>::max();
        for (i += n; i > 0; i >>= 1) y = min(y, fs[i](x));
        return get_min ? y : -y;
    }
};