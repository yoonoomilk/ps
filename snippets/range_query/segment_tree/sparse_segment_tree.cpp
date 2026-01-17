template <typename T, typename L, typename Merge, typename Update, typename Composition, T raw = T(), L lazy_raw = L()>
class sparse_segment_tree {
  const int sz;
  struct node {
    int l = -1, r = -1;
    T v = raw;
    L lazy = lazy_raw;
  };
  vector<node> tree;
  Merge op;
  Update upd;
  Composition comp;

  int append() {
    tree.push_back(node());
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

  void update(int cur, int s, int e, int l, int r, const L& v) {
    push(cur, s, e);
    if(r < s || e < l) return;
    if(l <= s && e <= r) {
      tree[cur].lazy = comp(tree[cur].lazy, v);
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
  sparse_segment_tree(int mx) : sz(mx + 1) {
    append();
  }

  void update(int l, int r, const L& v) {
    update(0, 0, sz - 1, l, r, v);
  }

  T operator() (int l, int r) {
    return query(0, 0, sz - 1, l, r);
  }
};