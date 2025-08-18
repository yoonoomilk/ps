template <typename T, typename L, typename Merge, typename Update, typename Composition>
class sparse_segment_tree {
  const int sz;
  const T raw;
  const L lazy_raw;
  struct node {
    int l, r;
    T v;
    L lazy;
    node(const T &a, const L &b) : l(-1), r(-1), v(a), lazy(b) {}
  };
  vector<node> tree;
  Merge op;
  Update upd;
  Composition comp;

  int append() {
    tree.push_back(node(raw, lazy_raw));
    return tree.size() - 1;
  }

  void push(int cur, int s, int e) {
    if(cur == -1 || tree[cur].lazy == lazy_raw) return;
    upd(tree[cur].v, tree[cur].lazy, e - s + 1);
    if(s != e) {
      if(tree[cur].l == -1) tree[cur].l = append();
      if(tree[cur].r == -1) tree[cur].r = append();
      tree[tree[cur].l].lazy = comp(tree[tree[cur].l].lazy, tree[cur].lazy);
      tree[tree[cur].r].lazy = comp(tree[tree[cur].r].lazy, tree[cur].lazy);
    }
    tree[cur].lazy = lazy_raw;
  }

  void update(int cur, int s, int e, int l, int r, L& v) {
    push(cur, s, e);
    if(r < s || e < l) return;
    if(l <= s && e <= r) {
      tree[cur].lazy = comp(v, tree[cur].lazy);
      push(cur, s, e);
      return;
    }
    int m = (s + e) / 2;
    if(tree[cur].l == -1) tree[cur].l = append();
    if(tree[cur].r == -1) tree[cur].r = append();
    update(tree[cur].l, s, m, l, r, v);
    update(tree[cur].r, m + 1, e, l, r, v);
    tree[cur].v = op(tree[tree[cur].l].v, tree[tree[cur].r].v);
  }

  T query(int cur, int s, int e, int l, int r) {
    if(cur == -1 || r < s || e < l) return raw;
    push(cur, s, e);
    if(l <= s && e <= r) return tree[cur].v;
    int m = (s + e) / 2;
    return op(
      query(tree[cur].l, s, m, l, r),
      query(tree[cur].r, m + 1, e, l, r)
    );
  }

public:
  sparse_segment_tree(int mx, T raw = T(), L lazy_raw = L()) : sz(mx + 1), raw(raw), lazy_raw(lazy_raw) {
    append();
  }

  void update(int l, int r, L v) {
    update(0, 0, sz - 1, l, r, v);
  }

  T operator() (int l, int r) {
    return query(0, 0, sz - 1, l, r);
  }
};

struct op {
  ll operator() (ll a, ll b) {
    return a + b;
  }
};

struct upd {
  void operator() (ll &a, ll b, int cnt) {
    a += b * cnt;
  }
};

struct comp {
  ll operator() (ll a, ll b) {
    return a + b;
  }
};