class const_lca {
  const int sz;
  vector<pii> edges;
  vector<int> dep, pa, top, in, mask;

public:
  const_lca(int n) : sz(n + 1),
    dep(sz), top(sz), in(sz), mask(sz) {}

  void add(int a, int b, bool directed = true) {
    edges.emplace_back(a, b);
    if (!directed) edges.emplace_back(b, a);
  }

  void init() {
    vector<int> cnt(sz + 1), csr(edges.size());
    for(auto [a, b] : edges) cnt[a + 1]++;
    for(int i = 1;i <= sz;i++) cnt[i] += cnt[i - 1];
    for(auto [a, b] : edges) csr[cnt[a]++] = b;
    edges = vector<pii>();

    vector<int> arr(sz), pa(sz);
    int ettn = 1;
    auto dfs = [&](auto& self, int cur, int bef) -> void {
      arr[in[cur] = ettn++] = cur;
      dep[cur] = dep[bef] + 1;
      pa[cur] = bef;
      for(int i = cnt[cur - 1];i < cnt[cur];i++) {
        int nxt = csr[i];
        if(nxt == bef) continue;
        self(self, nxt, cur);
        top[in[nxt]] = cur;
        if((in[cur] & -in[cur]) < (in[nxt] & -in[nxt])) in[cur] = in[nxt];
      }
    };
    dfs(dfs, 1, 0);
    for(int i = 1;i < ettn;i++) {
      int a = arr[i], b = pa[a];
      mask[a] = mask[b] | (in[a] & -in[a]);
    }
  }

  int operator() (int a, int b) {
    if(in[a] != in[b]) {
      int cur = mask[a] & mask[b] & -bit_floor<unsigned>(in[a] ^ in[b]);
      if(mask[a] != cur) {
        int tmp = bit_floor<unsigned>(mask[a] ^ cur);
        a = top[(in[a] & -tmp) | tmp];
      }
      if(mask[b] != cur) {
        int tmp = bit_floor<unsigned>(mask[b] ^ cur);
        b = top[(in[b] & -tmp) | tmp];
      }
    }
    return dep[a] < dep[b] ? a : b;
  }
};