
### top
```cpp
T top() {
  return tree[1];
}
```

## segment tree

### kth
```cpp
int kth(int k) {
  int idx = 1;
  while(idx < sz) {
    if(tree[idx * 2] < k) {
      k -= tree[idx * 2];
      idx = idx * 2 + 1;
    } else idx = idx * 2;
  }
  return idx - sz;
}
```

### 금광 세그
```cpp
struct hoit {
  int p, l, r, a;
};

struct op {
  hoit operator() (hoit& a, hoit& b) {
    hoit tmp;
    tmp.p = max({a.r + b.l, a.p, b.p});
    tmp.l = max(a.l, a.a + b.l);
    tmp.r = max(a.r + b.a, b.r);
    tmp.a = a.a + b.a;
    return tmp;
  }
};
```

## lazy segment tree
`lazy_segment_tree<T, L, Merge, Update, Composition> seg(n, raw, lazy_raw)`

* T : tree에 들어갈 타입
* L : lazy에 들어갈 타입
* Merge : `T operator() (T a, T b)`
  * non-lazy한 값끼리 합치기
* Update : `void operator() (T& a, L b)`
  * non-lazy한 a에 lazy한 b를 적용
* Composition : `L operator() (L a, L b)`
  * lazy한 a에 lazy한 b 합치기
```cpp
struct op {
  pii operator() (pii a, pii b) {
    return {a.first + b.first, a.second + b.second};
  }
};

struct upd {
  void operator() (pii& a, ll b) {
    a.first += b * a.second;
  }
};

struct comp {
  ll operator() (ll a, ll b) {
    return a + b;
  }
};
```

## segment tree beats

### [수열과 쿼리 26](https://www.acmicpc.net/problem/17474)
```cpp

struct hoit {
  ll max1, max2, sum;
  int cnt;
};

struct op {
  hoit operator() (hoit& a, hoit& b) {
    hoit tmp;
    tmp.sum = a.sum + b.sum;
    tmp.max1 = max(a.max1, b.max1);
    if(a.max1 < b.max1) {
      tmp.cnt = b.cnt;
      tmp.max2 = max(b.max2, a.max1);
    } else if(a.max1 > b.max1) {
      tmp.cnt = a.cnt;
      tmp.max2 = max(a.max2, b.max1);
    } else {
      tmp.cnt = a.cnt + b.cnt;
      tmp.max2 = max(a.max2, b.max2);
    }
    return tmp;
  }
};

struct try_upd {
  bool operator() (hoit& a, ll& b) {
    if(b >= a.max1) {}
    else if(b > a.max2) {
      a.sum -= (a.max1 - b) * a.cnt;
      a.max1 = b;
    } else return true;
    return false;
  }
};

struct comp {
  ll operator() (ll a, ll b) {
    return min(a, b);
  }
};
```

## dynamic segment tree

### kth
```cpp
ll kth(int cur, ll s, ll e, T v) {
  if(s == e) return s;
  ll m = (s + e) / 2;
  if(tree[tree[cur].l].v >= v) return kth(tree[cur].l, s, m, v);
  else return kth(tree[cur].r, m + 1, e, v - tree[tree[cur].l].v);
}

ll kth(T k) {
  return kth(0, 0, sz - 1, k);
}
```