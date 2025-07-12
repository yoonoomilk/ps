template <typename T, typename L, typename Merge, typename Update, typename Composition>
class segment_tree_beats {
  const int lg, sz;
  const T raw;
  const L lazy_raw;
  vector<T> tree;
  vector<L> lazy;
  Merge op;
  Update upd;
  Composition comp;

  void apply(int i, const L& v) {
    tree[i] = upd(v, tree[i]);
    if(i < sz) {
      lazy[i] = comp(v, lazy[i]);
      if(tree[i].fail) {
        push(i);
        pull(i);
      }
    }
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
  segment_tree_beats(int n, T raw = T(), L lazy_raw = L())
  : lg(__lg(n * 2 - 1)), sz(1 << lg), raw(raw), lazy_raw(lazy_raw), tree(sz * 2, raw), lazy(sz * 2, lazy_raw) {}

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

// 수쿼 26
struct hoit {
  ll max1, max2, sum;
  int cnt;
  bool fail;
};

struct op {
  hoit operator() (hoit &a, hoit &b) {
    hoit tmp;
    tmp.sum = a.sum + b.sum;
    tmp.max1 = max(a.max1, b.max1);
    if(a.max1 < b.max1) {
      tmp.cnt = b.cnt;
      tmp.max2 = max(b.max2, a.max1);
    } else if(a.max1 > b.max1) {
      tmp.cnt = a.cnt;
      tmp.max2 = max(a.max2, b.max1);
    } else {
      tmp.cnt = a.cnt + b.cnt;
      tmp.max2 = max(a.max2, b.max2);
    }
    return tmp;
  }
};

struct upd {
  hoit operator() (ll a, hoit b) {
    if(a >= b.max1) {}
    else if(a > b.max2) {
      b.sum -= (b.max1 - a) * b.cnt;
      b.max1 = a;
    } else b.fail = true;
    return b;
  }
};

struct comp {
  ll operator() (ll a, ll b) {
    return min(a, b);
  }
};