# 코드 (1-based)
```cpp
template <typename T, typename Merge>
class fenwick_tree {
  const int sz;
  const T raw;
  vector<T> tree;
  Merge op;

public:
  fenwick_tree(int sz, const T& raw = T()) : sz(sz), raw(raw), tree(sz + 1, raw) {}

  void update(int i, const T& v) {
    for (;i <= sz;i += i & -i) tree[i] += v;
  }

  T Query(int i) {
    T s = raw;
    for (;i;i -= i & -i) s = op(s, tree[i]);
    return s;
  }
};
```

# 문제
* [구간 합 구하기](https://boj.kr/2042)
  * http://boj.kr/
* [구간 곱 구하기](https://boj.kr/11505)
  * http://boj.kr/