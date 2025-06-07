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
      vector<int> bef(sz, -1);
      queue<int> q;
      q.push(s);
      while(q.size() && bef[e] == -1) {
        int cur = q.front();
        q.pop();
        for(int i : edges[cur]) if(cap[cur][i] > flow[cur][i] && bef[i] == -1) {
          bef[i] = cur;
          q.push(i);
        }
      }
      if(bef[e] == -1) break;
      int tmp = 1e9;
      for(int i = e;i != s;i = bef[i]) tmp = min(tmp, cap[bef[i]][i] - flow[bef[i]][i]);
      for(int i = e;i != s;i = bef[i]) {
        flow[bef[i]][i] += tmp;
        flow[i][bef[i]] -= tmp;
      }
      ret += tmp;
    }
    return ret;
  }
};