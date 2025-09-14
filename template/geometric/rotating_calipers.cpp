ll rotating_calipers(polygon& poly) {
  int idx = 0;
  ll tmp = 0;
  for(int i = 0;i < poly.size();i++) {
    while(idx + 1 < poly.size() && ccw({0, 0}, poly[i + 1] - poly[i], poly[idx + 1] - poly[idx]) >= 0) {
      tmp = max(tmp, dist2(poly[i] - poly[idx]));
      idx++;
    }
    tmp = max(tmp, dist2(poly[i] - poly[idx]));
  }
  return tmp;
};