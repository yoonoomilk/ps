pair<pt, pt> rotating_calipers(polygon& poly) {
  int sz = poly.size();
  pair<ll, pair<pt, pt>> tmp = {-1, {poly[0], poly[1]}};
  for(int i = 0, j = 1;i < sz;i++) {
    while(dist2(poly[i] - poly[(j + 1) % sz]) > dist2(poly[i] - poly[j])) j = (j + 1) % sz; 
    tmp = max(tmp, {dist2(poly[i] - poly[j]), {poly[i], poly[j]}});
  }
  return tmp.second;
};