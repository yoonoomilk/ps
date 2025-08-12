template <typename T, typename L, typename Merge, typename Update, typename Composition>
class segment_tree_beats {
  const int sz;
  const T raw;
  const L lazy_raw;
  vector<T> tree;
  vector<L> lazy;
  Merge op;
  Update upd;
  Composition comp;

  T init(int cur, int s, int e) {
    if(s == e) return tree[cur] = raw;
    int m = (s + e) / 2;
    return tree[cur] = op(init(cur * 2, s, m), init(cur * 2 + 1, m + 1, e));
  }

  void push(int cur, int s, int e) {
    if(lazy[cur] == lazy_raw) return;
    tree[cur] = upd(lazy[cur], tree[cur], e - s + 1);
    if(s != e) {
      lazy[cur * 2] = comp(lazy[cur], lazy[cur * 2]);
      lazy[cur * 2 + 1] = comp(lazy[cur], lazy[cur * 2 + 1]);
    }
    lazy[cur] = lazy_raw;
  }

  void update(int cur, int s, int e, int l, int r, L& v) {
    push(cur, s, e);
    if(r < s || e < l) return;
    if(break_condition) return;
    if(l <= s && e <= r) {
      if(tag_condition) {
        lazy[cur] = comp(v, lazy[cur]);
        push(cur, s, e);
        return;
      }
    }
    int m = (s + e) / 2;
    update(cur * 2, s, m, l, r, v);
    update(cur * 2 + 1, m + 1, e, l, r, v);
    tree[cur] = op(tree[cur * 2], tree[cur * 2 + 1]);
  }

  T query(int cur, int s, int e, int l, int r) {
    push(cur, s, e);
    if(r < s || e < l) return raw;
    if(l <= s && e <= r) return tree[cur];
    int m = (s + e) / 2;
    return op(query(cur * 2, s, m, l, r), query(cur * 2 + 1, m + 1, e, l, r));
  }

public:
  segment_tree_beats(int n, T raw = T(), L lazy_raw = L()) : sz(1 << __lg(n * 2 - 1)), raw(raw), lazy_raw(lazy_raw) , tree(sz * 2), lazy(sz * 2, lazy_raw) {
    init(1, 0, sz - 1);
  }

  void update(int l, int r, L v) {
    update(1, 0, sz - 1, l, r, v);
  }

  T operator() (int l, int r) {
    return query(1, 0, sz - 1, l, r);
  }
};