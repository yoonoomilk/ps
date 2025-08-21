class strongly_connected_component {
  const int sz;
  vector<vector<int>> edges, _scc, _dag;
  vector<int> idx;

public:
  strongly_connected_component(int n) : sz(n + 1), edges(sz), idx(sz, -1) {}

  void add(int a, int b) {
    edges[a].push_back(b);
  }

  void operator() () {
    vector<int> pa(sz, -1);
    vector<bool> finished(sz);
    stack<int> st;
    int cnt = 0;
    function<int(int)> dfs = [&](int cur) {
      st.push(cur);
      int bef = pa[cur] = ++cnt;
      for(int i : edges[cur]) {
        if(pa[i] == -1) bef = min(bef, dfs(i));
        else if(!finished[i]) bef = min(bef, pa[i]);
      }
      if(bef == pa[cur]) {
        _scc.push_back({});
        while(1) {
          int i = st.top();
          st.pop();
          _scc.back().push_back(i);
          finished[i] = true;
          idx[i] = _scc.size() - 1;
          if(cur == i) break;
        }
        sort(_scc.back().begin(), _scc.back().end());
      }
      return bef;
    };
    for(int i = 1;i < sz;i++) if(pa[i] == -1) dfs(i);
    _dag.resize(_scc.size());
    for(int i = 1;i < sz;i++) for(int j : edges[i]) if(idx[i] != idx[j]) _dag[idx[i]].push_back(idx[j]);
    for(auto& i : _dag) {
      sort(i.begin(), i.end());
      i.erase(unique(i.begin(), i.end()), i.end());
    }
  }

  const vector<vector<int>>& scc() { return _scc; }
  const vector<vector<int>>& dag() { return _dag; }
  int operator[] (int i) { return idx[i]; }
};