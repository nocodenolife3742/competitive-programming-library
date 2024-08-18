istream &operator>>(istream &is, __int128 &v) {
    string s;
    is >> s;
    v = 0;
    for (auto &&i: s)
        if (isdigit(i))
            v = v * 10 + i - '0';
    if (s[0] == '-') v *= -1;
    return is;
}

ostream &operator<<(ostream &os, const __int128 &v) {
    if (v == 0) return os << '0';
    __int128 num = v;
    if (v < 0) os << '-', num = -num;
    string s;
    while (num) s.push_back(num % 10 + '0'), num /= 10;
    reverse(s.begin(), s.end());
    return os << s;
}