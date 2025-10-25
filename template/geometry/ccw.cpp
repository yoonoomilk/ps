int ccw(point a, point b, point c) {
  ll s = (ll)(b.x - a.x) * (c.y - a.y) - (ll)(b.y - a.y) * (c.x - a.x);
  return (s > 0) - (s < 0);
}