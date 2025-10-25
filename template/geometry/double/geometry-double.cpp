struct point {
  double x, y;
  point operator+ (const point v) const { return {x + v.x, y + v.y}; }
  point operator- (const point v) const { return {x - v.x, y - v.y}; }
  double operator* (const point v) const { return x * v.x + y * v.y; }
  double operator/ (const point v) const { return x * v.y - y * v.x; }
  point operator* (const double v) const { return {x * v, y * v}; }
  bool operator== (const point v) const { return abs(x - v.x) < 1e-9 && abs(y - v.y) < 1e-9; }
  bool operator!= (const point v) const { return !(*this == v); }
  bool operator< (const point v) const { return x != v.x ? x < v.x : y < v.y; }
  double size() const { return hypot(x, y); }
  friend istream& operator>> (istream& cin, point& v) { return cin >> v.x >> v.y; }
  friend ostream& operator<< (ostream& cout, point& v) { return cout << v.x << ' ' << v.y; }
};
struct line {
  point s, t;
  bool sgn() const { return s.y == t.y ? s.x < t.x : s.y < t.y; }
  bool operator< (const line v) const { return sgn() != v.sgn() ? sgn() < v.sgn() : (t - s) / (v.t - v.s) > 0; }
  friend ostream& operator<< (ostream& cout, line& v) { return cout << v.s << ' ' << v.t; }
};
using polygon = vector<point>;