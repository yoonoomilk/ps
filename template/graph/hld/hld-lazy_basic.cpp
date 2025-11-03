template <typename T>
class heavy_light_decomposition {
  const int sz;
  vector<int> weight, dep, pa, top, in;
  vector<vector<int>> edges;
  lazy_fenwick_tree<T> seg;

public:
  heavy_light_decomposition(int n) : sz(n + 1),
    weight(sz), dep(sz), pa(sz), top(sz), in(sz),
    edges(sz), seg(sz) {}

  void add(int a, int b) {
    edges[a].push_back(b);
  }

  void init() {
    auto dfs = [&](auto&& dfs, int cur, int bef) -> void {
      weight[cur] = 1;
      dep[cur] = dep[bef] + 1;
      pa[cur] = bef;
      for(int& i : edges[cur]) if(i != bef) {
        dfs(dfs, i, cur);
        weight[cur] += weight[i];
        if(weight[i] > weight[edges[cur][0]]) swap(i, edges[cur][0]);
      }
    };
    dfs(dfs, 1, 0);
    int ettn = 0;
    auto ett = [&](auto&& ett, int cur, int bef) -> void {
      in[cur] = ettn++;
      for(int i : edges[cur]) if(i != bef) {
        top[i] = i == edges[cur][0] ? top[cur] : i;
        ett(ett, i, cur);
      }
    };
    top[1] = 1;
    ett(ett, 1, 0);
  }

  void update(int a, int b, T v) {
    for(;top[a] != top[b];a = pa[top[a]]) {
      if(dep[top[a]] < dep[top[b]]) swap(a, b);
      seg.update(in[top[a]], in[a], v);
    }
    if(dep[a] > dep[b]) swap(a, b);
    seg.update(in[a] + 1, in[b], v);
  }

  T operator() (int a, int b) {
    T s = 0;
    for(;top[a] != top[b];a = pa[top[a]]) {
      if(dep[top[a]] < dep[top[b]]) swap(a, b);
      s += seg(in[top[a]], in[a]);
    }
    if(dep[a] > dep[b]) swap(a, b);
    return s + seg(in[a] + 1, in[b]);
  }
};