class union_find {
  const int sz;
  vector<int> pa;

public:
  union_find(int n) : sz(n + 1), pa(sz) {
    iota(pa.begin(), pa.end(), 0);
  }

  int find(int i) { return i == pa[i] ? i : pa[i] = find(pa[i]); }
  bool merge(int a, int b) { return find(a) != find(b) && (pa[pa[a]] = pa[b], true); }
  bool same(int a, int b) { return find(a) == find(b); }
};