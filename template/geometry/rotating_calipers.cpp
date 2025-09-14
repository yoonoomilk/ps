ll rotating_calipers(polygon& poly) {
  int sz = poly.size();
  ll tmp = -1;
  for(int i = 0, j = 0;i < sz;i++) {
    while(ccw(poly[i], poly[(i + 1) % sz], poly[(i + 1) % sz] + poly[(j + 1) % sz] - poly[j]) <= 0 && i != j) {
      j = (j + 1) % sz;
      tmp = max(tmp, dist2(poly[i] - poly[j]));
    }
    tmp = max(tmp, dist2(poly[i] - poly[j]));
  }
  return tmp;
};