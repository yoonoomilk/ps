#include "geometry/geometry.cpp"

int cross(point p1, point p2, point p3, point p4) {
  int l1 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
  int l2 = ccw(p3, p4, p1) * ccw(p3, p4, p2);
  if(l1 == 0 && l2 == 0) {
    point d1 = p2 - p1, d2 = p4 - p3;
    if((ll)d1.x * d2.y != (ll)d1.y * d2.x) return 1;
    if(p2 < p1) swap(p1, p2);
    if(p4 < p3) swap(p3, p4);
    if(p3 < p1) {
      swap(p1, p3);
      swap(p2, p4);
    }
    return (p2 < p3 || p2 == p3) - (p2 != p3);
  }
  return l1 <= 0 && l2 <= 0;
}