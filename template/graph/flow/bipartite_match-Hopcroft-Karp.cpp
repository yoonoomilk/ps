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
    vector<int> idx_l(l, -1), idx_r(r, -1), level(l);
    while(1) {
      queue<int> q;
      for(int i = 0;i < l;i++) {
        if(!visited[i]) q.push(i);
        else level[i] = 1e9;
      }
      while(q.size()) {
        int cur = q.front();
        q.pop();
        for(int i : edges[cur]) if(idx_r[i] != -1 && level[idx_r[i]] == 1e9) {
          level[idx_r[i]] = level[cur] + 1;
          q.push(idx_r[i]);
        }
      }
      int tmp = 0;
      function<bool(int)> dfs = [&](int cur) {
        for(int i : edges[cur]) if(idx_r[i] == -1 || level[idx_r[i]] == level[cur] + 1 && dfs(idx_r[i])) {
          visited[cur] = true;
          idx_l[cur] = i;
          idx_r[i] = cur;
          return true;
        }
        return false;
      };
      for(int i = 0;i < l;i++) if(!visited[i] && dfs(i)) tmp++;
      if(tmp == 0) break;
      ret += tmp;
    }
    return ret;
  }
};