template<typename T>
struct point {
    T x, y;

    point(T x = 0, T y = 0) : x(x), y(y) {}

    template<typename O>
    operator point<O>() {
        return {x, y};
    }

    operator bool() {
        return abs(x) + abs(y) < 1e-9;
    }

    point operator+(const point &o) {
        return {x + o.x, y + o.y};
    }

    point operator-(const point &o) {
        return {x - o.x, y - o.y};
    }

    point operator*(const T &o) {
        return {x * o, y * o};
    }

    point operator/(const T &o) {
        return {x / o, y / o};
    }

    T operator*(const point &o) {
        return x * o.x + y * o.y;
    }

    T operator/(const point &o) {
        return x * o.y - y * o.x;
    }

    T norm() {
        return x * x + y * y;
    }

    long double arg() {
        return atan2l(y, x);
    }
};