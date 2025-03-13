# 코드
```cpp
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <typename T>
class dynamic_segment_tree {
  int sz = 1;
  T raw;
  cc_hash_table<int, T> arr;
  function<T(T, T)> op;

  T get(int a) {
    if(arr.find(a) != arr.end()) return arr[a];
    return raw;
  }

public:
  dynamic_segment_tree(int n, function<T(T, T)> op, T raw = T()) : op(op), raw(raw) {
    while (sz < n) sz *= 2;
  }

  void update(int a, T x) {
    a += sz;
    arr[a] = x;
    while (a /= 2) arr[a] = op(get(a * 2), get(a * 2 + 1));
  }

  T query(int l, int r) {
    l += sz;
    r += sz;
    T s1 = raw, s2 = raw;
    while (l <= r) {
      if (l % 2 == 1) s1 = op(s1, get(l++));
      if (r % 2 == 0) s2 = op(get(r--), s2);
      l /= 2;
      r /= 2;
    }
    return op(s1, s2);
  }

  T value(int a) {
    return get(arr[a + sz]);
  }

  T top() {
    return get(arr[1]);
  }
};
```

# 문제
* [구간 합 구하기](https://boj.kr/2042)
  * http://boj.kr/a23257a0c2e94596a6944e183c05ccc6
* [구간 곱 구하기](https://boj.kr/11505)
  * http://boj.kr/0d1c823b40a644e0a6aea80c7bb0e73a
* [최솟값과 최댓값](https://boj.kr/2357)
  * http://boj.kr/26fdfb777ec7497bbb97c671f2638ac8
* [연속합과 쿼리](https://boj.kr/16993)
  * http://boj.kr/79c47a7c6dd14964b55f41a1b49475fd