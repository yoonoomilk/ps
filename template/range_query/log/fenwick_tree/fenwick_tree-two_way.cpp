template <typename T, typename Merge>
class fenwick_tree {
  const int sz;
  const T raw;
  Merge op;
  vector<T> arr, tree1, tree2;

public:
  fenwick_tree(int sz, T raw = T()) : sz(sz), raw(raw), arr(sz + 1, raw), tree1(sz + 1, raw), tree2(sz + 1, raw) {}
  
  void update(int i, T v) {
    T tmp = arr[i] = v;
    for(int j = i, l = i - 1, r = i + 1;j <= sz;j += j & -j) {
      for(;l > j - (j & -j);l -= l & -l) tmp = op(tree1[l], tmp);
      for(;r < j;r += r & -r) tmp = op(tmp, tree2[r]);
      tree1[j] = i ^ j ? op(tmp, arr[j]) : tmp;
    }
    tmp = v;
    for(int j = i, l = i - 1, r = i + 1;j;j -= j & -j) {
      for(;l > j;l -= l & -l) tmp = op(tree1[l], tmp);
      for(;r <= sz && r < j + (j & -j);r += r & -r) tmp = op(tmp, tree2[r]);
      tree2[j] = i ^ j ? op(arr[j], tmp) : tmp;
    }
  }

  T operator() (int l, int r) {
    T s1 = raw, s2 = raw;
    int i;
    for(i = l;i + (i & -i) <= r;i += i & -i) s1 = op(s1, tree2[i]);
    for(i = r;i - (i & -i) >= l;i -= i & -i) s2 = op(tree1[i], s2);
    return op(op(s1, arr[i]), s2);
  }
};

// TODO: with 2 array