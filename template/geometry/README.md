## struct
```cpp
struct point {
  int x, y;
  point operator+ (const point v) const { return {x + v.x, y + v.y}; }
  point operator- (const point v) const { return {x - v.x, y - v.y}; }
  bool operator== (const point v) const { return x == v.x && y == v.y; }
  bool operator!= (const point v) const { return x != v.x || y != v.y; }
  bool operator< (const point v) const { return x != v.x ? x < v.x : y < v.y; }
  ll size() const { return (ll)x * x + (ll)y * y; }
  friend istream& operator>> (istream& cin, point& v) { return cin >> v.x >> v.y; }
  friend ostream& operator<< (ostream& cout, point& v) { return cout << v.x << ' '<< v.y; }
};
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
int cross(point p1, point p2, point p3, point p4) {
  int l1 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
  int l2 = ccw(p3, p4, p1) * ccw(p3, p4, p2);
  if(l1 == 0 && l2 == 0) {
    point d1 = p2 - p1, d2 = p4 - p3;
    if((ll)d1.x * d2.y != (ll)d1.y * d2.x) return 1;
    if(p2 < p1) swap(p1, p2);
    if(p4 < p3) swap(p3, p4);
    if(p3 < p1) {
      swap(p1, p3);
      swap(p2, p4);
    }
    return (p2 < p3 || p2 == p3) - (p2 != p3);
  }
  return l1 <= 0 && l2 <= 0;
}
```

### intersection (only if cross() == 1)
```cpp
pair<double, double> intersection(point p1, point p2, point p3, point p4) {
  ll l1 = (ll)p1.x * p2.y - (ll)p1.y * p2.x, l2 = (ll)p3.x * p4.y - (ll)p3.y * p4.x;
  double px = l1 * (p3.x - p4.x) - l2 * (p1.x - p2.x), py = l1 * (p3.y - p4.y) - l2 * (p1.y - p2.y);
  ll d = (ll)(p1.x - p2.x) * (p3.y - p4.y) - (ll)(p1.y - p2.y) * (p3.x - p4.x);
  if(d == 0) {
    if(p1 == p3 || p1 == p4) return {p1.x, p1.y};
    if(p2 == p3 || p2 == p4) return {p2.x, p2.y};
  }
  return {px / d, py / d};
}
```
