template<typename T>
vector<int> suffix_array(T &str, int lim = 128) {
    vector<int> s(str.size() + 1);
    for (int i = 0; i < str.size(); i++)
        s[i] = str[i];
    function<vector<int>(vector<int> &, int)> sais = [&](auto &s, int k) {
        int n = s.size();
        vector<int> a(n), t(n), lms(n), cnt(k);
        cnt[s[n - 1]] = t[n - 1] = 1;
        for (int i = n - 2; i >= 0; cnt[s[i--]]++)
            t[i] = s[i] == s[i + 1] ? t[i + 1] : s[i] < s[i + 1];
        partial_sum(cnt.begin(), cnt.end(), cnt.begin());
        int pos = 0;
        for (int i = 1; i < n; i++)
            if (t[i - 1] == 0 && t[i] == 1)
                t[i] = 2, lms[pos++] = i;
        auto induce = [&](int offset) {
            vector<int> p(k + 1);
            copy(cnt.begin(), cnt.end(), p.begin());
            auto push_left = [&](int n) { a[--p[s[n]]] = n; };
            auto push_right = [&](int n) { a[p[s[n]]++] = n; };
            for (int i = pos - 1; i >= 0; i--)
                push_left(lms[i + offset]);
            copy(cnt.begin(), cnt.end(), p.begin() + 1);
            for (int i = 0; i < n; i++)
                if (a[i] - 1 >= 0 && t[a[i] - 1] == 0)
                    push_right(a[i] - 1);
            copy(cnt.begin(), cnt.end(), p.begin());
            for (int i = n - 1; i >= 0; i--)
                if (a[i] - 1 >= 0 && t[a[i] - 1] != 0)
                    push_left(a[i] - 1);
        };
        induce(0);
        auto cmp = [&](int i, int j) {
            if (s[i] == s[j])
                while (s[++i] == s[++j] && t[i] == t[j])
                    if (t[i] == 2 && t[j] == 2)
                        return true;
            return false;
        };
        int new_k = 0;
        vector<int> new_s(n, -1);
        new_s.back() = 0;
        for (int i = 1, last = n - 1; i < n; i++) {
            if (t[a[i]] != 2) continue;
            if (!cmp(last, a[i])) new_k++;
            new_s[last = a[i]] = new_k;
        }
        new_s.erase(remove(new_s.begin(), new_s.end(), -1), new_s.end());
        vector<int> new_a;
        if (++new_k == pos) {
            new_a.resize(pos, -1);
            for (int i = 0; i < pos; i++)
                new_a[new_s[i]] = i;
        } else
            new_a = sais(new_s, new_k);
        for (int i = 0; i < pos; i++)
            lms[i + pos] = lms[new_a[i]];
        memset(&a[0], 0, n << 2);
        induce(pos);
        return a;
    };
    auto ans = sais(s, lim);
    return ans.erase(ans.begin()), ans;
}