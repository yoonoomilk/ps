template <typename T, typename Merge>
class dynamic_segment_tree {
  const int sz;
  const T raw;
  struct node {
    int l, r;
    T v;
    node(const T& a) : l(-1), r(-1), v(a) {}
  };
  vector<node> tree;
  Merge op;

  int append() {
    tree.push_back(node());
    return tree.size() - 1;
  }

  void update(int cur, int s, int e, int i, const T &v) {
    if(s == e) {
      tree[cur].v = v;
      return;
    }
    int m = (s + e) / 2;
    if(i <= m) {
      if(tree[cur].l == -1) tree[cur].l = append();
      update(tree[cur].l, s, m, i, v);
    } else {
      if(tree[cur].r == -1) tree[cur].r = append();
      update(tree[cur].r, m + 1, e, i, v);
    }
    tree[cur].v = op(
      tree[cur].l != -1 ? tree[tree[cur].l].v : raw,
      tree[cur].r != -1 ? tree[tree[cur].r].v : raw
    );
  }

  T query(int cur, int s, int e, int l, int r) {
    if(cur == -1 || r < s || e < l) return raw;
    if(l <= s && e <= r) return tree[cur].v;
    int m = (s + e) / 2;
    return op(
      query(tree[cur].l, s, m, l, r),
      query(tree[cur].r, m + 1, e, l, r)
    );
  }

public:
  dynamic_segment_tree(int mx, const T &raw = T()) : sz(mx + 1), raw(raw) {
    append();
  }

  void update(int i, const T &v) {
    update(0, 0, sz - 1, i, v);
  }

  T query(int l, int r) {
    return query(0, 0, sz - 1, l, r);
  }
};