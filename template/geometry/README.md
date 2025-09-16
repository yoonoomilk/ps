## struct
```cpp
struct point {
  int x, y;
  point operator+ (const point v) const { return {x + v.x, y + v.y}; }
  point operator- (const point v) const { return {x - v.x, y - v.y}; }
  bool operator== (const point v) const { return x == v.x && y == v.y; }
  bool operator< (const point v) const { return x != v.x ? x < v.x : y < v.y; }
  bool operator<= (const point v) const { return x != v.x ? x <= v.x : y <= v.y; }
  ll size() const { return (ll)x * x + (ll)y * y; }
};
istream& operator>> (istream& cin, point& v) { return cin >> v.x >> v.y; }
using polygon = vector<point>;
```

### distance
[from point to line defined by two points](https://ko.wikipedia.org/wiki/점과_직선_사이의_거리#두_점을_지나는_직선에_대해)

### CCW
```cpp
int ccw(point a, point b, point c) {
  ll s = (ll)(b.x - a.x) * (c.y - a.y) - (ll)(b.y - a.y) * (c.x - a.x);
  return (s > 0) - (s < 0);
}

ll true_ccw(point a, point b, point c) {
  ll s = (ll)(b.x - a.x) * (c.y - a.y) - (ll)(b.y - a.y) * (c.x - a.x);
  return s;
}
```

### cross
```cpp
bool cross(point p1, point p2, point p3, point p4) {
  int p1p2 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
  int p3p4 = ccw(p3, p4, p1) * ccw(p3, p4, p2);
  return (p1p2 <= 0 && p3p4 <= 0);
}
```