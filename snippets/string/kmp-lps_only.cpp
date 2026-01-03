vector<int> lps(string_view p) {
  vector<int> pi(p.size());
  for(int i = 1, j = 0;i < p.size();i++) {
    while(j && p[i] != p[j]) j = pi[j - 1];
    if(p[i] == p[j]) pi[i] = ++j;
  }
  return pi;
}