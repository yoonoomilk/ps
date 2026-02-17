#include "geometry/geometry.cpp"
#include "geometry/point_in_convex_polygon.cpp"

pii tangent_of_convex_polygon(const polygon& poly, point cur) {
  if(point_in_convex_polygon(poly, cur) >= 0) return {-1, -1};
  int n = poly.size();
  int s1 = -1, s2 = -1;
  bool flag = ccw(cur, poly[0], poly[n - 1]) >= 0;
  {
    auto f = [&](int m) {
      int a = (m + 1) % n, b = (m - 1 + n) % n;
      return !flag ?
        (ccw(cur, poly[m], poly[b]) < 0 && ccw(cur, poly[m], poly[a]) > 0 && ccw(cur, poly[0], poly[m]) <= 0) :
        (ccw(cur, poly[m], poly[b]) < 0 || (ccw(cur, poly[m], poly[b]) >= 0 && ccw(cur, poly[m], poly[a]) <= 0 && ccw(cur, poly[0], poly[m]) >= 0));
    };
    int l = 0, r = n - 1;
    while(l < r) {
      int m = (l + r + 1) / 2;
      if(f(m)) r = m - 1;
      else l = m;
    }
    s1 = l;
  }
  {
    auto f = [&](int m) {
      int a = (m + 1) % n, b = (m - 1 + n) % n;
      return flag ?
        (ccw(cur, poly[m], poly[b]) >= 0 && ccw(cur, poly[m], poly[a]) <= 0 && ccw(cur, poly[0], poly[m]) >= 0) :
        (ccw(cur, poly[m], poly[b]) >= 0 || (ccw(cur, poly[m], poly[b]) < 0 && ccw(cur, poly[m], poly[a]) > 0 && ccw(cur, poly[0], poly[m]) <= 0));
    };
    int l = 0, r = n - 1;
    while(l < r) {
      int m = (l + r + 1) / 2;
      if(f(m)) r = m - 1;
      else l = m;
    }
    s2 = l;
  }
  return {s2, s1};
}