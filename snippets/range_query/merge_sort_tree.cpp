template <typename T, typename Count>
class merge_sort_tree {
  const int sz;
  vector<vector<T>> tree;
  vector<pair<T, int>> loc;
  Count cnt;

public:
  merge_sort_tree(int n) : sz(n + 1), tree(sz + 1), loc(sz, {T(), -1}) {}

  void set(int i, const T& v) {
    loc[i] = {v, i};
  }
  void init() {
    sort(loc.begin(), loc.end());
    for(int i = 0;i < sz;i++) if(loc[i].second != -1) {
      for(int j = loc[i].second;j <= sz;j += j & -j) tree[j].push_back(loc[i].first);
    }
  }

  int operator() (int i, const T& k) {
    int s = 0;
    for(;i;i -= i & -i) s += cnt(tree[i], k);
    return s;
  }
  int operator() (int l, int r, const T& k) {
    return (*this)(r, k) - (*this)(l - 1, k);
  }
};

struct op {
  int operator() (const vector<int>& v, int k) {
    return v.end() - upper_bound(v.begin(), v.end(), k);
  }
};