double area(polygon& poly) {
  double tmp = 0;
  for(int i = 0;i < poly.size();i++) {
    point bef = i ? poly[i - 1] : poly.back();
    tmp += bef.x * poly[i].y - bef.y * poly[i].x;
  }
  return abs(tmp) / 2;
}