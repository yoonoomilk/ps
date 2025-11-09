template <typename T, typename L, typename Merge, typename Update, typename Composition>
class heavy_light_decomposition {
  const int sz;
  const T raw;
  const L lazy_raw;
  vector<int> weight, dep, pa, top, in, out;
  vector<vector<int>> edges;
  lazy_segment_tree<T, L, Merge, Update, Composition> seg;
  Merge op;

public:
  heavy_light_decomposition(int n, T raw, L lazy_raw) : sz(n + 1), raw(raw), lazy_raw(lazy_raw),
    weight(sz), dep(sz), pa(sz), top(sz), in(sz), out(sz),
    edges(sz), seg(sz, raw, lazy_raw) {
    for(int i = 0;i < sz;i++) seg.set(i, {0, 1});
    seg.init();
  }

  void add(int a, int b) {
    edges[a].push_back(b);
  }

  void init() {
    auto dfs = [&](auto& self, int cur, int bef) -> void {
      weight[cur] = 1;
      dep[cur] = dep[bef] + 1;
      pa[cur] = bef;
      for(int& i : edges[cur]) if(i != bef) {
        self(self, i, cur);
        weight[cur] += weight[i];
        if(weight[i] > weight[edges[cur][0]]) swap(i, edges[cur][0]);
      }
    };
    dfs(dfs, 1, 0);
    int ettn = 0;
    auto ett = [&](auto& self, int cur, int bef) -> void {
      in[cur] = ettn++;
      for(int i : edges[cur]) if(i != bef) {
        top[i] = i == edges[cur][0] ? top[cur] : i;
        self(self, i, cur);
      }
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