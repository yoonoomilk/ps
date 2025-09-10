template <typename T>
class fenwick_tree {
  const int sz;
  const T raw;
  vector<T> tree;

public:
  fenwick_tree(int sz, T raw = T()) : sz(sz), raw(raw), tree(sz + 1, raw) {}

  void update(int i, T v) {
    for(;i <= sz;i += i & -i) tree[i] += v;
  }

  T operator() (int i) {
    T s = raw;
    for(;i;i -= i & -i) s += tree[i];
    return s;
  }
  T operator() (int l, int r) {
    return (*this)(r) - (*this)(l - 1);
  }
};