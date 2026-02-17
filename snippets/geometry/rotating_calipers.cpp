#include "geometry/geometry.cpp"

pair<ll, line> rotating_calipers(const polygon& poly) {
  int n = poly.size();
  pair<ll, line> tmp = {(poly[0] - poly[1]).dist2(), {poly[0], poly[1]}};
  for(int i = 0, j = 0;i < n;i++) {
    while(ccw(poly[i], poly[(i + 1) % n], poly[(i + 1) % n] + poly[(j + 1) % n] - poly[j]) > 0) {
      tmp = max(tmp, {(poly[i] - poly[j]).dist2(), {poly[i], poly[j]}});
      j = (j + 1) % n;
    }
    tmp = max(tmp, {(poly[i] - poly[j]).dist2(), {poly[i], poly[j]}});
  }
  return tmp;
}