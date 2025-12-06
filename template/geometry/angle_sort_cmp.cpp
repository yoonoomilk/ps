struct angle_sort_cmp {
  const point p;
  angle_sort_cmp(point p) : p(p) {}
  bool operator() (const point& a, const point& b) const {
    if(p < a != p < b) return b < a;
    if(int w = ccw(p, a, b)) return w > 0;
    return (p - a).dist2() < (p - b).dist2();
  }
};