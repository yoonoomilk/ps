int ccw(point a, point b, point c) {
  double s = (b - a) / (c - b);
  return (s > 0) - (s < 0);
}