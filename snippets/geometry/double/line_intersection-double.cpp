#include "geometry/double/geometry-double.cpp"

bool line_intersection(line& a, line& b, point& v) {
  double d = (a.t - a.s) / (b.t - b.s);
  if(abs(d) < 1e-9) return false;
  v = a.s + (a.t - a.s) * ((b.s - a.s) / (b.t - b.s) / d);
  return true;
}