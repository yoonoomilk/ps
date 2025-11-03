class max_flow {
  struct edge {
    int loc, cap, flow, rev;
  };

  const int sz;
  vector<vector<edge>> edges;

public:
  max_flow(int sz) : sz(sz), edges(sz) {}

  void add(int a, int b, int cap, bool directed = true) {
    edges[a].emplace_back(b, cap, 0, edges[b].size());
    edges[b].emplace_back(a, directed ? 0 : cap, 0, edges[a].size() - 1);
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
        for(edge &i : edges[cur]) if(level[i.loc] == -1 && i.cap > i.flow) {
          level[i.loc] = level[cur] + 1;
          q.push(i.loc);
        }
      }
      if(level[e] == -1) break;
      auto dfs = [&](auto&& dfs, int cur, int tmp) {
        if(cur == e) return tmp;
        for(int& i = idx[cur];i < edges[cur].size();i++) {
          edge& j = edges[cur][i];
          if(level[cur] + 1 == level[j.loc] && j.cap > j.flow) {
            int nxt = dfs(dfs, j.loc, min(tmp, j.cap - j.flow));
            if(nxt) {
              j.flow += nxt;
              edges[j.loc][j.rev].flow -= nxt;
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