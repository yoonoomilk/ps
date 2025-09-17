polygon convex_hull(polygon& poly) {
  polygon tmp;
  swap(poly[0], *min_element(poly.begin(), poly.end()));
  sort(++poly.begin(), poly.end(), [&](point a, point b) {
    int w = ccw(poly[0], a, b);
    if(w) return w > 0;
    return (poly[0] - a).size() < (poly[0] - b).size();
  });
  tmp.push_back(poly[0]);
  tmp.push_back(poly[1]);
  for(int i = 2;i < poly.size();i++) {
    while(tmp.size() >= 2) {
      point cur = tmp.back();
      tmp.pop_back();
      if(ccw(tmp.back(), cur, poly[i]) > 0) {
        tmp.push_back(cur);
        break;
      }
    }
    tmp.push_back(poly[i]);
  }
  return tmp;
}