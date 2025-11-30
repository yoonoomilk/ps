int lcs(string_view a, string_view b) {
  int n = a.size(), m = b.size();
  dynamic_bitset loc[128], dp(m);
  for(int i = 0;i < 128;i++) loc[i].init(m);
  for(int i = 0;i < m;i++) loc[b[i]][i] = true;
  for(int i = 0;i < n;i++) {
    dynamic_bitset tmp = loc[a[i]] | dp;
    dp <<= 1;
    dp[0] = true;
    dp = tmp & (tmp ^ (tmp - dp));
  }
  return dp.count();
}