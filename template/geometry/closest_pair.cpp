pair<ll, line> closest_pair(polygon& poly) {
  sort(poly.begin(), poly.end(), [](point& a, point& b) { return a.y < b.y; });
  pair<ll, line> tmp = {(poly[0] - poly[1]).size(), {poly[0], poly[1]}};
  set<point> arr;
  for(int i = 0, j = 0;i < poly.size();i++) {
    point d = {1 + sqrt(tmp.first), 0};
    while(poly[j].y <= poly[i].y - d.x) arr.erase(poly[j++]);
    auto l = arr.lower_bound(poly[i] - d), r = arr.upper_bound(poly[i] + d);
    for(;l != r;l++) tmp = min(tmp, {(*l - poly[i]).size(), {*l, poly[i]}});
    arr.insert(poly[i]);
  }
  return tmp;
}