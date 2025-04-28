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
for(int i = 0;i < m;i++) {
  while(q[i].l < l) add(raw[--l]);
  while(q[i].l > l) del(raw[l++]);
  while(q[i].r < r) del(raw[r--]);
  while(q[i].r > r) add(raw[++r]);
  ans[q[i].idx] = tmp;
}
```

## 설명

* `tmp`는 **[l, r]** 쿼리의 값
* `add(v)`는 `v`를 범위에 포함시켰을 때, `del(v)`는 `v`를 범위에서 제거했을 때


# 문제
* [수열과 쿼리 5](https://boj.kr/13547)
  * http://boj.kr/9be65825bfcf47d0aaa21e0f5e775223
* [수열과 쿼리 6](https://boj.kr/13548)
  * http://boj.kr/ed8e687f70e74bb380a16f41ec74ef08
* [수열과 쿼리 8](https://boj.kr/13553)
  * http://boj.kr/536994dd0e5b43ae9aae112f25d15bb6
* [수열과 쿼리 23](https://boj.kr/16979)
  * http://boj.kr/16c1960f6eb547709d2cfe25e1813fff
* [배열의 힘](https://boj.kr/8462)
  * http://boj.kr/6eafcfeea9584beea2ace18a1a45d42f
* [백설공주와 난쟁이](https://boj.kr/2912)
  * http://boj.kr/99d9a9b5f84d443fbae1476c7c0f52f3
* [화려한 마을 3](https://boj.kr/12999)
  * http://boj.kr/cd0ef53243224f7b945efb1b47387a11
* [스퀘어 게임](https://boj.kr/32277)
  * http://boj.kr/7a988a00b3a44611ae2928da5884d8bf
* [민호의 소원](https://boj.kr/13028)
  * http://boj.kr/b86b24a27a7a4967a90cb6fd4bb90c8d