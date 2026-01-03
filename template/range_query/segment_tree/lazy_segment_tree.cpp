template <typename T, typename L, typename Merge, typename Update, typename Composition>
class lazy_segment_tree {
  const int lg, sz;
  const T raw;
  const L lazy_raw;
  vector<T> tree;
  vector<L> lazy;
  Merge op;
  Update upd;
  Composition comp;

  void apply(int i, L v) {
    upd(tree[i], v);
    if(i < sz) lazy[i] = comp(lazy[i], v);
  }

  void push(int i) {
    apply(i * 2, lazy[i]);
    apply(i * 2 + 1, lazy[i]);
    lazy[i] = lazy_raw;
  }

  void pull(int i) {
    tree[i] = op(tree[i * 2], tree[i * 2 + 1]);
  }

public:
  lazy_segment_tree(int n, T raw = T(), L lazy_raw = L())
  : lg(__lg(n * 2 - 1)), sz(1 << lg), raw(raw), lazy_raw(lazy_raw), tree(sz * 2, raw), lazy(sz, lazy_raw) {}

  void set(int i, const T& v) {
    tree[i + sz] = v;
  }
  void init() {
    for(int i = sz;--i;) pull(i);
  }

  void update(int i, L v) {
    i += sz;
    for(int j = lg;j;j--) push(i >> j);
    apply(i, v);
    for(int j = 1;j <= lg;j++) pull(i >> j);
  }
  void update(int l, int r, L v) {
    l += sz; r += sz;
    for(int i = lg;i;i--) {
      if(l >> i << i != l) push(l >> i);
      if(r + 1 >> i << i != r + 1) push(r >> i);
    }
    for(int s = l, e = r;s <= e;s /= 2, e /= 2) {
      if(s & 1) apply(s++, v);
      if(~e & 1) apply(e--, v);
    }
    for(int i = 1;i <= lg;i++) {
      if(l >> i << i != l) pull(l >> i);
      if(r + 1 >> i << i != r + 1) pull(r >> i);
    }
  }

  T operator() (int i) {
    i += sz;
    for(int j = lg;j;j--) push(i >> j);
    return tree[i];
  }
  T operator() (int l, int r) {
    l += sz; r += sz;
    T s1 = raw, s2 = raw;
    for(int i = lg;i;i--) {
      if(l >> i << i != l) push(l >> i);
      if(r + 1 >> i << i != r + 1) push(r >> i);
    }
    for(;l <= r;l /= 2, r /= 2) {
      if(l & 1) s1 = op(s1, tree[l++]);
      if(~r & 1) s2 = op(tree[r--], s2);
    }
    return op(s1, s2);
  }
};