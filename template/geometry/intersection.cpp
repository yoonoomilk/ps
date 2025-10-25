// only if cross() == 1
pair<double, double> intersection(point p1, point p2, point p3, point p4) {
  ll l1 = (ll)p1.x * p2.y - (ll)p1.y * p2.x, l2 = (ll)p3.x * p4.y - (ll)p3.y * p4.x;
  double px = l1 * (p3.x - p4.x) - l2 * (p1.x - p2.x), py = l1 * (p3.y - p4.y) - l2 * (p1.y - p2.y);
  ll d = (ll)(p1.x - p2.x) * (p3.y - p4.y) - (ll)(p1.y - p2.y) * (p3.x - p4.x);
  if(d == 0) {
    if(p1 == p3 || p1 == p4) return {p1.x, p1.y};
    if(p2 == p3 || p2 == p4) return {p2.x, p2.y};
  }
  return {px / d, py / d};
}