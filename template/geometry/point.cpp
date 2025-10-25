struct point {
  int x, y;
  point operator+ (const point v) const { return {x + v.x, y + v.y}; }
  point operator- (const point v) const { return {x - v.x, y - v.y}; }
  double operator/ (const point v) const { return x * v.y - y * v.x; }
  bool operator== (const point v) const { return x == v.x && y == v.y; }
  bool operator!= (const point v) const { return x != v.x || y != v.y; }
  bool operator< (const point v) const { return x != v.x ? x < v.x : y < v.y; }
  bool operator<= (const point v) const { return *this < v || *this == v; }
  ll size() const { return (ll)x * x + (ll)y * y; }
  friend istream& operator>> (istream& cin, point& v) { return cin >> v.x >> v.y; }
  friend ostream& operator<< (ostream& cout, point& v) { return cout << v.x << ' '<< v.y; }
};
struct line { point s, t; };
using polygon = vector<point>;