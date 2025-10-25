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
struct line { point s, t; };
using polygon = vector<point>;