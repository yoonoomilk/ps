pair<double, line> rotating_calipers(polygon& poly) {
  int sz = poly.size();
  pair<double, line> tmp = {(poly[0] - poly[1]).size(), {poly[0], poly[1]}};
  for(int i = 0, j = 0;i < sz;i++) {
    while(ccw(poly[i], poly[(i + 1) % sz], poly[(i + 1) % sz] + poly[(j + 1) % sz] - poly[j % sz]) > 0) {
      tmp = max(tmp, {(poly[i] - poly[j % sz]).size(), {poly[i], poly[j % sz]}});
      j = (j + 1) % sz;
    }
    tmp = max(tmp, {(poly[i] - poly[j % sz]).size(), {poly[i], poly[j % sz]}});
  }
  return tmp;
};