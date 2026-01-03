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