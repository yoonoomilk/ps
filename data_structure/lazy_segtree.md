# 코드 (**NOT DONE**)
```cpp
template <typename T>
struct lazy_segtree {
  int sz = 1, h = 0;
  vector<T> arr, lazy;
  T raw;
  function<T(T, T)> op;
  function<T(T, T, int)> ops;

  lazy_segtree(int n, function<T(T, T)> op, function<T(T, T, int)> ops, T raw = T())
    : op(op), ops(ops), raw(raw) {
    while(sz < n) {
      sz *= 2;
      h++;
    }
    arr.resize(2 * sz, raw);
    lazy.resize(sz, raw);
  }

  void apply_node(int a, int cnt, T x) {
    arr[a] = ops(arr[a], x, cnt);
    if (a < sz) lazy[a] = op(lazy[a], x);
  }

  void merge_node(int a, int cnt) {
    if (a >= sz) return;
    arr[a] = ops(op(arr[a * 2], arr[a * 2 + 1]), lazy[a], cnt);
  }

  void push(int a) {
    for (int hh = h, cnt = 1 << h;hh > 0;hh--) {
      cnt /= 2;
      int p = a >> hh;
      if (lazy[p] != raw) {
        apply_node(p * 2, cnt, lazy[p]);
        apply_node(p * 2 + 1, cnt, lazy[p]);
        lazy[p] = raw;
      }
    }
  }

  void update(int l, int r, T x) {
    l += sz;
    r += sz;
    push(l);
    push(r);
    for (int s = l, e = r, cnt = 1;s <= e;cnt *= 2) {
      if (s % 2 == 1) apply_node(s++, cnt, x);
      if (e % 2 == 0) apply_node(e--, cnt, x);
      s /= 2;
      e /= 2;
    }
    for (int s = l / 2, e = r / 2, cnt = 2;s > 0;cnt *= 2) {
      merge_node(s, cnt);
      merge_node(e, cnt);
      s /= 2;
      e /= 2;
    }
  }

  T query(int l, int r) {
    l += sz;
    r += sz;
    push(l);
    push(r);
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