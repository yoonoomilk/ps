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
    vector<int> dist(sz, INT_MAX);
    vector<bool> inq(sz);
    queue<int> q;
    dist[s] = 0;
    inq[s] = true;
    q.push(s);
    while(q.size()) {
      int cur = q.front();
      q.pop();
      inq[cur] = false;
      for(auto [loc, left, cost, rev] : edges[cur]) if(left && dist[loc] > dist[cur] + cost) {
        dist[loc] = dist[cur] + cost;
        if(!inq[loc]) q.push(loc);
        inq[loc] = true;
      }
    }
    while(1) {
      vector<int> idx(sz);
      vector<char> visited(sz);
      auto dfs = [&](auto self, int cur, int tmp) {
        visited[cur] = true;
        if(cur == e) return tmp;
        for(;idx[cur] < edges[cur].size();idx[cur]++) {
          auto& [loc, left, cost, rev] = edges[cur][idx[cur]];
          if(!visited[loc] && dist[loc] == dist[cur] + cost && left) {
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
        memset(visited.data(), 0, visited.size());
      };
      {
        int tmp = INT_MAX;
        for(int i = 0;i < sz;i++) if(visited[i]) {
          for(auto [loc, left, cost, rev] : edges[i]) {
            if(left && !visited[loc]) tmp = min(tmp, dist[i] - dist[loc] + cost);
          }
        }
        if(tmp == INT_MAX) break;
        for(int i = 0;i < sz;i++) if(!visited[i]) dist[i] += tmp;
      }
    }
    return {flow, cost};
  }
};