class strongly_connected_component {
  const int sz;
  vector<vector<int>> edges;
  vector<int> idx;

public:
  vector<vector<int>> scc, dag;

  strongly_connected_component(int n) : sz(n + 1), edges(sz), idx(sz, -1) {}

  void add(int a, int b) {
    edges[a].push_back(b);
  }

  void init() {
    vector<int> pa(sz, -1);
    vector<bool> finished(sz);
    stack<int> st;
    int cnt = 0;
    auto dfs = [&](auto&& self, int cur) -> int {
      st.push(cur);
      int bef = pa[cur] = ++cnt;
      for(int i : edges[cur]) {
        if(pa[i] == -1) bef = min(bef, self(self, i));
        else if(!finished[i]) bef = min(bef, pa[i]);
      }
      if(bef == pa[cur]) {
        scc.push_back({});
        while(1) {
          int i = st.top();
          st.pop();
          scc.back().push_back(i);
          finished[i] = true;
          idx[i] = scc.size() - 1;
          if(cur == i) break;
        }
        sort(scc.back().begin(), scc.back().end());
      }
      return bef;
    };
    for(int i = 1;i < sz;i++) if(pa[i] == -1) dfs(dfs, i);
    dag.resize(scc.size());
    for(int i = 1;i < sz;i++) for(int j : edges[i]) if(idx[i] != idx[j]) dag[idx[i]].push_back(idx[j]);
    for(auto& i : dag) {
      sort(i.begin(), i.end());
      i.erase(unique(i.begin(), i.end()), i.end());
    }
  }

  int operator[] (int i) { return idx[i]; }
};