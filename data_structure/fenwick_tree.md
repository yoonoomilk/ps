# 코드 (**NOT DONE**)
```cpp
template <typename T>
class fenwick_tree {
  int sz;
  vector<T> arr;

  T sum(int r) {
    T s = 0;
    while(r > 0) {
      s += arr[r-1];
      r -= r & -r;
    }
    return s;
  }

public:
  fenwick_tree(int n) : sz(n) {
    arr.resize(sz);
  }

  void add(int a, T x) {
    a++;
    while (a <= sz) {
      arr[a - 1] += x;
      a += a & -a;
    }
  }

  T query(int l, int r) {
    return sum(r) - sum(l);
  }
};
```

# 문제
* [구간 합 구하기](https://boj.kr/2042)
  * http://boj.kr/
* [구간 곱 구하기](https://boj.kr/11505)
  * http://boj.kr/
* [최솟값과 최댓값](https://boj.kr/2357)
  * http://boj.kr/
* [연속합과 쿼리](https://boj.kr/16993)
  * http://boj.kr/