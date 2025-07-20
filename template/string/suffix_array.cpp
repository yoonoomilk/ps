// O(N log^2 N)
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

// O(N log N)
class suffix_array {
  const int sz;

public:
  vector<int> pos, suf, lcp;

  template <typename I>
  suffix_array(I s, I e) : sz(distance(s, e)), pos(s, e), suf(sz), lcp(sz) {
    iota(suf.begin(), suf.end(), 0);
    auto rank = [&](int i) { return i < sz ? pos[i] + 1 : 0; };
    for(int i = 1;i < sz;i *= 2) {
      vector<int> tmp(sz), cnt(max(sz, 256));
      for(int j = 0;j < sz;j++) cnt[rank(suf[j] + i)]++;
      for(int j = 1;j < cnt.size();j++) cnt[j] += cnt[j - 1];
      for(int j = sz;j--;) tmp[--cnt[rank(suf[j] + i)]] = suf[j];
      fill(cnt.begin(), cnt.end(), 0);
      for(int j = 0;j < sz;j++) cnt[rank(tmp[j])]++;
      for(int j = 1;j < cnt.size();j++) cnt[j] += cnt[j - 1];
      for(int j = sz;j--;) suf[--cnt[rank(tmp[j])]] = tmp[j];
      tmp[suf[0]] = 0;
      for(int j = 1;j < sz;j++) tmp[suf[j]] = tmp[suf[j - 1]] + (rank(suf[j]) != rank(suf[j - 1]) || rank(suf[j] + i) != rank(suf[j - 1] + i));
      pos = tmp;
      if(pos[suf[sz - 1]] == sz - 1) break;
    }
    for(int i = 0, j = 0;i < sz;i++) {
      if(pos[i]) {
        while(s[i + j] == s[suf[pos[i] - 1] + j]) j++;
        lcp[pos[i]] = j;
        if(j > 0) j--;
      } else lcp[pos[i]] = -1;
    }
  }
};