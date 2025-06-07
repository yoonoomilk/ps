// 1-based

// 구간 갱신 점 쿼리
```cpp
template <typename T>
class fenwick_tree {
  const int sz;
  const T raw;
  vector<T> tree;

public:
  fenwick_tree(int sz, const T& raw = T()) : sz(sz), raw(raw), tree(sz + 1, raw) {}

  void update(int l, int r, const T& v) {
    for(;l <= sz;l += l & -l) tree[l] += v;
    for(r++;r <= sz;r += r & -r) tree[r] -= v;
  }

  T operator() (int i) {
    T s = raw;
    for(;i;i -= i & -i) s += tree[i];
    return s;
  }
};

// 점 갱신 구간 쿼리
template <typename T>
class fenwick_tree {
  const int sz;
  const T raw;
  vector<T> tree;

public:
  fenwick_tree(int sz, const T& raw = T()) : sz(sz), raw(raw), tree(sz + 1, raw) {}

  void update(int i, const T& v) {
    for(;i <= sz;i += i & -i) tree[i] += v;
  }

  T operator() (int i) {
    T s = raw;
    for(;i;i -= i & -i) s += tree[i];
    return s;
  }
  T operator() (int l, int r) {
    return (*this)(r) - (*this)(l - 1);
  }
};