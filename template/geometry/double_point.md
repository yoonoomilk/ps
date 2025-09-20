## struct
```cpp
struct point {
  double x, y;
  point operator+ (const point v) const { return {x + v.x, y + v.y}; }
  point operator- (const point v) const { return {x - v.x, y - v.y}; }
  double operator/ (const point v) const { return x * v.y - y * v.x; }
  point operator* (const double v) const { return {x * v, y * v}; }
  point operator/ (const double v) const { return {x / v, y / v}; }
  bool operator< (const point v) const { return x != v.x ? x < v.x : y < v.y; }
  double size() const { return hypot(x, y); }
  friend istream& operator>> (istream& cin, point& v) { return cin >> v.x >> v.y; }
  friend ostream& operator<< (ostream& cout, point& v) { return cout << v.x << ' '<< v.y; }
};
using polygon = vector<point>;
```

### CCW
```cpp
int ccw(point a, point b, point c) {
  double s = (b - a) / (c - b);
  return (s > 0) - (s < 0);
}
```

### cross
```cpp
bool cross(point p1, point p2, point p3, point p4) {
  if(abs((p2 - p1) / (p4 - p3)) < 1e-10) return false;
  int l1 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
  int l2 = ccw(p3, p4, p1) * ccw(p3, p4, p2);
  if(l1 == 0 && l2 == 0){
    if(p2 < p1) swap(p1, p2);
    if(p4 < p3) swap(p3, p4);
    return !(p2 < p3 || p4 < p1);
  }
  return l1 <= 0 && l2 <= 0;
}
```

### intersection (only if cross() == 1)
```cpp
point intersection(point p1, point p2, point p3, point p4) {
  double d = (p2 - p1) / (p4 - p3);
  return p1 + (p2 - p1) * ((p3 - p1) / (p4 - p3) / d);
}
```