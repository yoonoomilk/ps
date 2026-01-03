#include "geometry/double/geometry-double.cpp"

bool cross(point p1, point p2, point p3, point p4) {
  if(abs((p2 - p1) / (p4 - p3)) < 1e-9) return false;
  int l1 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
  int l2 = ccw(p3, p4, p1) * ccw(p3, p4, p2);
  if(l1 == 0 && l2 == 0){
    if(p2 < p1) swap(p1, p2);
    if(p4 < p3) swap(p3, p4);
    return !(p2 < p3 || p4 < p1);
  }
  return l1 <= 0 && l2 <= 0;
}