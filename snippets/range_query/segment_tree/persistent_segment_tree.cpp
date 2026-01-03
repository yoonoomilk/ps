template <typename T, typename Merge>
class persistent_segment_tree {
  const int sz;
  const T raw;
  struct node {
    int l, r;
    T v;
    node(const T& v) : l(-1), r(-1), v(v) {}
  };
  vector<node> tree;
  vector<int> root;
  Merge op;

  int append() {
    tree.push_back(node(raw));
    return tree.size() - 1;
  }

  void update(int prev, int cur, int s, int e, int i, T& v) {
    if(cur == -1 || s > i || e < i) return;
    if(s == e) {
      tree[cur].v = op(tree[cur].v, v);
      return;
    }
    if(tree[prev].l == -1) tree[prev].l = append();
    if(tree[prev].r == -1) tree[prev].r = append();
    int m = (s + e) / 2;
    if(i <= m) {
      int nxt = append();
      tree[nxt] = tree[tree[prev].l];
      tree[cur].l = nxt;
      tree[cur].r = tree[prev].r;
      update(tree[prev].l, tree[cur].l, s, m, i, v);
    } else {
      int nxt = append();
      tree[nxt] = tree[tree[prev].r];
      tree[cur].l = tree[prev].l;
      tree[cur].r = nxt;
      update(tree[prev].r, tree[cur].r, m + 1, e, i, v);
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
    return op(query(tree[cur].l, s, m, l, r), query(tree[cur].r, m + 1, e, l, r));
  }

public:
  persistent_segment_tree(int n, T raw = T()) : sz(n), raw(raw) {
    root.push_back(append());
  }

  int update(int i, T v) {
    int prev = root.back();
    root.push_back(append());
    update(prev, root.back(), 0, sz - 1, i, v);
    return root.size() - 1;
  }

  T query(int ver, int l, int r) {
    return query(root[ver], 0, sz - 1, l, r);
  }
};