## struct
```cpp
struct pt {
  int x, y;
  pt operator+ (pt& v) { return {x + v.x, y + v.y}; }
  pt operator- (pt& v) { return {x - v.x, y - v.y}; }
  bool operator== (pt& v) { return x == v.x && y == v.y; }
  bool operator< (pt& v) { return x != v.x ? x < v.x : y < v.y; }
};

istream& operator >> (istream& cin, pt& v) {
  return cin >> v.x >> v.y;
}

using line = pair<pt, pt>;

using polygon = vector<pt>;
```

### distance
```cpp
double dist(pt a) {
  return hypot(a.x, a.y);
}

ll dist2(pt a) {
  return (ll)a.x * a.x + (ll)a.y * a.y;
}
```

### CCW
```cpp
int ccw(pt a, pt b, pt c) {
  ll s = (ll)(b.x - a.x) * (c.y - a.y) - (ll)(b.y - a.y) * (c.x - a.x);
  return (s > 0) - (s < 0);
}
```

### cross
```cpp
bool cross(line a, line b) {
  pt p1 = a.first, p2 = a.second, p3 = b.first, p4 = b.second;
  int p1p2 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
  int p3p4 = ccw(p3, p4, p1) * ccw(p3, p4, p2);
  return (p1p2 <= 0 && p3p4 <= 0);
}
```