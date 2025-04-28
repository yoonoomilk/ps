# 코드
```cpp
int sz = sqrt(n);

struct query {
  int l, r, idx;
  bool operator < (const query& v) const {
    if(l / sz != v.l / sz) return l / sz < v.l / sz;
    return r < v.r;
  }
};

int l = 0, r = 0;
for (int i = 0;i < m;i++) {
  while (q[i].l < l) add(raw[--l]);
  while (q[i].l > l) del(raw[l++]);
  while (q[i].r < r) del(raw[r--]);
  while (q[i].r > r) add(raw[++r]);
  ans[q[i].idx] = tmp;
}
```

## [설명](https://justicehui.github.io/hard-algorithm/2019/06/17/MoAlgorithm/)

* `tmp`는 누적(?)합
* `add(v)`는 `tmp`에 `v`더하고, `del(v)`는 `tmp`에 `v`를 빼고


# 문제
* [수열과 쿼리 5](https://boj.kr/13547)
  * http://boj.kr/9be65825bfcf47d0aaa21e0f5e775223
* [수열과 쿼리 6](https://boj.kr/13548)
  * http://boj.kr/2d4d89d9f2d64a5ab2ced88baa1bceba