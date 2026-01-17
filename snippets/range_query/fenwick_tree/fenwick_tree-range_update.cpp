template <typename T>
class fenwick_tree {
  const int sz;
  vector<T> tree;

public:
  fenwick_tree(int sz) : sz(sz), tree(sz + 1) {}

  void update(int l, int r, const T& v) {
    for(;l <= sz;l += l & -l) tree[l] += v;
    for(r++;r <= sz;r += r & -r) tree[r] -= v;
  }

  T operator() (int i) {
    T s = 0;
    for(;i;i -= i & -i) s += tree[i];
    return s;
  }
};