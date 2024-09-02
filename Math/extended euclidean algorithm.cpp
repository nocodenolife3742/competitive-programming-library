array<i64, 3> exgcd(i64 a, i64 b) {
    if (b == 0) return {1, 0, a};
    auto [x, y, g] = exgcd(b, a % b);
    return {y, x - a / b * y, g};
}