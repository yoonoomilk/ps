```cpp
using pt = pair<int, int>;
using line = pair<pt, pt>;
#define x first
#define y second

int ccw(pt &a, pt &b, pt &c) {
  ll s = (b.x - a.x) * (c.y - b.y) - (c.x - b.x) * (b.y - a.y);
  if(s > 0) return 1;
  if(s < 0) return -1;
  return 0;
}

bool cross(line &a, line &b) {
  pt p1 = a.x, p2 = a.y, p3 = b.x, p4 = b.y;

  int p1p2 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
  int p3p4 = ccw(p3, p4, p1) * ccw(p3, p4, p2);

  return (p1p2 <= 0 && p3p4 <= 0);
}
```