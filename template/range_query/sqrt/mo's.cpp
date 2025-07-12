// O((N+Q)√N)
int sz = sqrt(n);

struct query {
  int l, r, idx;
  bool operator < (const query& v) const {
    if(l / sz != v.l / sz) return l / sz < v.l / sz;
    return r < v.r;
  }
};

//faster
struct query {
  int l, r, idx;
  bool operator < (const query& v) const {
    int a = l / sz, b = v.l / sz;
    return (a < b) || ((a == b) && ((a & 1) ^ (r < v.r)));
  }
};

int l = q[0].l, r = l - 1;
for(int i = 0;i < m;i++) {
  while(q[i].l < l) add(raw[--l]);
  while(q[i].l > l) del(raw[l++]);
  while(q[i].r < r) del(raw[r--]);
  while(q[i].r > r) add(raw[++r]);
  ans[q[i].idx] = tmp;
}

// O(N√Q) [An alternative sorting order for Mo's algorithm](https://codeforces.com/blog/entry/61203)
struct query {
  int l, r, idx;
  int64_t ord = 0;
  void operator() () {
    int x = l, y = r;
    int lg = __lg(max(x, y) * 2 + 1) | 1;
    uint64_t maxn = (1ULL << lg) - 1;
    for(uint64_t s = 1ULL << (lg - 1);s;s >>= 1) {
      bool rx = x & s, ry = y & s;
      ord = (ord << 2) | (rx ? ry ? 2 : 1 : ry ? 3 : 0);
      if(rx) continue;
      if(ry) x ^= maxn, y ^= maxn;
      swap(x, y);
    }
  }
  bool operator < (const query& v) const {
    return ord < v.ord;
  }
};

/*
`tmp`는 **[l, r]** 쿼리의 값
`add(v)`는 `v`를 범위에 포함시켰을 때
`del(v)`는 `v`를 범위에서 제거했을 때
*/