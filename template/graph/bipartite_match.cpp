#include <bits/stdc++.h>
using namespace std;

class bipartite_match {
  const int l, r;
  vector<vector<int>> edges;

public:
  bipartite_match(int l, int r) : l(l), r(r), edges(l) {}

  void add(int a, int b) {
    edges[a].push_back(b);
  }

  int operator() () {
    int ret = 0;
    vector<bool> visited(l);
    vector<int> idx(r, -1);
    function<bool(int)> dfs = [&](int cur) {
      visited[cur] = true;
      for(int i : edges[cur]) if(idx[i] == -1) {
        idx[i] = cur;
        return true;
      }
      for(int i : edges[cur]) if(idx[i] != -1 && !visited[idx[i]] && dfs(idx[i])) {
        idx[i] = cur;
        return true;
      }
      return false;
    };
    for(int i = 0;i < l;i++) {
      visited.assign(l, 0);
      ret += dfs(i);
    }
    return ret;
  }
};

int n, m;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n >> m;
  bipartite_match bipartite(n + 1, m + 1);
  for(int i = 1;i <= n;i++) {
    int a, b;
    cin >> a;
    while(a--) {
      cin >> b;
      bipartite.add(i, b);
    }
  }

  cout << bipartite();

  return 0;
}