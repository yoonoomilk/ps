class suffix_array {
  const int sz;

public:
  vector<int> pos, suf, lcp;

  template <typename I>
  suffix_array(I s, I e) : sz(distance(s, e)), pos(s, e), suf(sz), lcp(sz) {
    iota(suf.begin(), suf.end(), 0);
    for(int i = 1;i < sz;i *= 2) {
      auto cmp = [&](int a, int b) {
        if(pos[a] != pos[b]) return pos[a] < pos[b];
        a += i; b += i;
        return (a < sz && b < sz) ? (pos[a] < pos[b]) : (a > b);
      };
      sort(suf.begin(), suf.end(), cmp);
      vector<int> tmp(sz);
      for(int j = 1;j < sz;j++) tmp[j] = tmp[j - 1] + cmp(suf[j - 1], suf[j]);
      for(int j = 0;j < sz;j++) pos[suf[j]] = tmp[j];
      if(tmp[sz - 1] == sz - 1) break;
    }
    for(int i = 0, j = 0;i < sz;i++) {
      if(pos[i]) {
        while(s[i + j] == s[suf[pos[i] - 1] + j]) j++;
        lcp[pos[i]] = j;
        j = max(0, j - 1);
      } else lcp[pos[i]] = -1;
    }
  }
};