template <typename T>
class fenwick_tree {
  const int sz;
  const T raw;
  vector<T> tree;

public:
  fenwick_tree(int sz, T raw = T()) : sz(sz), raw(raw), tree(sz + 1, raw) {}

  void update(int l, int r, T v) {
    for(;l <= sz;l += l & -l) tree[l] += v;
    for(r++;r <= sz;r += r & -r) tree[r] -= v;
  }

  T operator() (int i) {
    T s = raw;
    for(;i;i -= i & -i) s += tree[i];
    return s;
  }
};