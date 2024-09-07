vector<int> kmp_nxt(string &s) {
    vector<int> nxt(s.size(), 0);
    for (int i = 1, j = 0; i < s.size(); nxt[i++] = j) {
        while (j > 0 && s[i] != s[j]) j = nxt[j - 1];
        if (s[i] == s[j]) j++;
    }
    return nxt;
}