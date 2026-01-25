string bwt_inverse(string_view s) {
  int n = s.size();
  vector<int> cnt(128), occ(128), loc(128);
  for(char c : s) cnt[c]++;
  for(int c = 0, i = 0;c < 128;c++) {
    loc[c] = i;
    i += cnt[c];
  }
  vector<int> lf(n);
  for(int i = 0;i < n;i++) lf[i] = loc[s[i]] + occ[s[i]]++;
  string tmp(n, '\0');
  for(int i = n, j = min_element(s.begin(), s.end()) - s.begin();i--;j = lf[j]) tmp[i] = s[j];
  return tmp;
}