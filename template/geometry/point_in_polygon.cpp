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
  //TODO
}