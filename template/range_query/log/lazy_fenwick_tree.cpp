template <typename T>
class lazy_fenwick_tree {
  using L = complex<T>;
  const int sz;
  vector<L> tree;

  void _update(int i, L v) {
    for(;i <= sz;i += i & -i) tree[i] += v;
  }

public:
  lazy_fenwick_tree(int sz) : sz(sz), tree(sz + 1) {}

  void update(int l, int r, T v) {
    _update(l, L(v, -v * (l - 1)));
    _update(r + 1, L(-v, v * r));
  }

  T operator() (int i) {
    L s;
    int st = i;
    for(;i;i -= i & -i) s += tree[i];
    return s.real() * st + s.imag();
  }
  T operator() (int l, int r) {
    return (*this)(r) - (*this)(l - 1);
  }
};