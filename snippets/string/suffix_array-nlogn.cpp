template <typename I>
auto suffix_array(I s, I e) {
  int n = distance(s, e);
  vector<int> pos(s, e), suf(n), lcp(n);
  iota(suf.begin(), suf.end(), 0);
  auto rank = [&](int i) { return i < n ? pos[i] + 1 : 0; };
  for(int i = 1;i < n;i *= 2) {
    vector<int> tmp(n), cnt(max(n, 256));
    for(int j = 0;j < n;j++) cnt[rank(suf[j] + i)]++;
    for(int j = 1;j < cnt.size();j++) cnt[j] += cnt[j - 1];
    for(int j = n;j--;) tmp[--cnt[rank(suf[j] + i)]] = suf[j];
    fill(cnt.begin(), cnt.end(), 0);
    for(int j = 0;j < n;j++) cnt[rank(tmp[j])]++;
    for(int j = 1;j < cnt.size();j++) cnt[j] += cnt[j - 1];
    for(int j = n;j--;) suf[--cnt[rank(tmp[j])]] = tmp[j];
    tmp[suf[0]] = 0;
    for(int j = 1;j < n;j++) tmp[suf[j]] = tmp[suf[j - 1]] + (rank(suf[j]) != rank(suf[j - 1]) || rank(suf[j] + i) != rank(suf[j - 1] + i));
    pos = tmp;
    if(pos[suf[n - 1]] == n - 1) break;
  }
  for(int i = 0, j = 0;i < n;i++) {
    if(pos[i]) {
      while(s[i + j] == s[suf[pos[i] - 1] + j]) j++;
      lcp[pos[i]] = j;
      if(j > 0) j--;
    } else lcp[pos[i]] = -1;
  }
  return tuple{pos, suf, lcp};
}