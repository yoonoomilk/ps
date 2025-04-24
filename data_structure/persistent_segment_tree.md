# 코드 (**not done**)
```cpp
template <typename T, typename Merge>
class segment_tree {
  const int mx;
  const T raw;
  struct node {
    int l, r;
    T v;
    node() : l(-1), r(-1) {
      v = raw;
    }
  };
  vector<node> tree;
  vector<int> nth;
  Merge op;

  int append() {
    int tmp = tree.size();
    tree.push_back(node());
    return tmp;
  }

  void update(int cur, int s, int e, int x, const T &v) {
    if (s == e) {
      tree[cur].v = v;
      return;
    }
    int m = (s + e) / 2;
    if (x <= m) {
      if (tree[cur].l == -1) tree[cur].l = append();
      update(tree[cur].l, s, m, x, v);
    } else {
      if (tree[cur].r == -1) tree[cur].r = append();
      update(tree[cur].r, m + 1, e, x, v);
    }
    tree[cur].v = op(
      tree[cur].l != -1 ? tree[tree[cur].l].v : raw,
      tree[cur].r != -1 ? tree[tree[cur].r].v : raw
    );
  }

  T query(int cur, int s, int e, int l, int r) {
    if (cur == -1) return raw;
    if (r < s || e < l) return raw;
    if (l <= s && e <= r) return tree[cur].v;
    int m = (s + e) / 2;
    return query(tree[cur].l, s, m, l, r) + query(tree[cur].r, m + 1, e, l, r);
  }

public:
  segment_tree(int mx, const T &raw = T()) : mx(mx), raw(raw) {
    nth.push_back(append());
  }

  void update(int i, const T &x) {
    update(0, 0, mx, i, x);
  }

  T query(int l, int r) {
    return query(0, 0, mx, l, r);
  }
};
```