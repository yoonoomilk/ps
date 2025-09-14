class polygon : vector<pt> {
  using super = vector<pt>;
  using super::super;

public:
  using super::push_back;
  using super::size;
  using super::begin;
  using super::end;
  using super::operator[];

  ll area2() {
    ll tmp = 0;
    for(int i = 0;i < this->size();i++) {
      pt bef = i ? (*this)[i - 1] : this->back();
      tmp += (ll)bef.x * (*this)[i].y - (ll)bef.y * (*this)[i].x;
    }
    return abs(tmp);
  }

  void convex_hull() {
    polygon tmp;
    for(int i = 1;i < this->size();i++) if((*this)[i] < (*this)[0]) iter_swap(this->begin(), this->begin() + i);
    sort(++this->begin(), this->end(), [&](pt a, pt b) {
      int w = ccw((*this)[0], a, b);
      if(w) return w < 0;
      return a < b;
    });
    tmp.push_back((*this)[0]);
    tmp.push_back((*this)[1]);
    for(int i = 2;i < this->size();i++) {
      while(tmp.size() >= 2) {
        pt cur = tmp.back();
        tmp.pop_back();
        if(ccw(tmp.back(), cur, (*this)[i]) < 0) {
          tmp.push_back(cur);
          break;
        }
      }
      tmp.push_back((*this)[i]);
    }
    *this = tmp;
  }
};