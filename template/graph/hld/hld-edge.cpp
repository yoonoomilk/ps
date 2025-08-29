template <typename T, typename Merge>
class heavy_light_decomposition {
  const int sz;
  const T raw;
  vector<int> weight, dep, pa, top, in;
  vector<vector<int>> edges;
  segment_tree<T, Merge> seg;
  Merge op;
  struct lca_op {
    pii operator() (pii a, pii b) {
      return min(a, b);
    }
  };
  segment_tree<pii, lca_op> lca;

  T query(int a, int b) {
    T s = raw;
    for(;top[a] != top[b];a = pa[top[a]]) {
      if(dep[top[a]] < dep[top[b]]) swap(a, b);
      s = op(s, seg(in[top[a]], in[a]));
    }
    if(dep[a] > dep[b]) swap(a, b);
    return op(s, seg(in[a] + 1, in[b]));
  }

public:
  heavy_light_decomposition(int n, T raw) : sz(n + 1), raw(raw),
    weight(sz), dep(sz), pa(sz), top(sz), in(sz),
    edges(sz), seg(sz * 2, raw), lca(sz * 2, {sz, sz}) {}

  void add(int a, int b) {
    edges[a].push_back(b);
  }

  void init() {
    function<void(int, int)> dfs = [&](int cur, int bef) {
      weight[cur] = 1;
      dep[cur] = dep[bef] + 1;
      pa[cur] = bef;
      for(int& i : edges[cur]) if(i != bef) {
        dfs(i, cur);
        weight[cur] += weight[i];
        if(weight[i] > weight[edges[cur][0]]) swap(i, edges[cur][0]);
      }
    };
    dfs(1, 0);
    int ettn = 0;
    function <void(int, int)> ett = [&](int cur, int bef) {
      lca.update(in[cur] = ettn++, {dep[cur], cur});
      for(int i : edges[cur]) if(i != bef) {
        top[i] = (i == edges[cur][0] ? top[cur] : i);
        ett(i, cur);
        lca.update(ettn++, {dep[cur], cur});
      }
    };
    top[1] = 1;
    ett(1, 0);
  }

  void update(int a, int b, T v) {
    if(dep[a] < dep[b]) swap(a, b);
    seg.update(in[a], v);
  }

  T operator() (int a, int b) {
    int l = lca(min(in[a], in[b]), max(in[a], in[b])).second;
    return op(query(a, l), query(b, l));
  }
};