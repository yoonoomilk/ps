pair<pt, pt> rotating_calipers(polygon& poly) {
  int sz = poly.size();
  pair<ll, pair<pt, pt>> tmp = {dist2(poly[0] - poly[1]), {poly[0], poly[1]}};
  for(int i = 0, j = 0;i < sz;i++) {
    while(j < sz * 2 && ccw(poly[i], poly[(i + 1) % sz], poly[(i + 1) % sz] + poly[(j + 1) % sz] - poly[j % sz]) > 0) {
      tmp = max(tmp, {dist2(poly[i] - poly[j % sz]), {poly[i], poly[j % sz]}});
      j = (j + 1) % sz;
    }
    tmp = max(tmp, {dist2(poly[i] - poly[j % sz]), {poly[i], poly[j % sz]}});
  }
  return tmp.second;
};

ll rotating_calipers(polygon& poly) {
  int sz = poly.size();
  ll tmp = dist2(poly[0] - poly[1]);
  for(int i = 0, j = 0;i < sz;i++) {
    while(j < sz * 2 && ccw(poly[i], poly[(i + 1) % sz], poly[(i + 1) % sz] + poly[(j + 1) % sz] - poly[j % sz]) > 0) {
      tmp = max(tmp, dist2(poly[i] - poly[j % sz]));
      j = (j + 1) % sz;
    }
    tmp = max(tmp, dist2(poly[i] - poly[j % sz]));
  }
  return tmp;
};