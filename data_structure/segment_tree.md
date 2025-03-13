# 코드
```cpp
template <typename T>
class segment_tree {
  int sz = 1;
  T raw;
  vector<T> arr;
  function<T(T, T)> op;

public:
  segment_tree(int n, function<T(T, T)> op, T raw = T()) : op(op), raw(raw) {
    while (sz < n) sz *= 2;
    arr.resize(2 * sz, raw);
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
    return arr[a + sz];
  }

  T top() {
    return arr[1];
  }
};
```

# 추가
```cpp
void assign(vector<T> &raw) {
  for (int i = 0;i < raw.size();i++) arr[i + sz] = raw[i];
  for (int i = sz;--i;) arr[i] = op(arr[i * 2], op[i * 2 + 1]);
}
```

# 문제
* [구간 합 구하기](https://boj.kr/2042)
  * http://boj.kr/1a8be0056d4e48e591bdf82dccb955ae
* [구간 곱 구하기](https://boj.kr/11505)
  * http://boj.kr/4e68e526b26c4f8bb18d631ef7171b40
* [최솟값과 최댓값](https://boj.kr/2357)
  * http://boj.kr/a7b203814a474eb0a00c0878bd51c22e
* [연속합과 쿼리](https://boj.kr/16993)
  * http://boj.kr/da21d05be1a64f73a695049f7a8eec7d
