struct min_cost_max_flow {
  struct edge {
    int loc, left, cost, rev;
  };

  const int sz;
  vector<vector<edge>> edges;

  min_cost_max_flow(int sz) : sz(sz), edges(sz) {}

  void add(int a, int b, int cap, int cost, bool directed = true) {
    edges[a].emplace_back(b, cap, cost, edges[b].size());
    edges[b].emplace_back(a, directed ? 0 : cap, -cost, edges[a].size() - 1);
  }

  pii operator() (int s, int e) {
    int flow = 0, cost = 0;
    while(1) {
      vector<int> dist(sz, INT_MAX), idx(sz);
      vector<char> inq(sz);
      queue<int> q;
      dist[s] = 0;
      inq[s] = 1;
      q.push(s);
      while(q.size()) {
        int cur = q.front();
        q.pop();
        inq[cur] = 0;
        for(auto [loc, left, cost, rev] : edges[cur]) if(left && dist[loc] > dist[cur] + cost) {
          dist[loc] = dist[cur] + cost;
          if(!inq[loc]) q.push(loc);
          inq[loc] = 1;
        }
      }
      if(dist[e] == INT_MAX) break;
      auto dfs = [&](auto& self, int cur, int tmp) {
        inq[cur] = 1;
        q.push(cur);
        if(cur == e) return tmp;
        for(;idx[cur] < edges[cur].size();idx[cur]++) {
          auto& [loc, left, cost, rev] = edges[cur][idx[cur]];
          if(!inq[loc] && dist[loc] == dist[cur] + cost && left) {
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
      for(int i;i = dfs(dfs, s, INT_MAX);) {
        flow += i;
        cost += dist[e] * i;
        for(;q.size();q.pop()) inq[q.front()] = 0;
      };
    }
    return {flow, cost};
  }
};