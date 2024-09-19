// 1. remember deal with null pointer
// 2. call up() when constuct new node

struct node {
    int rev = 0, sz = 1, pri = rand();
    node *lc = nullptr, *rc = nullptr;

    void down() {
        if (!rev) return;
        swap(lc, rc);
        if (lc) lc->rev ^= 1;
        if (rc) rc->rev ^= 1;
        rev = 0;
    }

    void up() {
        sz = (lc ? lc->sz : 0) + (rc ? rc->sz : 0) + 1;
    }
};

node *merge(node *a, node *b) {
    if (!a || !b) return a ? a : b;
    if (a->pri < b->pri) {
        a->down();
        a->rc = merge(a->rc, b);
        a->up();
        return a;
    }
    b->down();
    b->lc = merge(a, b->lc);
    b->up();
    return b;
}

pair<node *, node *> split(node *t, int k) {
    if (!t) return {nullptr, nullptr};
    t->down();
    int sz = (t->lc ? t->lc->sz : 0);
    if (k <= sz) {
        auto [tl, tr] = split(t->lc, k);
        t->lc = tr;
        t->up();
        return {tl, t};
    }
    auto [tl, tr] = split(t->rc, k - sz - 1);
    t->rc = tl;
    t->up();
    return {t, tr};
}

array<node *, 3> split_range(node *t, int l, int r) {
    auto [lt, rp] = split(t, r + 1);
    auto [lp, mp] = split(lt, l);
    return {lp, mp, rp};
}