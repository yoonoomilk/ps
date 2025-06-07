class bipartite_match {
  const int l, r;
  vector<vector<int>> edges;

public:
  bipartite_match(int l, int r) : l(l), r(r), edges(l) {}

  void add(int a, int b) {
    edges[a].push_back(b);
  }

  int operator() () {
    int ret = 0;
    vector<bool> visited(l);
    vector<int> idx(r, -1);
    auto dfs = [&](int cur) -> bool {
      visited[cur] = true;
      for(int i : edges[cur]) if(idx[i] == -1) {
        idx[i] = cur;
        return true;
      }
      for(int i : edges[cur]) if(idx[i] != -1 && !visited[idx[i]] && dfs(idx[i])) {
        idx[i] = cur;
        return true;
      }
      return false;
    };
    for(int i = 0;i < l;i++) {
      visited.assign(l, 0);
      ret += dfs(i);
    }
    return ret;
  }
};