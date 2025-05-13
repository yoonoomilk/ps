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

  void apply(int i, const L &v) {
    tree[i] = upd(v, tree[i]);
    if(i < sz) lazy[i] = comp(v, lazy[i]);
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
  lazy_segment_tree(int n, const T &raw = T(), const L &lazy_raw = L())
  : lg(__lg(n * 2 - 1)), sz(1 << lg), raw(raw), lazy_raw(lazy_raw), tree(sz * 2, raw), lazy(sz * 2, lazy_raw) {}

  void set(int i, const T &v) {
    tree[i + sz] = v;
  }

  void init() {
    for(int i = sz;--i;) pull(i);
  }

  void update(int i, const L &v) {
    i += sz;
    for(int j = lg;j;j--) push(i >> j);
    apply(i, v);
    for(int j = 1;j <= lg;j++) pull(i >> j);
  }
  void update(int l, int r, const L &v) {
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

  T query(int i) {
    i += sz;
    for(int j = lg;j;j--) push(i >> j);
    return tree[i];
  }
  T query(int l, int r) {
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

/*
`lazy_segment_tree<T, L, Merge, Update, Composition> seg(n, raw, lazy_raw)`

* T : tree에 들어갈 타입
* L : lazy에 들어갈 타입
* Merge : `T operator() (const T& a, const T& b)`
  * non-lazy한 값끼리 합치기
* Update : `T operator() (const L& a, const T& b)`
  * non-lazy한 b에 lazy한 a를 적용
* Composition : `L operator() (const L& a, const L& b)`
  * lazy한 b에 lazy한 a 합치기
*/