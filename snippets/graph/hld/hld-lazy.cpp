#include "range_query/segment_tree/lazy_segment_tree.cpp"

template <typename T, typename L, typename Merge, typename Update, typename Composition>
class heavy_light_decomposition {
  const int sz;
  const T raw;
  const L lazy_raw;
  vector<pii> edges;
  vector<int> dep, pa, top, in, out;
  lazy_segment_tree<T, L, Merge, Update, Composition> seg;
  Merge op;

public:
  heavy_light_decomposition(int n, T raw = T(), L lazy_raw = L()) : sz(n + 1), raw(raw), lazy_raw(lazy_raw),
    dep(sz), pa(sz), top(sz), in(sz), out(sz), seg(sz, raw, lazy_raw) {
    for(int i = 0;i < sz;i++) seg.set(i, {0, 1});
    seg.init();
  }

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
      out[cur] = ettn - 1;
    };
    top[1] = 1;
    ett(ett, 1, 0);
  }

  void update(int a, L v) {
    seg.update(in[a], out[a], v);
  }
  void update(int a, int b, L v) {
    for(;top[a] != top[b];a = pa[top[a]]) {
      if(dep[top[a]] < dep[top[b]]) swap(a, b);
      seg.update(in[top[a]], in[a], v);
    }
    if(dep[a] > dep[b]) swap(a, b);
    seg.update(in[a], in[b], v);
  }

  T operator() (int a) {
    return seg(in[a], out[a]);
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