# 코드 (1-based)

## 구간 업데이트 점 쿼리
```cpp
template <typename T, typename Merge>
class fenwick_tree {
  const int sz;
  const T raw;
  vector<T> tree;
  Merge op;

public:
  fenwick_tree(int sz, const T& raw = T()) : sz(sz), raw(raw), tree(sz + 1, raw) {}

  void update(int l, int r, const T& v) {
    for (;l <= sz;l += l & -l) tree[l] = op(tree[l], v, false);
    for (r++;r <= sz;r += r & -r) tree[r] = op(tree[r], v, true);
  }

  T query(int i) {
    T s = raw;
    for (;i;i -= i & -i) s = op(s, tree[i], false);
    return s;
  }
};
```

## 점 업데이트 구간 쿼리
```cpp
template <typename T, typename Merge>
class fenwick_tree {
  const int sz;
  const T raw;
  vector<T> tree;
  Merge op;

public:
  fenwick_tree(int sz, const T& raw = T()) : sz(sz), raw(raw), tree(sz + 1, raw) {}

  void update(int i, const T& v) {
    for (;i <= sz;i += i & -i) tree[i] = op(tree[i], v, false);
  }

  T query(int i) {
    T s = raw;
    for (;i;i -= i & -i) s = op(s, tree[i], false);
    return s;
  }
  T query(int l, int r) {
    T s = raw;
    for (;r;r -= r & -r) s = op(s, tree[r], false);
    for (l--;l;l -= l & -l) s = op(s, tree[l], true);
    return s;
  }
};
```
[l, r] 쿼리 함수 없는거
```cpp
template <typename T, typename Merge>
class fenwick_tree {
  const int sz;
  const T raw;
  vector<T> tree;
  Merge op;

public:
  fenwick_tree(int sz, const T& raw = T()) : sz(sz), raw(raw), tree(sz + 1, raw) {}

  void update(int i, const T& v) {
    for (;i <= sz;i += i & -i) tree[i] = op(tree[i], v);
  }

  T query(int i) {
    if (i < 1) return raw;
    if (i > sz) i = sz;
    T s = raw;
    for (;i;i -= i & -i) s = op(s, tree[i]);
    return s;
  }
};
```

## 추가
범위 벗어나도 안전하게!
```cpp
T query(int i) {
  if (i < 1) return raw;
  if (i > sz) i = sz;
  T s = raw;
  for (;i;i -= i & -i) s = op(s, tree[i]);
  return s;
}
```

# 문제

## 구간 업데이트 점 쿼리
* [수열과 쿼리 21](https://boj.kr/16975)
  * http://boj.kr/386958a926f54c71a27f0fac388535d9
* [LRH 식물](https://boj.kr/2934)
  * http://boj.kr/70c7d3bab61049f09f1d166c68fa7128
* [하늘에서 떨어지는 1, 2, ..., R-L+1개의 별](https://boj.kr/17353)
  * http://boj.kr/caf2c870bcd047ae9a80819ad8ff9791

## 점 업데이트 구간 쿼리
* [구간 합 구하기](https://boj.kr/2042)
  * http://boj.kr/1fbe27944c56499489838b3bc2aca0cd
* [공장](https://boj.kr/7578)
  * http://boj.kr/8f2e2777bea24c21922252adac0c84fd
* [북서풍](https://boj.kr/5419)
  * http://boj.kr/429cf0d020214635a036669ca712bb1d
* [커피숍2](https://boj.kr/1275)
  * http://boj.kr/27689e0f91e947f79578ab1c8419e6f1
