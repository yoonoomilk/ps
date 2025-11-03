class max_flow {
  const int sz;
  vector<vector<int>> edges, cap, flow;

public:
  max_flow(int sz) : sz(sz), edges(sz), cap(sz, vector<int>(sz)), flow(sz, vector<int>(sz)) {}

  void add(int a, int b, int v, bool directed = true) {
    edges[a].push_back(b);
    edges[b].push_back(a);
    cap[a][b] += v;
    if(!directed) cap[b][a] += v;
  }

  int operator() (int s, int e) {
    int ret = 0;
    while(1) {
      vector<int> level(sz, -1);
      level[s] = 0;
      queue<int> q;
      q.push(s);
      while(q.size()) {
        int cur = q.front();
        q.pop();
        for(int i : edges[cur]) if(cap[cur][i] > flow[cur][i] && level[i] == -1) {
          level[i] = level[cur] + 1;
          q.push(i);
        }
      }
      if(level[e] == -1) break;
      vector<int> idx(sz);
      auto dfs = [&](auto&& dfs, int cur, int tmp) {
        if(cur == e) return tmp;
        for(int& i = idx[cur];i < edges[cur].size();i++) {
          int j = edges[cur][i];
          if(level[cur] + 1 == level[j] && cap[cur][j] > flow[cur][j]) {
            int nxt = dfs(dfs, j, min(cap[cur][j] - flow[cur][j], tmp));
            if(nxt) {
              flow[cur][j] += nxt;
              flow[j][cur] -= nxt;
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