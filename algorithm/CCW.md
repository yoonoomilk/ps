```cpp
using ll = long long;
using pt = pair<int, int>;
using line = pair<pt, pt>;
#define x first
#define y second
```

# 코드
```cpp
int CCW(pt &a, pt &b, pt &c) {
  ll s = (ll)(b.x - a.x) * (c.y - b.y) - (ll)(c.x - b.x) * (b.y - a.y);
  return (s > 0) - (s < 0);
}

bool cross(line &a, line &b) {
  pt p1 = a.x, p2 = a.y, p3 = b.x, p4 = b.y;

  int p1p2 = CCW(p1, p2, p3) * CCW(p1, p2, p4);
  int p3p4 = CCW(p3, p4, p1) * CCW(p3, p4, p2);

  return (p1p2 <= 0 && p3p4 <= 0);
}
```

# 문제
* [CCW](https://boj.kr/11758)
  * http://boj.kr/f515cc5699cd4d838245f2f997b903d0
* [선분 교차 1](https://boj.kr/17386), [선분 교차 2](https://boj.kr/17387)
  * http://boj.kr/91a3f8e8aa604c5ea3dbb0565e76f045
  * http://boj.kr/2fbf41c2245f4bf58615256eb2e7cfb4
* [선분 그룹](https://boj.kr/2162)
  * http://boj.kr/978059d6cdd04c85bc2fe65455333938