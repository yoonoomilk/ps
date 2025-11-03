class lowest_common_ancestor {
  const int sz;
  vector<int> weight, dep, pa, top;
  vector<vector<int>> edges;

public:
  lowest_common_ancestor(int n) : sz(n + 1), 
    weight(sz), dep(sz), pa(sz), top(sz),
    edges(sz) {}

  void add(int a, int b) {
    edges[a].push_back(b);
  }

  void init(int root) {
    auto dfs = [&](auto&& dfs, int cur, int bef) {
      weight[cur] = 1;
      dep[cur] = dep[bef] + 1;
      pa[cur] = bef;
      for(int& i : edges[cur]) if(i != bef) {
        dfs(dfs, i, cur);
        weight[cur] += weight[i];
        if(weight[i] > weight[edges[cur][0]]) swap(i, edges[cur][0]);
      }
    };
    dfs(dfs, root, 0);
    auto ett = [&](auto&& ett, int cur, int bef) {
      for(int i : edges[cur]) if(i != bef) {
        top[i] = i == edges[cur][0] ? top[cur] : i;
        ett(ett, i, cur);
      }
    };
    top[root] = 1;
    ett(ett, root, 0);
  }

  int operator() (int a, int b) {
    for(;top[a] != top[b];a = pa[top[a]]) {
      if(dep[top[a]] < dep[top[b]]) swap(a, b);
    }
    return dep[a] < dep[b] ? a : b;
  }
};