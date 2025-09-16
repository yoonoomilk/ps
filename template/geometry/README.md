## struct
```cpp
struct point {
  int x, y;
  point operator+ (const point v) const { return {x + v.x, y + v.y}; }
  point operator- (const point v) const { return {x - v.x, y - v.y}; }
  bool operator== (const point v) const { return x == v.x && y == v.y; }
  bool operator< (const point v) const { return x != v.x ? x < v.x : y < v.y; }
  ll size() const { return (ll)x * x + (ll)y * y; }
};
istream& operator>> (istream& cin, point& v) { return cin >> v.x >> v.y; }
using polygon = vector<point>;
using line = pair<point, point>;
```

### CCW
```cpp
int ccw(point a, point b, point c) {
  ll s = (ll)(b.x - a.x) * (c.y - a.y) - (ll)(b.y - a.y) * (c.x - a.x);
  return (s > 0) - (s < 0);
}
```

### cross
```cpp
bool cross(line a, line b) {
  point p1 = a.first, p2 = a.second, p3 = b.first, p4 = b.second;
  int p1p2 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
  int p3p4 = ccw(p3, p4, p1) * ccw(p3, p4, p2);
  return (p1p2 <= 0 && p3p4 <= 0);
}
```