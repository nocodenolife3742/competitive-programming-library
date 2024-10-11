// return sum of floor((a * i + b) / m) for all i = 0 ~ n - 1
i64 floor_sum(i64 n, i64 m, i64 a, i64 b) {
    if (m == 0) return 0;
    i64 ans = a / m * n * (n - 1) / 2 + b / m * n;
    a %= m, b %= m;
    i64 y = (a * (n - 1) + b) / m;
    ans += y * (n - 1) - floor_sum(y, a, m, m - b - 1);
    return ans;
}