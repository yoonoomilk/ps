// O((N+Q)√N)
int sz = sqrt(n);

struct query {
  int l, r, idx;
  bool operator < (const query& v) const {
    if(l / sz != v.l / sz) return l / sz < v.l / sz;
    return r < v.r;
  }
};

int l = q[0].l, r = l-1;
for(int i = 0;i < m;i++) {
  while(q[i].l < l) add(raw[--l]);
  while(q[i].l > l) del(raw[l++]);
  while(q[i].r < r) del(raw[r--]);
  while(q[i].r > r) add(raw[++r]);
  ans[q[i].idx] = tmp;
}

// O(N√Q) [An alternative sorting order for Mo's algorithm](https://codeforces.com/blog/entry/61203)
inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
  if(pow == 0) return 0;
  int hpow = 1 << (pow - 1);
  int seg = (x < hpow) ? (
    (y < hpow) ? 0 : 3
  ) : (
    (y < hpow) ? 1 : 2
  );
  seg = (seg + rotate) & 3;
  const int rotateDelta[4] = {3, 0, 0, 1};
  int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
  int nrot = (rotate + rotateDelta[seg]) & 3;
  int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
  int64_t ans = seg * subSquareSize;
  int64_t add = hilbertOrder(nx, ny, pow - 1, nrot);
  ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
  return ans;
}

struct query {
  int l, r, idx;
  int64_t ord;
  void calcOrder() {
    ord = hilbertOrder(l, r, 21, 0);
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