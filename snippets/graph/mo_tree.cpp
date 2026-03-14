template <typename Use, typename Unuse, typename Calc, typename... Args>
class mo_tree {
  const int sz;
  vector<pii> edges;
  vector<tuple<int, int, int, ll, int, Args...>> queries;
  Use use;
  Unuse unuse;
  Calc calc;

public:
  mo_tree(int n) : sz(n + 1) {}

  void add(int a, int b) {
    edges.emplace_back(a, b);
    edges.emplace_back(b, a);
  }

  void operator() (int a, int b, Args&... args) {
    queries.emplace_back(a, b, queries.size(), 0, -1, args...);
  }

  auto init() {
    vector<int> cnt(sz + 1), csr(edges.size());
    for(auto [a, b] : edges) cnt[a + 1]++;
    for(int i = 1;i <= sz;i++) cnt[i] += cnt[i - 1];
    for(auto [a, b] : edges) csr[cnt[a]++] = b;
    edges = vector<pii>();

    vector<int> arr(sz * 2), in(sz), out(sz), dep(sz), pa(sz), top(sz);

    {
      vector<int> weight(sz);
      auto dfs = [&](auto& self, int cur, int bef) -> void {
        weight[cur] = 1;
        dep[cur] = dep[bef] + 1;
        pa[cur] = bef;
        for(int i = cnt[cur - 1];i < cnt[cur];i++) if(csr[i] != bef) {
          self(self, csr[i], cur);
          weight[cur] += weight[csr[i]];
          if(weight[csr[i]] > weight[csr[cnt[cur - 1]]]) swap(csr[i], csr[cnt[cur - 1]]);
        }
      };
      dfs(dfs, 1, 0);
    }
    int ettn = 0;
    auto ett = [&](auto& self, int cur, int bef) -> void {
      arr[in[cur] = ettn++] = cur;
      for(int i = cnt[cur - 1];i < cnt[cur];i++) if(csr[i] != bef) {
        top[csr[i]] = csr[i] == csr[cnt[cur - 1]] ? top[cur] : csr[i];
        self(self, csr[i], cur);
      }
      arr[out[cur] = ettn++] = cur;
    };
    top[1] = 1;
    ett(ett, 1, 0);

    auto lca = [&](int a, int b) {
      for(;top[a] != top[b];a = pa[top[a]]) if(dep[top[a]] < dep[top[b]]) swap(a, b);
      return dep[a] < dep[b] ? a : b;
    };

    for(auto& q : queries) {
      int &a = get<0>(q), &b = get<1>(q);
      if(in[a] > in[b]) swap(a, b);
      int &c = get<4>(q) = lca(a, b), x = a == c ? in[a] : out[a], y = in[b];
      ll &ord = get<3>(q);
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

    vector<bool> used(sz);
    vector<decltype(calc(declval<Args>()...))> ans(queries.size());

    int l = 0, r = -1;
    auto toggle = [&](int i) {
      if(used[i]) unuse(i);
      else use(i);
      used[i] = !used[i];
    };
    for(auto& q : queries) {
      int a = get<0>(q), b = get<1>(q), i = get<2>(q), c = get<4>(q);
      int ll = a == c ? in[a] : out[a], rr = in[b];
      while(ll < l) toggle(arr[--l]);
      while(ll > l) toggle(arr[l++]);
      while(rr < r) toggle(arr[r--]);
      while(rr > r) toggle(arr[++r]);
      if(a != c) toggle(c);
      ans[i] = apply([&](auto&, auto&, auto&, auto&, auto&, auto&... args) { return calc(args...); }, q);
      if(a != c) toggle(c);
    }
    return ans;
  }
};