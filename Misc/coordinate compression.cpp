template<typename T>
vector<T> compress(vector<T> a) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    return a;
}

template<typename T>
int get_index(T val, const vector<T> &a) {
    return lower_bound(a.begin(), a.end(), val) - a.begin();
}