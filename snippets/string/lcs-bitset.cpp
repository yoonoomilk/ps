#include <x86intrin.h>

int lcs(string_view a, string_view b) {
  int n = a.size(), m = b.size(), sz = m + 63 >> 6;
  vector<vector<uint64_t>> loc(128, vector<uint64_t>(sz));
  vector<uint64_t> dp(sz);
  for(int i = 0;i < m;i++) loc[b[i]][i >> 6] |= 1ULL << (i & 63);
  for(int i = 0;i < n;i++) for(int j = 0, c = 0;j < sz;j++) {
    uint64_t x = loc[a[i]][j] | dp[j];
    c = _subborrow_u64(c, dp[j], dp[j] ^ x, dp.data() + j);
    dp[j] &= x;
  }
  int tmp = 0;
  for(int i = 0;i < sz;i++) tmp += __builtin_popcountll(dp[i]);
  return tmp;
}