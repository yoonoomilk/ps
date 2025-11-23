struct point {
  int x, y;
  point operator+ (const point v) const { return {x + v.x, y + v.y}; }
  point operator- (const point v) const { return {x - v.x, y - v.y}; }
  ll operator* (const point v) const { return (ll)x * v.x + (ll)y * v.y; }
  ll operator/ (const point v) const { return (ll)x * v.y - (ll)y * v.x; }
  bool operator== (const point v) const { return x == v.x && y == v.y; }
  bool operator!= (const point v) const { return !(*this == v); }
  bool operator< (const point v) const { return x != v.x ? x < v.x : y < v.y; }
  ll dist2() const { return (ll)x * x + (ll)y * y; }
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