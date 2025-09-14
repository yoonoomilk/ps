## point
```cpp
struct pt {
  int x, y;
  pt operator- (pt& v) {
    return {x - v.x, y - v.y};
  }
  bool operator== (pt& v) {
    return x == v.x && y == v.y;
  }
  bool operator< (pt& v) {
    return x != v.x ? x < v.x : y < v.y;
  }
};

istream& operator >> (istream& cin, pt& v) {
  return cin >> v.x >> v.y;
}
```

### distance
```cpp
double dist(pt a, pt b) {
  return hypot(a.x - b.x, a.y - b.y);
}

ll dist2(pt a, pt b) {
  return (ll)(a.x - b.x) * (a.x - b.x) + (ll)(a.y - b.y) * (a.y - b.y);
}
```

### CCW
```cpp
int ccw(pt a, pt b, pt c) {
  ll s = (ll)(b.x - a.x) * (c.y - b.y) - (ll)(c.x - b.x) * (b.y - a.y);
  return (s > 0) - (s < 0);
}
```

## line
```cpp
using line = pair<pt, pt>;
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