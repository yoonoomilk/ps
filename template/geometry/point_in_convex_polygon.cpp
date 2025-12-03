int point_in_convex_polygon(polygon& poly, point cur) {
  const int n = poly.size();
  int l = 1, r = n - 1;
  if(ccw(poly[0], poly[l], cur) < 0 || ccw(poly[0], poly[r], cur) > 0) return -1;
  while(l + 1 < r) {
    int m = (l + r) / 2;
    if(ccw(poly[0], poly[m], cur) >= 0) l = m;
    else r = m;
  }
  return ccw(cur, poly[l], poly[r]);
}