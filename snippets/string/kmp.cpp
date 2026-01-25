auto kmp(string_view s, string_view p) {
  int n = s.size(), m = p.size();
  vector<int> pi(m), match;
  for(int i = 1, j = 0;i < m;i++) {
    while(j && p[i] != p[j]) j = pi[j - 1];
    if(p[i] == p[j]) pi[i] = ++j;
  }
  for(int i = 0, j = 0;i < n;i++) {
    while(j && s[i] != p[j]) j = pi[j - 1];
    if(s[i] != p[j]) continue;
    if(j == m - 1) {
      match.push_back(i - j);
      j = pi[j];
    } else j++;
  }
  return tuple{pi, match};
}