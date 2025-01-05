# 코드 (**NOT DONE**)
```cpp
template <typename T>
class lazy_segtree {
  int sz = 1;
  const T raw;
  vector<T> arr;
  vector<T> lazy;
  function<T(T, T)> op;
  function<T(T, T, int)> ops;

public:
  lazy_segtree(int n, function<T(T, T)> op, function<T(T, T, int)> ops, T raw = T())
    : op(op), ops(ops), raw(raw) {
    while (sz < n) sz *= 2;
    arr.resize(2 * sz, raw);
    lazy.resize(sz, raw);
  }

  void update(int a, T x) {
    a += sz;
    arr[a] = x;
    while (a /= 2) arr[a] = op(arr[a * 2], arr[a * 2 + 1]);
  }

  T query(int l, int r) {
    l += sz;
    r += sz;
    T s1 = raw, s2 = raw;
    while (l <= r) {
      if (l % 2 == 1) s1 = op(s1, arr[l++]);
      if (r % 2 == 0) s2 = op(arr[r--], s2);
      l /= 2;
      r /= 2;
    }
    return op(s1, s2);
  }

  T value(int a) {
    a += sz;
    return arr[a];
  }

  T top() {
    return arr[1];
  }
};
```