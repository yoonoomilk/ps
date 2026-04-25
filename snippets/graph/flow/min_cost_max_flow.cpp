template <typename flow_t = int, typename cost_t = int, cost_t cost_inf = cost_t(INT_MAX)>
struct min_cost_max_flow {
  struct edge {
    int loc, rev;
    flow_t left;
    cost_t cost;
  };

  const int sz;
  vector<vector<edge>> edges;

  min_cost_max_flow(int sz) : sz(sz), edges(sz) {}

  void add(int a, int b, flow_t cap, cost_t cost) {
    edges[a].emplace_back(b, edges[b].size(), cap, cost);
    edges[b].emplace_back(a, edges[a].size() - 1, 0, -cost);
  }

  auto operator() (int s, int e, flow_t limit = cost_inf) {
    flow_t flow{};
    cost_t cost{};
    while(1) {
      vector<cost_t> dist(sz, cost_inf);
      vector<int> idx(sz);
      vector<char> inq(sz);
      queue<int> q;
      dist[s] = 0;
      q.push(s);
      inq[s] = 1;
      while(q.size()) {
        int cur = q.front();
        q.pop();
        inq[cur] = 0;
        for(auto [loc, rev, left, cost] : edges[cur]) if(left && dist[loc] > dist[cur] + cost) {
          dist[loc] = dist[cur] + cost;
          if(!inq[loc]) q.push(loc);
          inq[loc] = 1;
        }
      }
      if(dist[e] == cost_inf) break;
      auto dfs = [&](auto& self, int cur, flow_t tmp) {
        q.push(cur);
        inq[cur] = 1;
        if(cur == e) return tmp;
        for(;idx[cur] < edges[cur].size();idx[cur]++) {
          auto& [loc, rev, left, cost] = edges[cur][idx[cur]];
          if(!inq[loc] && left && dist[loc] == dist[cur] + cost) {
            flow_t nxt = self(self, loc, min(tmp, left));
            if(nxt) {
              left -= nxt;
              edges[loc][rev].left += nxt;
              return nxt;
            }
          }
        }
        return flow_t();
      };
      for(flow_t i;i = dfs(dfs, s, limit);) {
        flow += i;
        cost += dist[e] * i;
        for(;q.size();q.pop()) inq[q.front()] = 0;
      };
    }
    return pair{flow, cost};
  }
};