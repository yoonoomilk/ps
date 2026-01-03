class union_find {
  const int sz;
  vector<int> pa;

public:
  union_find(int n) : sz(n + 1), pa(sz, -1) {}

  int find(int i) { return pa[i] < 0 ? i : pa[i] = find(pa[i]); }
  bool merge(int a, int b) {
    a = find(a), b = find(b);
    if(a == b) return false;
    pa[a] += pa[b];
    pa[b] = a;
    return true;
  }
  bool same(int a, int b) { return find(a) == find(b); }
  int size(int i) { return -pa[find(i)]; }
};