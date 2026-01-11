#include "geometry/geometry.cpp"

int point_in_convex_polygon(const polygon& poly, point cur) {
  int l = 1, r = poly.size() - 1;
  if(ccw(poly[0], poly[l], cur) < 0 || ccw(poly[0], poly[r], cur) > 0) return -1;
  if(ccw(poly[0], poly[l], cur) == 0) return ccw(poly[l], poly[l + 1], cur) >= 0 ? 0 : -1;
  if(ccw(poly[0], poly[r], cur) == 0) return ccw(poly[r - 1], poly[r], cur) >= 0 ? 0 : -1;
  while(l + 1 < r) {
    int m = (l + r) / 2;
    if(ccw(poly[0], poly[m], cur) >= 0) l = m;
    else r = m;
  }
  return ccw(poly[l], poly[r], cur);
}