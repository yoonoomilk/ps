class two_sat {
  const int sz;
  strongly_connected_component scc;
  vector<char> ans;

public:
  two_sat(int n) : sz(n + 1), scc(sz * 2 + 1), ans(sz * 2 + 1, -1) {}

  void add(int a, int b) {
    if(a > 0) a = a * 2;
    else a = -a * 2 + 1;
    if(b > 0) b = b * 2;
    else b = -b * 2 + 1;
    scc.add(a ^ 1, b);
    scc.add(b ^ 1, a);
  }

  bool operator() () {
    bool flag = true;
    scc.init();
    for(int i = 1;i < sz && flag;i++) flag &= scc[i * 2] != scc[i * 2 + 1];
    if(flag) {
      vector<pair<int, int>> arr(sz * 2 - 2);
      for(int i = 1;i < sz;i++) {
        arr[i * 2 - 2] = {scc[i * 2], i * 2};
        arr[i * 2 - 1] = {scc[i * 2 + 1], i * 2 + 1};
      }
      sort(arr.rbegin(), arr.rend());
      for(auto [_, a] : arr) if(ans[a] == -1) {
        ans[a] = 0;
        ans[a ^ 1] = 1;
      }
    }
    return flag;
  }

  bool operator[] (int i) { return ans[i * 2]; }
};

//short ver
class two_sat {
  const int sz;
  strongly_connected_component scc;

public:
  two_sat(int n) : sz(n + 1), scc(sz * 2 + 1) {}

  void add(int a, int b) {
    if(a > 0) a = a * 2;
    else a = -a * 2 + 1;
    if(b > 0) b = b * 2;
    else b = -b * 2 + 1;
    scc.add(a ^ 1, b);
    scc.add(b ^ 1, a);
  }

  bool operator() () {
    bool flag = true;
    scc.init();
    for(int i = 1;i < sz && flag;i++) flag &= scc[i * 2] != scc[i * 2 + 1];
    return flag;
  }
};