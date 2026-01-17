#include <x86intrin.h>

string lcs(string_view a, string_view b) {
  string tmp;
  auto f = [&](auto& self, int l1, int r1, int l2, int r2) -> void {
    if(l1 > r1) return;
    if(l1 == r1) {
      for(int i = l2;i <= r2;i++) if(b[i] == a[l1]) {
        tmp.push_back(b[i]);
        break;
      }
      return;
    }
    int m = (l1 + r1) / 2, len = r2 - l2 + 2, sz = len + 63 >> 6;
    vector<int> t1(len), t2(len);
    {
      vector<vector<uint64_t>> loc(128, vector<uint64_t>(sz));
      vector<uint64_t> dp(sz);
      for(int i = l2;i <= r2;i++) loc[b[i]][i - l2 >> 6] |= 1ULL << (i - l2 & 63);
      for(int i = l1;i <= m;i++) for(int j = 0, c = 0;j < sz;j++) {
        uint64_t x = loc[a[i]][j] | dp[j];
        c = _subborrow_u64(c, dp[j], dp[j] ^ x, dp.data() + j);
        dp[j] &= x;
      }
      for(int i = l2;i <= r2;i++) t1[i - l2 + 1] = t1[i - l2] + ((dp[i - l2 >> 6] >> (i - l2 & 63)) & 1);
    }
    {
      vector<vector<uint64_t>> loc(128, vector<uint64_t>(sz));
      vector<uint64_t> dp(sz);
      for(int i = r2;i >= l2;i--) loc[b[i]][r2 - i >> 6] |= 1ULL << (r2 - i & 63);
      for(int i = r1;i > m;i--) for(int j = 0, c = 0;j < sz;j++) {
        uint64_t x = loc[a[i]][j] | dp[j];
        c = _subborrow_u64(c, dp[j], dp[j] ^ x, dp.data() + j);
        dp[j] &= x;
      }
      for(int i = r2;i >= l2;i--) t2[i - l2] = t2[i - l2 + 1] + ((dp[r2 - i >> 6] >> (r2 - i & 63)) & 1);
    }
    pii mx = {-1, 0};
    for(int i = l2;i <= r2 + 1;i++) mx = max(mx, {t1[i - l2] + t2[i - l2], i});
    self(self, l1, m, l2, mx.second - 1);
    self(self, m + 1, r1, mx.second, r2);
  };
  f(f, 0, a.size() - 1, 0, b.size() - 1);
  return tmp;
}