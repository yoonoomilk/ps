```cpp
using ll = long long;
using pt = pair<int, int>;
using line = pair<pt, pt>;
#define x first
#define y second
```

```cpp
int ccw(pt &a, pt &b, pt &c) {
  ll s = (ll)(b.x - a.x) * (c.y - b.y) - (ll)(c.x - b.x) * (b.y - a.y);
  return (s > 0) - (s < 0);
}

bool cross(line &a, line &b) {
  pt p1 = a.x, p2 = a.y, p3 = b.x, p4 = b.y;

  int p1p2 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
  int p3p4 = ccw(p3, p4, p1) * ccw(p3, p4, p2);

  return (p1p2 <= 0 && p3p4 <= 0);
}
```

## 문제
* [CCW](https://boj.kr/11758)
* [선분 교차 1](https://boj.kr/17386), [선분 교차 2](https://boj.kr/17387)
* [선분 그룹](https://boj.kr/2162)
