template<typename V, V (*f)(V, V), typename T,
    V (*mp)(T, V), T (*c)(T, T), T (*te)()>
struct segtree {
    struct node {
        V val;
        T tag;
        int l, r;
        node *lc, *rc;

        node(int l, int r) : l(l), r(r) {
            lc = rc = nullptr, tag = te();
        }

        void get(T new_tag) {
            val = mp(new_tag, val);
            tag = c(new_tag, tag);
        }

        void up() {
            if (lc && rc) val = f(lc->val, rc->val);
        }

        void down() {
            if (lc && rc) lc->get(tag), rc->get(tag);
            tag = te();
        }
    } *root;

    node *build(int l, int r, const vector<V> &a) {
        node *p = new node(l, r);
        if (l == r) return p->val = a[l], p;
        int m = l + r >> 1;
        p->lc = build(l, m, a);
        p->rc = build(m + 1, r, a);
        return p->up(), p;
    }

    void modify(int l, int r, T t, node *p = nullptr) {
        if (!p) return modify(l, r, t, root);
        if (p->r < l || p->l > r) return;
        p->down();
        if (l <= p->l && p->r <= r) return p->get(t);
        modify(l, r, t, p->lc), modify(l, r, t, p->rc);
        p->up();
    }

    V query(int l, int r, node *p = nullptr) {
        if (!p) return query(l, r, root);
        p->down();
        if (l <= p->l && p->r <= r) return p->val;
        int m = p->l + p->r >> 1;
        if (r <= m) return query(l, r, p->lc);
        if (l > m) return query(l, r, p->rc);
        return f(query(l, r, p->lc), query(l, r, p->rc));
    }

    segtree(const vector<V> &a) {
        root = build(0, a.size() - 1, a);
    }
};