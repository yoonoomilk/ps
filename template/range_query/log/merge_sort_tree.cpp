template <typename T, typename Count>
class merge_sort_tree {
  const int sz;
  vector<vector<T>> tree;
  Count cnt;

public:
  template <typename I>
  merge_sort_tree(I s, I e) : sz(1 << __lg(distance(s, e) * 2 - 1)), tree(sz * 2) {
    for(int i = 0;s + i != e;i++) tree[i + sz].push_back(s[i]);
    for(int i = sz;--i;) {
      auto &l = tree[i * 2], &r = tree[i * 2 + 1];
      tree[i].resize(l.size() + r.size());
      merge(l.begin(), l.end(), r.begin(), r.end(), tree[i].begin());
    }
  }

  int operator() (int l, int r, const T& k) {
    l += sz; r += sz;
    int s = 0;
    for(;l <= r;l /= 2, r /= 2) {
      if(l & 1) s += cnt(tree[l++], k);
      if(~r & 1) s += cnt(tree[r--], k);
    }
    return s;
  }
};

struct op {
  int operator() (const vector<int>& v, const int& k) {
    return 0;
  }
};