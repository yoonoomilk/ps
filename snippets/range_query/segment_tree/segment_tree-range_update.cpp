template <typename T, typename Merge, T raw = T()>
class segment_tree {
  const int sz;
  vector<T> tree;
  Merge op;

public:
  segment_tree(int n) : sz(1 << __lg(n * 2 - 1)), tree(sz * 2, raw) {}

  void update(int i, const T& v) {
    i += sz;
    tree[i] = op(tree[i], v);
  }

  void update(int l, int r, const T& v) {
    l += sz; r += sz;
    for(;l <= r;l /= 2, r /= 2) {
      if(l & 1) tree[l] = op(tree[l], v), l++;
      if(~r & 1) tree[r] = op(tree[r], v), r--;
    }
  }

  T operator() (int i) {
    i += sz;
    T s = raw;
    for(;i;i /= 2) s = op(s, tree[i]);
    return s;
  }
};