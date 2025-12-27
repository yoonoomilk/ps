template <typename I>
auto suffix_array(I s, I e) {
  int n = distance(s, e);
  vector<int> pos(s, e), suf(n), lcp(n);
  iota(suf.begin(), suf.end(), 0);
  for(int i = 1;i < n;i *= 2) {
    auto cmp = [&](int a, int b) {
      if(pos[a] != pos[b]) return pos[a] < pos[b];
      a += i; b += i;
      return (a < n && b < n) ? (pos[a] < pos[b]) : (a > b);
    };
    sort(suf.begin(), suf.end(), cmp);
    vector<int> tmp(n);
    for(int j = 1;j < n;j++) tmp[j] = tmp[j - 1] + cmp(suf[j - 1], suf[j]);
    for(int j = 0;j < n;j++) pos[suf[j]] = tmp[j];
    if(tmp[n - 1] == n - 1) break;
  }
  for(int i = 0, j = 0;i < n;i++) {
    if(pos[i]) {
      while(s[i + j] == s[suf[pos[i] - 1] + j]) j++;
      lcp[pos[i]] = j;
      j = max(0, j - 1);
    } else lcp[pos[i]] = -1;
  }
  return tuple{pos, suf, lcp};
}