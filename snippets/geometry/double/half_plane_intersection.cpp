#include "geometry/double/geometry-double.cpp"
#include "geometry/double/line_intersection-double.cpp"

polygon half_plane_intersection(vector<line>& lines) {
  auto bad = [](line& a, line& b, line& c) {
    point v;
    if(!line_intersection(a, b, v)) return false;
    double d = (c.t - c.s) / (v - c.s);
    return d < 1e-9;
  };
  sort(lines.begin(), lines.end());
  vector<line> unique_lines{lines[0]};
  for(int i = 1;i < lines.size();i++) {
    line& bef = unique_lines.back(), cur = lines[i];;
    double d = (bef.t - bef.s) / (cur.t - cur.s);
    if(abs(d) > 1e-9) unique_lines.push_back(cur);
    else if(ccw(bef.s, bef.t, cur.s) > 0) bef = cur;
  }
  swap(lines, unique_lines);
  deque<line> dq;
  for(line& i : lines) {
    while(dq.size() >= 2 && bad(dq[dq.size() - 2], dq.back(), i)) dq.pop_back();
    while(dq.size() >= 2 && bad(dq[0], dq[1], i)) dq.pop_front();
    if(dq.size() < 2 || !bad(dq.back(), i, dq[0])) dq.push_back(i);
  }
  polygon tmp;
  if(dq.size() >= 3) for(int i = 0;i < dq.size();i++) {
    point v;
    if(line_intersection(dq[i], dq[(i + 1) % dq.size()], v)) tmp.push_back(v);
  }
  return tmp;
}