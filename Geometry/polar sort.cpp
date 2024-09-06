template<typename T>
struct polar_sort {
    static bool up(point<T> &p) {
        return p.y > 0 || (!p.y && p.x < 0);
    }

    static bool cmp(point<T> &a, point<T> &b) {
        if (!is_integral_v<T>)
            return a.arg() < b.arg();
        if (up(a) == up(b))
            return !a && !b ? a / b > 0 : a < b;
        return up(a) < up(b);
    }
};