template <typename T, typename Count>
class merge_sort_tree {
  const int sz;
  vector<vector<T>> tree;
  Count cnt;

public:
  template <typename I>
  merge_sort_tree(I s, I e) : sz(distance(s, e)), tree(sz + 1) {
    for(int i = 0;i < sz;i++) for(int j = i + 1;j <= sz;j += j & -j) tree[j].push_back(*s++);
    for(int i = 1;i <= sz;i++) sort(tree[i].begin(), tree[i].end());
  }

  int operator() (int i, T &k) {
    int s = 0;
    for(;i;i -= i & -i) s += cnt(tree[i], k);
    return s;
  }
  int operator() (int l, int r, T k) {
    return (*this)(r, k) - (*this)(l - 1, k);
  }
};

struct op {
  int operator() (vector<int>& v, int k) {
    return 0;
  }
};