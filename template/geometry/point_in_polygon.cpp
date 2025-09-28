bool point_in_polygon(polygon& poly, point cur) {
  int cnt = 0;
  for(int i = 0;i < poly.size();i++) {
    point p1 = poly[i], p2 = poly[(i + 1) % poly.size()];
    if(p1.y > p2.y) swap(p1, p2);
    if(ccw(p1, cur, p2) == 0 && p1.y <= cur.y && cur.y <= p2.y && min(p1.x, p2.x) <= cur.x && cur.x <= max(p1.x, p2.x)) return true;
    if(p1.y <= cur.y && cur.y < p2.y && ccw(p1, p2, cur) > 0) cnt++;
  }
  return cnt % 2;
}

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