// 뭔가 잘못 구현된 듯
class bit_match {
  const int l, r;
  vector<vector<int>> edges;

public:
  bit_match(int l, int r) : l(l), r(r), edges(l) {}

  void add(int a, int b) {
    edges[a].push_back(b);
  }

  int operator() () {
    int ret = 0;
    vector<int> idx_l(l, -1), idx_r(r, -1);
    while(1) {
      vector<int> level(l, -1);
      queue<int> q;
      for(int i = 0;i < l;i++) if(idx_l[i] == -1) {
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
      function<bool(int)> dfs = [&](int cur) {
        for(int i : edges[cur]) if(idx_r[i] == -1 || level[idx_r[i]] == level[cur] + 1 && dfs(idx_r[i])) {
          idx_l[cur] = i;
          idx_r[i] = cur;
          return true;
        }
        return false;
      };
      for(int i = 0;i < l;i++) if(idx_l[i] == -1 && dfs(i)) ret++;
    }
    return ret;
  }
};