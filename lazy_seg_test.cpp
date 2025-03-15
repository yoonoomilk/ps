#include <bits/stdc++.h>
using namespace std;

template <typename T>
class lazy_segment_tree {
public:
  int sz = 1;
  T raw;
  vector<T> arr, lazy;
  function<T(T, T, int)> ops;

  int count(int a) {
    if(a >= sz) return 1;
    return count(a*2)*2;
  }

  void propagate(int a) {
    for (int h = __lg(sz);h > 0;h--) {
      int i = a >> h;
      if (lazy[i] != raw) {
        arr[i] = ops(arr[i], lazy[i], count(i));
        if (i * 2 < sz) {
          lazy[i * 2] = ops(lazy[i * 2], lazy[i], 1);
          lazy[i * 2 + 1] = ops(lazy[i * 2 + 1], lazy[i], 1);
        } else {
          arr[i * 2] = ops(arr[i * 2], lazy[i], 1);
          arr[i * 2 + 1] = ops(arr[i * 2 + 1], lazy[i], 1);
        }
        lazy[i] = raw;
      }
    }
  }

public:
  lazy_segment_tree(int n, function<T(T, T, int)> ops, T raw = T()) : ops(ops), raw(raw) {
    while (sz < n) sz *= 2;
    arr.resize(2 * sz, raw);
    lazy.resize(sz, raw);
  }

  void update_range(int l, int r, T x) {
    l += sz;
    r += sz;
    while (l <= r) {
      if (l % 2 == 1) {
        if (l < sz) {
          lazy[l] = ops(lazy[l], x, 1);
          for (int i = l / 2;i > 0;i /= 2) arr[i] = ops(arr[i], lazy[l], count(l));
        }
        else {
          arr[l] = ops(arr[l], x, 1);
          for (int i = l / 2;i > 0;i /= 2) arr[i] = ops(arr[i * 2], arr[i * 2 + 1], 1);
        }
        l++;
      }
      if (r % 2 == 0) {
        if (r < sz) {
          lazy[r] = ops(lazy[r], x, 1);
          for (int i = r / 2;i > 0;i /= 2) arr[i] = ops(arr[i], lazy[r], count(r));
        }
        else {
          arr[r] = ops(arr[r], x, 1);
          for (int i = r / 2;i > 0;i /= 2) arr[i] = ops(arr[i * 2], arr[i * 2 + 1], 1);
        }
        r--;
      }
      l /= 2;
      r /= 2;
    }
  }

  T query(int l, int r) {
    l += sz; propagate(l);
    r += sz; propagate(r);
    T s = raw;
    while (l <= r) {
      if (l % 2 == 1) {
        s = ops(s, arr[l], 1);
        if (l < sz) s = ops(s, lazy[l], count(l));
        l++;
      }
      if (r % 2 == 0) {
        s = ops(s, arr[r], 1);
        if (r < sz) s = ops(s, lazy[r], count(r));
        r--;
      }
      l /= 2;
      r /= 2;
    }
    return s;
  }
};

using ll = long long;

void yap(lazy_segment_tree<ll> &seg) {
  // return;
  for(int c = 0;ll j : seg.arr) {
    if(c == 0) {
      c++;
      continue;
    }
    if(1 << __lg(c) == c) cout << '\n';
    for(int k = 1;k < (1<<4-__lg(c));k++) cout << ' ';
    cout << j;
    if(c < seg.sz) cout << '(' << seg.lazy[c] << ')';
    else cout << "  ";
    c++;
  }
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m, k;
  cin >> n >> m >> k;
  lazy_segment_tree<ll> seg(n, [](ll a, ll b, int c) { return a + b * c; });

  for (int i = 0;i < n;i++) {
    ll tmp;
    cin >> tmp;
    seg.update_range(i, i, tmp);
  }
  yap(seg);

  while (m + k--) {
    ll a, b, c, d; cin >> a >> b >> c;
    if (a == 1) {
      cin >> d;
      seg.update_range(b - 1, c - 1, d);
    } else {
      cout << seg.query(b - 1, c - 1) << '\n';
    }
    yap(seg);
  }

  return 0;
}