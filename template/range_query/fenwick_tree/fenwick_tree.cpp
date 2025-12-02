template <typename T>
class fenwick_tree {
  const int sz;
  vector<T> tree;

public:
  fenwick_tree(int sz) : sz(sz), tree(sz + 1) {}

  void update(int i, T v) {
    for(;i <= sz;i += i & -i) tree[i] += v;
  }

  T operator() (int i) {
    T s = 0;
    for(;i;i -= i & -i) s += tree[i];
    return s;
  }
  T operator() (int l, int r) {
    return (*this)(r) - (*this)(l - 1);
  }
};

void set(int i, T v) {
  tree[i] = v;
}

void init() {
  for(int i = 1;i <= sz;i++) tree[i] += tree[i - 1];
  for(int i = sz;i;i--) tree[i] -= tree[i & i - 1];
}