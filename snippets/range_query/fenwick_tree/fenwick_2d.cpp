template <typename T>
class fenwick_2d {
  const int n, m;
  vector<vector<T>> tree;

public:
  fenwick_2d(int n, int m) : n(n), m(m), tree(n + 1, vector<T>(m + 1)) {}

  void update(int i, int jj, T v) {
    for(;i <= n;i += i & -i) for(int j = jj;j <= m;j += j & -j) tree[i][j] += v;
  }

  T operator() (int i, int jj) {
    T s = 0;
    for(;i;i -= i & -i) for(int j = jj;j;j -= j & -j) s += tree[i][j];
    return s;
  }
  T operator() (int x1, int y1, int x2, int y2) {
    return (*this)(x2, y2) - (*this)(x2, y1 - 1) - (*this)(x1 - 1, y2) + (*this)(x1 - 1, y1 - 1);
  }
};