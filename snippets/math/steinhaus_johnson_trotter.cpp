// https://en.wikipedia.org/wiki/Steinhaus–Johnson–Trotter_algorithm

template <typename I>
class steinhaus_johnson_trotter {
  const int n;
  I s, e;
  vector<char> dir;

public:
  steinhaus_johnson_trotter(I s, I e) : n(distance(s, e)), s(s), e(e), dir(n, -1) {
    assert(is_sorted(s, e));
  }

  bool next() {
    int n = distance(s, e);
    int tmp = -1;
    for(int i = 0;i < n;i++) {
      int nxt = i + dir[i];
      if(nxt < 0 || nxt >= n) continue;
      if(s[i] > s[nxt] && (tmp == -1 || s[i] > s[tmp])) tmp = i;
    }
    if(tmp == -1) return false;
    int nxt = tmp + dir[tmp];
    for(int i = 0;i < n;i++) if(s[i] > s[nxt]) dir[i] *= -1;
  }
};