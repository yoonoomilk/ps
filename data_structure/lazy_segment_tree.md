# 코드
```cpp
template <typename T, typename L, typename Merge, typename Update, typename Composition>
class lazy_segment_tree {
  const int lg, sz;
  const T raw;
  const L lazy_raw;
  vector<pair<T, int>> tree;
  vector<L> lazy;
  Merge op;
  Update upd;
  Composition comp;

  void apply(int i, const L &v) {
    tree[i] = upd(v, tree[i]);
    if (i < sz) lazy[i] = comp(v, lazy[i]);
  }

  void push(int i) {
    apply(i * 2, lazy[i]);
    apply(i * 2 + 1, lazy[i]);
    lazy[i] = lazy_raw;
  }

  void pull(int i) {
    tree[i] = op(tree[i * 2], tree[i * 2 + 1]);
  }

public:
  lazy_segment_tree(int n, const T &raw = T(), const L &lazy_raw = L())
  : lg(__lg(n * 2 - 1)), sz(1 << lg), raw(raw), lazy_raw(lazy_raw), tree(sz * 2, {raw, 1}), lazy(sz * 2, lazy_raw) {}

  void set(int i, const T &v) {
    tree[i + sz] = {v, 1};
  }

  void init() {
    for (int i = sz;--i;) pull(i);
  }

  void update(int i, const L &v) {
    i += sz;
    for (int j = lg;j;j--) push(i >> j);
    apply(i, v);
    for (int j = 1;j <= lg;j++) pull(i >> j);
  }
  void update(int l, int r, const L &v) {
    l += sz; r += sz;
    for (int i = lg;i;i--) {
      if (l >> i << i != l) push(l >> i);
      if (r + 1 >> i << i != r + 1) push(r >> i);
    }
    for (int s = l, e = r;s <= e;s /= 2, e /= 2) {
      if (s & 1) apply(s++, v);
      if (~e & 1) apply(e--, v);
    }
    for (int i = 1;i <= lg;i++) {
      if (l >> i << i != l) pull(l >> i);
      if (r + 1 >> i << i != r + 1) pull(r >> i);
    }
  }

  T query(int i) {
    i += sz;
    for (int j = lg;j;j--) push(i >> j);
    return tree[i].first;
  }
  T query(int l, int r) {
    l += sz; r += sz;
    pair<T, int> s1 = {raw, 0}, s2 = {raw, 0};
    for (int i = lg;i;i--) {
      if (l >> i << i != l) push(l >> i);
      if (r + 1 >> i << i != r + 1) push(r >> i);
    }
    for (;l <= r;l /= 2, r /= 2) {
      if (l & 1) s1 = op(s1, tree[l++]);
      if (~r & 1) s2 = op(tree[r--], s2);
    }
    return op(s1, s2).first;
  }
};
```

# 의미미
`lazy_segment_tree<T, L, Merge, Update, Composition> seg(n, raw, lazy_raw)`

* T : tree에 들어갈 값
* L : lazy에 들어갈 값
* Merge : `pair<T, int> operator() (const pair<T, int>& a, const pair<T, int>& b)` 형식
  * `pair<T, int>.second`는 개수
* Update : `pair<T, int> operator() (const L& a, const pair<T, int>& b)` 형식
  * b에 lazy한 a를 적용
* Composition : `L operator() (const L& a, const L& b)` 형식
  * lazy끼리 합치기기

# 문제
* [구간 합 구하기 2](https://boj.kr/10999)
  * http://boj.kr/e42766420f364af689b5137d756f3241
* [수열과 쿼리 21](https://boj.kr/16975)
  * http://boj.kr/423b3aeec32d4adb9a22d9d5a9afc9ce
* [스위치](https://boj.kr/1395)
  * http://boj.kr/68d225afeb8a430db1131870685452d4
* [XOR](https://boj.kr/12844)
  * http://boj.kr/250ab06024954f229a38d38733ee8269

## [Segment Tree with Lazy Propagation의 비재귀 구현](https://www.acmicpc.net/blog/view/117)