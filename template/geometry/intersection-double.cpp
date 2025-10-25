point intersection(point p1, point p2, point p3, point p4) {
  double d = (p2 - p1) / (p4 - p3);
  return p1 + (p2 - p1) * ((p3 - p1) / (p4 - p3) / d);
}