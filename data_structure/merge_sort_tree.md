# 코드
```cpp
template <typename T, typename Count>
class merge_sort_tree {
  const int sz;
  vector<vector<T>> tree;
  Count cnt;

public:
  template <typename I>
  merge_sort_tree(int n, I s) : sz(1 << __lg(n * 2 - 1)), tree(sz * 2) {
    for(int i = 0;i < n;i++) tree[i + sz].push_back(s[i]);
    for(int i = sz;--i;) {
      auto &l = tree[i * 2], &r = tree[i * 2 + 1];
      tree[i].resize(l.size() + r.size());
      merge(l.begin(), l.end(), r.begin(), r.end(), tree[i].begin());
    }
  }

  int query(int l, int r, const T& k) {
    l += sz; r += sz;
    int s = 0;
    for(;l <= r;l /= 2, r /= 2) {
      if(l & 1) s += cnt(tree[l++], k);
      if(~r & 1) s += cnt(tree[r--], k);
    }
    return s;
  }
};
```

# 문제
* [수열과 쿼리 1](https://boj.kr/13537)
  * http://boj.kr/dcad82fba6374b9dac65cd3846be3d15
* [수열과 쿼리 3](https://boj.kr/13544)
  * http://boj.kr/b238a74b209a406486a82180f2793b47
* [K번째 수](https://boj.kr/7469)
  * http://boj.kr/2c605b1d357e4fcc9adac0e2b056a212
* [서로 다른 수와 쿼리 2](https://boj.kr/14898)
  * http://boj.kr/6939fd8112fa469a82e4e86ffc49029f