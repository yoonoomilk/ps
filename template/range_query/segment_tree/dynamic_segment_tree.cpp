template <typename T, typename Merge>
class dynamic_segment_tree {
  const ll sz;
  const T raw;
  struct node {
    int l, r;
    T v;
    node(const T& v) : l(-1), r(-1), v(v) {}
  };
  vector<node> tree;
  Merge op;

  int append() {
    tree.push_back(node(raw));
    return tree.size() - 1;
  }

  void update(int cur, ll s, ll e, ll i, T& v) {
    if(i < s || e < i) return;
    if(s == e) {
      tree[cur].v += v;
      return;
    }
    ll m = (s + e) / 2;
    if(tree[cur].l == -1) tree[cur].l = append();
    if(tree[cur].r == -1) tree[cur].r = append();
    update(tree[cur].l, s, m, i, v);
    update(tree[cur].r, m + 1, e, i, v);
    tree[cur].v = op(tree[tree[cur].l].v, tree[tree[cur].r].v);
  }

  T query(int cur, ll s, ll e, ll l, ll r) {
    if(cur == -1 || r < s || e < l) return raw;
    if(l <= s && e <= r) return tree[cur].v;
    ll m = (s + e) / 2;
    return op(
      query(tree[cur].l, s, m, l, r),
      query(tree[cur].r, m + 1, e, l, r)
    );
  }

public:
  dynamic_segment_tree(ll mx, T raw = T()) : sz(mx + 1), raw(raw) {
    append();
  }

  void update(ll i, T v) {
    update(0, 0, sz - 1, i, v);
  }

  T operator() (ll l, ll r) {
    return query(0, 0, sz - 1, l, r);
  }
};