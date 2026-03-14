template <typename T, typename Merge, T raw = T()>
class persistent_segment_tree {
  const int sz;
  struct node {
    int l = -1, r = -1;
    T v = raw;
  };
  vector<node> tree;
  vector<int> root;
  Merge op;

  int append() {
    tree.push_back({});
    return tree.size() - 1;
  }

  void update(int prev, int cur, int s, int e, int i, const T& v) {
    node tmp = ~prev ? tree[prev] : node();
    tree[cur] = tmp;
    tree[cur].v = op(tmp.v, v);
    if(s == e) return;
    int m = (s + e) / 2;
    if(i <= m) update(tmp.l, tree[cur].l = append(), s, m, i, v);
    else update(tmp.r, tree[cur].r = append(), m + 1, e, i, v);
  }

  T query(int cur, int s, int e, int l, int r) {
    if(cur == -1 || r < s || e < l) return raw;
    if(l <= s && e <= r) return tree[cur].v;
    int m = (s + e) / 2;
    return op(query(tree[cur].l, s, m, l, r), query(tree[cur].r, m + 1, e, l, r));
  }

public:
  persistent_segment_tree(int n) : sz(n) {
    root.push_back(-1);
  }

  int update(int prev, int i, const T& v) {
    root.push_back(append());
    update(root[prev], root.back(), 0, sz - 1, i, v);
    return root.size() - 1;
  }

  T operator() (int ver, int l, int r) {
    return query(root[ver], 0, sz - 1, l, r);
  }
};