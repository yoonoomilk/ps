double area(polygon& poly) {
  double tmp = 0;
  for(int i = 0;i < poly.size();i++) tmp += poly[i] / poly[(i + 1) % poly.size()];
  return abs(tmp) / 2;
}