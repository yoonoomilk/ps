polygon half_plane_intersection(vector<line>& lines) {
  auto bad = [](line& a, line& b, line& c) {
    point v;
    if(!line_intersection(a, b, v)) return false;
    double d = (c.t - c.s)/ (v - c.s);
    return d < 1e-9;
  };
  sort(lines.begin(), lines.end());
  vector<line> unique_lines;
  for(line i : lines) {
    if(unique_lines.size()) {
      line& prev = unique_lines.back();
      double d = (prev.t - prev.s) / (i.t - i.s);
      if(abs(d) < 1e-9) {
        if((prev.t - prev.s) / (i.s - prev.s) > 0) prev = i;
        continue;
      }
    }
    unique_lines.push_back(i);
  }
  lines = unique_lines;
  deque<line> dq;
  for(int i = 0;i < lines.size();i++) {
    while(dq.size() >= 2 && bad(dq[dq.size() - 2], dq.back(), lines[i])) dq.pop_back();
    while(dq.size() >= 2 && bad(dq[0], dq[1], lines[i])) dq.pop_front();
    if(dq.size() < 2 || !bad(dq.back(), lines[i], dq[0])) dq.push_back(lines[i]);
  }
  polygon tmp;
  if(dq.size() >= 3) for(int i = 0;i < dq.size();i++) {
    point v;
    if(intersection(dq[i], dq[(i + 1) % dq.size()], v)) tmp.push_back(v);
  }
  return tmp;
}