# 코드
```cpp
template <typename T, typename Merge>
class segment_tree {
  const int sz;
  const T raw;
  vector<T> tree;
  Merge op;

public:
  segment_tree(int n, const T &raw = T()) : sz(1 << __lg(n * 2 - 1)), raw(raw), tree(sz * 2, raw) {}

  void update(int i, const T &v) {
    i += sz;
    tree[i] = v;
    while (i /= 2) tree[i] = op(tree[i * 2], tree[i * 2 + 1]);
  }

  T query(int i) {
    return tree[i + sz];
  }
  T query(int l, int r) {
    l += sz; r += sz;
    T s1 = raw, s2 = raw;
    for (;l <= r;l /= 2, r /= 2) {
      if (l & 1) s1 = op(s1, tree[l++]);
      if (~r & 1) s2 = op(tree[r--], s2);
    }
    return op(s1, s2);
  }
};
```

## 추가
```cpp
void assign(const vector<T> &raw) {
  for (int i = 0;i < raw.size();i++) tree[i + sz] = raw[i];
  for (int i = sz;--i;) tree[i] = op(tree[i * 2], op[i * 2 + 1]);
}

T top() {
  return tree[1];
}
```

# 문제
* [구간 합 구하기](https://boj.kr/2042)
  * http://boj.kr/6b446911272241bab8c327bf135b9400
* [구간 곱 구하기](https://boj.kr/11505)
  * http://boj.kr/4e68e526b26c4f8bb18d631ef7171b40
* [최솟값과 최댓값](https://boj.kr/2357)
  * http://boj.kr/c37b406050744fc3977f495931590979
* [연속합과 쿼리](https://boj.kr/16993)
  * http://boj.kr/00ae7566aa0f4f30a1c695fb2a02e287
* [디지털 비디오 디스크(DVDs)](https://boj.kr/9345)
  * http://boj.kr/ae8b800440314fd3a9f3715f49223f6d
* [굉장한 학생](https://boj.kr/2336)
  * http://boj.kr/916609cff19548ae8a1dea63ebe5a1d9