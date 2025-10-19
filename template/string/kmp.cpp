vector<int> pidx(string_view p) {
  vector<int> pi(p.size());
  for(int i = 1, j = 0;i < p.size();i++) {
    while(j && p[i] != p[j]) j = pi[j - 1];
    if(p[i] == p[j]) pi[i] = ++j;
  }
  return pi;
}

vector<int> kmp(string_view s, string_view p) {
  vector<int> pi = pidx(p), match;
  for(int i = 0, j = 0;i < s.size();i++) {
    while(j && s[i] != p[j]) j = pi[j - 1];
    if(s[i] != p[j]) continue;
    if(j == p.size() - 1) {
      match.push_back(i - j);
      j = pi[j];
    } else j++;
  }
  return match;
}