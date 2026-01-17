template <typename T>
class lazy_fenwick_tree {
  using L = complex<T>;
  const int sz;
  vector<L> tree;

  T query(int i) {
    L s;
    int st = i;
    for(;i;i -= i & -i) s += tree[i];
    return s.real() * st + s.imag();
  }

public:
  lazy_fenwick_tree(int sz) : sz(sz), tree(sz + 1) {}

  void set(int i, const T& v) {
    tree[i] = complex<T>(T(), v);
  }
  void init() {
    for(int i = 1;i <= sz;i++) tree[i] += tree[i - 1];
    for(int i = sz;i;i--) tree[i] -= tree[i & i - 1];
  }

  void update(int l, int r, const T& v) {
    for(int i = l;i <= sz;i += i & -i) tree[i] += L(v, -v * (l - 1));
    for(int i = r + 1;i <= sz;i += i & -i) tree[i] += L(-v, v * r);
  }

  T operator() (int l, int r) {
    return query(r) - query(l - 1);
  }
};