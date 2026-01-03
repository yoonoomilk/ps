template <typename T>
class weighted_union_find {
  const int sz;
  vector<int> pa;
  vector<T> weight;

public:
  weighted_union_find(int n) : sz(n + 1), pa(sz, -1), weight(sz) {}

  int find(int i) {
    if(pa[i] < 0) return i;
    int bef = pa[i];
    pa[i] = find(pa[i]);
    weight[i] += weight[bef];
    return pa[i];
  }
  bool merge(int a, int b, T w = T()) {
    if(find(a) == find(b)) return false;
    w += weight[a] - weight[b];
    a = find(a), b = find(b);
    if(-pa[a] < -pa[b]) {
      swap(a, b);
      w = -w;
    }
    pa[a] += pa[b];
    pa[b] = a;
    weight[b] = w;
    return true;
  }
  bool same(int a, int b) { return find(a) == find(b); }
  auto diff(int a, int b) { return pair{same(a, b), weight[b] - weight[a]}; }
  int size(int i) { return -pa[find(i)]; }
};