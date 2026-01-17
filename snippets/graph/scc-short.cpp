class strongly_connected_component {
  const int sz;
  vector<vector<int>> edges;
  vector<int> idx;
  int scc = 0;

public:
  strongly_connected_component(int n) : sz(n + 1), edges(sz), idx(sz, -1) {}

  void add(int a, int b) {
    edges[a].push_back(b);
  }

  void init() {
    vector<int> pa(sz, -1);
    vector<bool> finished(sz);
    stack<int> st;
    int cnt = 0;
    auto dfs = [&](auto& self, int cur) -> int {
      st.push(cur);
      int bef = pa[cur] = ++cnt;
      for(int i : edges[cur]) {
        if(pa[i] == -1) bef = min(bef, self(self, i));
        else if(!finished[i]) bef = min(bef, pa[i]);
      }
      if(bef == pa[cur]) {
        scc++;
        while(1) {
          int i = st.top();
          st.pop();
          finished[i] = true;
          idx[i] = scc - 1;
          if(cur == i) break;
        }
      }
      return bef;
    };
    for(int i = 1;i < sz;i++) if(pa[i] == -1) dfs(dfs, i);
  }

  int operator[] (int i) { return idx[i]; }
};