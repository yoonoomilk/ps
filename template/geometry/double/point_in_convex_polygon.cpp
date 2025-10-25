bool point_in_convex_polygon(polygon& poly, point cur) {
  if(ccw(poly[0], poly[1], cur) < 0) return false;
  int l = 1, r = poly.size() - 1;
  while(l < r) {
    int m = (l + r + 1) / 2;
    if(ccw(poly[0], poly[m], cur) >= 0) l = m;
    else r = m - 1;
  }
  if(l == poly.size() - 1) return ccw(poly[0], poly.back(), cur) == 0 && poly[0] <= cur && cur <= poly.back();
  return ccw(poly[0], poly[1], cur) >= 0 && ccw(poly[l], poly[l + 1], cur) >= 0 && ccw(poly[l + 1], poly[0], cur) >= 0;
}