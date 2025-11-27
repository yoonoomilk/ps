struct universal_tree {
  const unsigned int sz, lg;
  vector<int> dep;
  vector<vector<int>> edges, pa;

  universal_tree(int n) : sz(n + 1), lg(bit_width(sz)),
    dep(sz), pa(sz, vector<int>(lg)), 
    edges(sz) {}

  void add(int a, int b, bool directed = true) {
    edges[a].push_back(b);
    if(!directed) edges[b].push_back(a);
  }

  void init(int root) {
    auto dfs = [&](auto& self, int cur, int bef) -> void {
      dep[cur] = dep[bef] + 1;
      pa[cur][0] = bef;
      for(int i = 1;i < lg && pa[cur][i - 1];i++) pa[cur][i] = pa[pa[cur][i - 1]][i - 1];
      for(int i : edges[cur]) if(i != bef) self(self, i, cur);
    };
    dfs(dfs, root, 0);
  }

  int lca(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    for(int i = lg, j = dep[a] - dep[b];i--;) if(j & (1 << i)) a = pa[a][i];
    if(a == b) return a;
    for(int i = lg;i--;) if(pa[a][i] != pa[b][i]) {
      a = pa[a][i];
      b = pa[b][i];
    }
    return pa[a][0];
  }

  int lift(int a, int d) {
    for(int i = lg;i--;) if(d & (1 << i)) a = pa[a][i];
    return a;
  }
};