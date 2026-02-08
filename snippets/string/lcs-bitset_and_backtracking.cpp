#include <x86intrin.h>

string lcs(string_view a, string_view b) {
  int n = a.size(), m = b.size(), sz = m + 63 >> 6;
  vector loc(128, vector(sz, 0ULL)), dp(a.size() + 1, vector(sz, 0ULL));
  for(int i = 0;i < m;i++) loc[b[i]][i >> 6] |= 1ULL << (i & 63);
  for(int i = 0;i < n;i++) for(int j = 0, c = 0;j < sz;j++) {
    uint64_t x = loc[a[i]][j] | dp[i][j];
    c = _subborrow_u64(c, dp[i][j], dp[i][j] ^ x, dp[i + 1].data() + j);
    dp[i + 1][j] &= x;
  }
  string tmp;
  for(int i = n, j = m - 1;i;i--) {
    while(j >= 0 && !((dp[i][j >> 6] >> (j & 63)) & 1)) j--;
    if(j < 0) break;
    while(i > 0 && ((dp[i - 1][j >> 6] >> (j & 63)) & 1)) i--;
    tmp.push_back(b[j--]);
  }
  reverse(tmp.begin(), tmp.end());
  return tmp;
}