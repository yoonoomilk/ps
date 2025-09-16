ll area2(polygon& poly) {
  ll tmp = 0;
  for(int i = 0;i < poly.size();i++) {
    pt bef = i ? poly[i - 1] : poly.back();
    tmp += (ll)bef.x * poly[i].y - (ll)bef.y * poly[i].x;
  }
  return abs(tmp);
}