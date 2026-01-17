#include "range_query/segment_tree/segment_tree.cpp"

template <typename T, typename Merge, T raw = T()>
class heavy_light_decomposition {
  const int sz;
  vector<pii> edges;
  vector<int> dep, pa, top, in;
  segment_tree<T, Merge, raw> seg;
  Merge op;

public:
  heavy_light_decomposition(int n) : sz(n + 1), dep(sz), pa(sz), top(sz), in(sz), seg(sz) {}

  void add(int a, int b, bool directed = true) {
    edges.emplace_back(a, b);
    if(!directed) edges.emplace_back(b, a);
  }

  void init() {
    vector<int> cnt(sz + 1), csr(edges.size());
    for(auto [a, b] : edges) cnt[a + 1]++;
    for(int i = 1;i <= sz;i++) cnt[i] += cnt[i - 1];
    for(auto [a, b] : edges) csr[cnt[a]++] = b;
    edges = vector<pii>();

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
    int ettn = 0;
    auto ett = [&](auto& self, int cur, int bef) -> void {
      in[cur] = ettn++;
      for(int i = cnt[cur - 1];i < cnt[cur];i++) if(csr[i] != bef) {
        top[csr[i]] = csr[i] == csr[cnt[cur - 1]] ? top[cur] : csr[i];
        self(self, csr[i], cur);
      }
    };
    top[1] = 1;
    ett(ett, 1, 0);
  }

  void update(int a, const T& v) {
    seg.update(in[a], v);
  }

  T operator() (int a, int b) {
    T s = raw;
    for(;top[a] != top[b];a = pa[top[a]]) {
      if(dep[top[a]] < dep[top[b]]) swap(a, b);
      s = op(s, seg(in[top[a]], in[a]));
    }
    if(dep[a] > dep[b]) swap(a, b);
    return op(s, seg(in[a], in[b]));
  }
};