# 코드
```cpp
class disjoint_set {
  int sz;
  vector<int> arr;

public:
  disjoint_set(int sz) : sz(sz) {
    arr.resize(sz);
    iota(arr.begin(), arr.end(), 0);
  }

  int find(int x) {
    if (arr[x] == x) return x;
    return arr[x] = find(arr[x]);
  }

  bool same(int a, int b) {
    a = find(a);
    b = find(b);
    return a == b;
  }

  void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (!same(a, b)) arr[b] = a;
  }
};
```

# 문제
* [집합의 표현](https://boj.kr/1717)
  * http://boj.kr/76456c17a1a14aafbcd30438c62144c9