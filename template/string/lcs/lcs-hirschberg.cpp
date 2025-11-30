string lcs(string_view a, string_view b) {
  string ans;
  auto f = [&](auto& self, int l1, int r1, int l2, int r2) -> void {
    if(l1 > r1) return;
    if(l1 == r1) {
      for(int i = l2;i <= r2;i++) if(b[i] == a[l1]) {
        ans.push_back(b[i]);
        break;
      }
      return;
    }
    int m = (l1 + r1) / 2, sz = r2 - l2 + 2;
    // lcs(l1, m, l2, r2), ~lcs(m + 1, r1, l2, r2)
    vector<int> t1(sz), t2(sz);
    {
      vector<dynamic_bitset> loc(128, dynamic_bitset(sz));
      dynamic_bitset dp(sz);
      for(int i = l2;i <= r2;i++) loc[b[i]][i - l2] = true;
      for(int i = l1;i <= m;i++) {
        dynamic_bitset tmp = loc[a[i]] | dp;
        dp <<= 1;
        dp[0] = true;
        dp = tmp & (tmp ^ (tmp - dp));
      }
      for(int i = l2;i <= r2;i++) t1[i - l2 + 1] = t1[i - l2] + dp[i - l2];
    }
    {
      vector<dynamic_bitset> loc(128, dynamic_bitset(sz));
      dynamic_bitset dp(sz);
      for(int i = r2;i >= l2;i--) loc[b[i]][r2 - i] = true;
      for(int i = r1;i > m;i--) {
        dynamic_bitset tmp = loc[a[i]] | dp;
        dp <<= 1;
        dp[0] = true;
        dp = tmp & (tmp ^ (tmp - dp));
      }
      for(int i = r2;i >= l2;i--) t2[i - l2] = t2[i - l2 + 1] + dp[r2 - i];
    }
    pii mx = {-1, 0};
    for(int i = l2;i <= r2 + 1;i++) mx = max(mx, {t1[i - l2] + t2[i - l2], i});
    self(self, l1, m, l2, mx.second - 1);
    self(self, m + 1, r1, mx.second, r2);
  };
  f(f, 0, a.size() - 1, 0, b.size() - 1);
  return ans;
}