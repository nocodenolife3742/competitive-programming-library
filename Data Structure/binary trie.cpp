template<typename T, int B>
struct btrie {
    vector<array<int, 2> > nxt{{0, 0}};
    vector<int> cnt{0};

    void insert(T num) {
        for (int i = B - 1, n = 0; i >= 0; i--) {
            int t = (num >> i) & 1;
            if (!nxt[n][t]) {
                nxt[n][t] = nxt.size();
                nxt.push_back({0, 0});
                cnt.push_back(0);
            }
            n = nxt[n][t], cnt[n]++;
        }
    }

    bool remove(T num) {
        if (!exist(num)) return false;
        for (int i = B - 1, n = 0; i >= 0; i--)
            n = nxt[n][(num >> i) & 1], cnt[n]--;
        return true;
    }

    bool exist(T num, T x = 0) {
        for (int i = B - 1, n = 0; i >= 0; i--) {
            int t = ((num ^ x) >> i) & 1;
            if (!nxt[n][t] || !cnt[nxt[n][t]])
                return false;
            n = nxt[n][t];
        }
        return true;
    }

    T find(T x = 0, bool mn = false) {
        for (int i = B - 1, n = 0; i >= 0; i--) {
            T t = (x >> i) & 1;
            if (mn) t ^= 1;
            if (nxt[n][1 ^ t] && cnt[nxt[n][1 ^ t]])
                t ^= 1;
            n = nxt[n][t], x ^= t << i;
        }
        return x;
    }
};