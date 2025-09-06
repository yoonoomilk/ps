class union_find {
  const int sz;
  vector<int> pa;

public:
  union_find(int n) : sz(n + 1), pa(sz) {
    iota(pa.begin(), pa.end(), 0);
  }

  int find(int i) { return i == pa[i] ? i : pa[i] = find(pa[i]); }
  bool uni(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) return false;
    pa[b] = a;
    return true;
  }
};