```cpp
#include <bits/stdc++.h>
using namespace std;
```

```cpp
template <typename T>
class segtree {
  int sz = 1;
  T raw;
  vector<T> arr;
  function<T(T, T)> choose;

public:
  segtree(int n, function<T(T, T)> choose, T raw) : choose(choose), raw(raw) {
    while (sz < n) sz *= 2;
    arr.resize(2 * sz, raw);
  }

  void update(int a, T x) {
    a += sz;
    arr[a] = x;
    while (a /= 2) arr[a] = choose(arr[a * 2], arr[a * 2 + 1]);
  }

  T query(int l, int r) {
    l += sz;
    r += sz;
    T s = raw;
    while (l <= r) {
      if (l % 2 == 1) s = choose(s, arr[l++]);
      if (r % 2 == 0) s = choose(s, arr[r--]);
      l /= 2;
      r /= 2;
    }
    return s;
  }
};

```

문제: [구간 합 구하기](https://boj.kr/2042)

[전체 코드](http://boj.kr/1a8be0056d4e48e591bdf82dccb955ae)