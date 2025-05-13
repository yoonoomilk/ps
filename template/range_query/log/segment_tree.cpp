template <typename T, typename Merge>
class segment_tree {
  const int sz;
  const T raw;
  vector<T> tree;
  Merge op;

public:
  segment_tree(int n, const T &raw = T()) : sz(1 << __lg(n * 2 - 1)), raw(raw), tree(sz * 2, raw) {}

  void update(int i, const T &v) {
    i += sz;
    tree[i] = v;
    while (i /= 2) tree[i] = op(tree[i * 2], tree[i * 2 + 1]);
  }

  T query(int i) {
    return tree[i + sz];
  }
  T query(int l, int r) {
    l += sz; r += sz;
    T s1 = raw, s2 = raw;
    for (;l <= r;l /= 2, r /= 2) {
      if (l & 1) s1 = op(s1, tree[l++]);
      if (~r & 1) s2 = op(tree[r--], s2);
    }
    return op(s1, s2);
  }
};

// 추가
void assign(const vector<T> &raw) {
  for (int i = 0;i < raw.size();i++) tree[i + sz] = raw[i];
  for (int i = sz;--i;) tree[i] = op(tree[i * 2], op[i * 2 + 1]);
}

T top() {
  return tree[1];
}

// 최대 구간합
struct hoit {
  int p, l, r, a;
};

struct op {
  hoit operator() (const hoit& a, const hoit& b) const {
    hoit tmp;
    tmp.p = max({a.r + b.l, a.p, b.p});
    tmp.l = max(a.l, a.a + b.l);
    tmp.r = max(a.r + b.a, b.r);
    tmp.a = a.a + b.a;
    return tmp;
  }
};