struct max_flow {
  struct edge {
    int loc, left, rev;
  };

  const int sz;
  vector<vector<edge>> edges;

  max_flow(int sz) : sz(sz), edges(sz) {}

  void add(int a, int b, int cap, bool directed = true) {
    edges[a].emplace_back(b, cap, edges[b].size());
    edges[b].emplace_back(a, directed ? 0 : cap, edges[a].size() - 1);
  }

  int operator() (int s, int e) {
    int ret = 0;
    while(1) {
      vector<int> level(sz, -1), idx(sz);
      queue<int> q;
      level[s] = 0;
      q.push(s);
      while(q.size() && level[e] == -1) {
        int cur = q.front();
        q.pop();
        for(auto [loc, left, rev] : edges[cur]) if(level[loc] == -1 && left) {
          level[loc] = level[cur] + 1;
          q.push(loc);
        }
      }
      if(level[e] == -1) break;
      auto dfs = [&](auto& self, int cur, int tmp) {
        if(cur == e) return tmp;
        for(;idx[cur] < edges[cur].size();idx[cur]++) {
          auto& [loc, left, rev] = edges[cur][idx[cur]];
          if(level[cur] + 1 == level[loc] && left) {
            int nxt = self(self, loc, min(tmp, left));
            if(nxt) {
              left -= nxt;
              edges[loc][rev].left += nxt;
              return nxt;
            }
          }
        }
        return 0;
      };
      for(int i;i = dfs(dfs, s, INT_MAX);ret += i);
    }
    return ret;
  }
};