class bit_match {
  const int n, m;
  vector<vector<int>> edges;

public:
  bit_match(int l, int r) : n(l), m(r), edges(l) {}

  void add(int a, int b) {
    edges[a].push_back(b);
  }

  int operator() () {
    int ret = 0;
    vector<int> idx_l(n, -1), idx_r(m, -1);
    while(1) {
      vector<int> level(n, -1), idx(n, 0);
      queue<int> q;
      for(int i = 0;i < n;i++) if(idx_l[i] == -1) {
        level[i] = 0;
        q.push(i);
      }
      bool flag = false;
      while(q.size()) {
        int cur = q.front();
        q.pop();
        for(int i : edges[cur]) {
          if(idx_r[i] == -1) flag = true;
          else if(level[idx_r[i]] == -1) {
            level[idx_r[i]] = level[cur] + 1;
            q.push(idx_r[i]);
          }
        }
      }
      if(!flag) break;
      auto dfs = [&](auto& self, int cur) -> bool {
        for(int& i = idx[cur];i < edges[cur].size();i++) {
          int j = edges[cur][i], &rr = idx_r[j];
          if(rr == -1 || (level[rr] == level[cur] + 1 && self(self, rr))) {
            idx_l[cur] = j;
            rr = cur;
            return true;
          }
        }
        level[cur] = -1;
        return false;
      };
      for(int i = 0;i < n;i++) if(idx_l[i] == -1 && dfs(dfs, i)) ret++;
    }
    return ret;
  }
};