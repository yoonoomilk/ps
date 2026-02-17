template <typename Use, typename Unuse, typename Calc>
class mo {
  const int sz;
  vector<tuple<int, int, int, ll>> queries;
  Use use;
  Unuse unuse;
  Calc calc;

public:
  mo(int n) : sz(n + 1) {}

  void operator() (int a, int b) {
    queries.emplace_back(a, b, queries.size(), 0);
  }

  template <int sq>
  auto init() {
    vector<decltype(calc())> ans(queries.size());

    for(auto& [l, r, i, ord] : queries) {
      int x = l, y = r;
      int lg = __lg(max(x, y) * 2 + 1) | 1;
      ll maxn = (1LL << lg) - 1;
      for(ll s = 1LL << (lg - 1);s;s >>= 1) {
        bool rx = x & s, ry = y & s;
        ord = (ord << 2) | (rx ? ry ? 2 : 1 : ry ? 3 : 0);
        if(rx) continue;
        if(ry) x ^= maxn, y ^= maxn;
        swap(x, y);
      }
    }

    sort(queries.begin(), queries.end(), [&](auto& a, auto& b) { return get<3>(a) < get<3>(b); });
 
    int l = 0, r = -1;
    for(auto [ll, rr, i, ord] : queries) {
      while(ll < l) use(--l, 0);
      while(rr > r) use(++r, 1);
      while(ll > l) unuse(l++, 0);
      while(rr < r) unuse(r--, 1);
      ans[i] = calc();
    }
    return ans;
  }
};