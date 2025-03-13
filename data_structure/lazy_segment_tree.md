# 코드 (**NOT DONE**)
```cpp
template <typename T>
class lazy_segment_tree {
  int sz = 1;
  T raw;
  vector<T> arr, lazy;
  function<T(T, T)> op;
  function<T(T, T, int)> ops;

  void propagate(int a) {
    for (int h = __lg(sz);h > 0;h--) if (int i = a >> h;lazy[i] != raw){
      arr[i * 2] = ops(arr[i * 2], lazy[i], sz / (1 << h));
      arr[i * 2 + 1] = ops(arr[i * 2 + 1], lazy[i], sz / (1 << h));
      lazy[i * 2] += lazy[i];
      lazy[i * 2 + 1] += lazy[i];
      lazy[i] = raw;
    }
  }

public:
  lazy_segment_tree(int n, function<T(T, T)> op, function<T(T, T, int)> ops, T raw = T())
    : op(op), ops(ops), raw(raw) {
    while (sz < n) sz *= 2;
    arr.resize(2 * sz, raw);
    lazy.resize(2 * sz, raw);
  }

  void update_range(int l, int r, T x) {
    l += sz;
    r += sz;
    int l0 = l, r0 = r;
    
    while (l <= r) {
      if (l % 2 == 1) {
        arr[l] = ops(arr[l], x, 1);
        lazy[l] += x;
        l++;
      }
      if (r % 2 == 0) {
        arr[r] = ops(arr[r], x, 1);
        lazy[r] += x;
        r--;
      }
      l /= 2;
      r /= 2;
    }
    
    for (int i = l0 / 2;i > 0;i /= 2) arr[i] = op(arr[i * 2], arr[i * 2 + 1]);
    for (int i = r0 / 2;i > 0;i /= 2) arr[i] = op(arr[i * 2], arr[i * 2 + 1]);
  }

  T query(int l, int r) {
    l += sz; propagate(l);
    r += sz; propagate(r);
    T s1 = raw, s2 = raw;
    while (l <= r) {
      if (l % 2 == 1) s1 = op(s1, arr[l++]);
      if (r % 2 == 0) s2 = op(arr[r--], s2);
      l /= 2;
      r /= 2;
    }
    return op(s1, s2);
  }
};
```