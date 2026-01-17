#pragma once

struct point {
  double x, y;
  point operator+ (const point& v) const { return {x + v.x, y + v.y}; }
  point operator- (const point& v) const { return {x - v.x, y - v.y}; }
  double operator* (const point& v) const { return x * v.x + y * v.y; }
  double operator/ (const point& v) const { return x * v.y - y * v.x; }
  point operator* (double v) const { return {x * v, y * v}; }
  point operator/ (double v) const { return {x / v, y / v}; }
  bool operator== (const point& v) const { return abs(x - v.x) < 1e-9 && abs(y - v.y) < 1e-9; }
  bool operator!= (const point& v) const { return !(*this == v); }
  bool operator< (const point& v) const { return x != v.x ? x < v.x : y < v.y; }
  double dist2() const { return x * x + y * y; }
  double dist() const { return sqrt(dist2()); }
  point norm() const { return *this / dist(); }
  friend istream& operator>> (istream& cin, point& v) { return cin >> v.x >> v.y; }
  friend ostream& operator<< (ostream& cout, const point& v) { return cout << v.x << ' ' << v.y; }
};
struct line {
  point s, t;
  bool sgn() const { return s.y == t.y ? s.x < t.x : s.y < t.y; }
  bool operator< (const line& v) const { return sgn() != v.sgn() ? sgn() < v.sgn() : (t - s) / (v.t - v.s) > 0; }
  friend ostream& operator<< (ostream& cout, const line& v) { return cout << v.s << ' ' << v.t; }
};
using polygon = vector<point>;

int ccw(const point& a, const point& b, const point& c) {
  double s = (b - a) / (c - a);
  return (s > 0) - (s < 0);
}