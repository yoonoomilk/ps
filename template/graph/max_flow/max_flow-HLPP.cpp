class max_flow {
  struct edge {
    int loc, cap, flow, rev;
  };

  const int sz;
  vector<vector<edge>> edges;
  vector<stack<int>> level_list;
  vector<int> excess, level;

  void apply(edge& e, int flow) {
    edge& rev = edges[e.loc][e.rev];
    if (!excess[e.loc] && flow) level_list[level[e.loc]].push(e.loc);
    e.flow += flow;
    e.cap -= flow;
    excess[e.loc] += flow;
    rev.flow -= flow;
    rev.cap += flow;
    excess[rev.loc] -= flow;
  }

public:
  max_flow(int n) : sz(n), edges(sz), excess(sz), level(sz), level_list(sz * 2) {}

  void add(int a, int b, int cap, bool directed = true) {
    edges[a].emplace_back(b, cap, 0, edges[b].size());
    edges[b].emplace_back(a, directed ? 0 : cap, 0, edges[a].size() - 1);
  }

  int operator() (int s, int e) {
    vector<int> cnt(sz * 2);
    vector<edge*> ptr(sz);
    level[s] = sz;
    excess[e] = 1;
    cnt[0] = sz - 1;
    for(int i = 0;i < sz;i++) ptr[i] = edges[i].data();
    for(edge& i : edges[s]) apply(i, i.cap);
    for(int top = 0;;) {
      while(level_list[top].empty()) if(!top--) return -excess[s];
      int cur = level_list[top].top();
      level_list[top].pop();
      while(excess[cur] > 0) {
        if(ptr[cur] == edges[cur].data() + edges[cur].size()) {
          level[cur] = INT_MAX;
          for(edge& i : edges[cur]) if(i.cap && level[cur] > level[i.loc] + 1) {
            level[cur] = level[i.loc] + 1;
            ptr[cur] = &i;
          }
          cnt[level[cur]]++;
          cnt[top]--;
          if(!cnt[top] && top < sz) for(int i = 0;i < sz;i++) if(top < level[i] && level[i] < sz) {
            cnt[level[i]]--;
            level[i] = sz + 1;
          }
          top = level[cur];
        } else if(ptr[cur]->cap && level[cur] == level[ptr[cur]->loc] + 1) apply(*ptr[cur], min(excess[cur], ptr[cur]->cap));
        else ptr[cur]++;
      }
    }
  }

  bool blocked(int a) {
    return level[a] >= sz;
  }
};