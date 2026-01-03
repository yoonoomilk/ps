template <typename T, typename Merge>
class segment_tree_2d {
  const int sz;
  const T raw;
  vector<vector<T>> tree;
  Merge op;

  T query(int x, int y1, int y2) {
    T s = raw;
    for(;y1 <= y2;y1 /= 2, y2 /= 2) {
      if(y1 & 1) s = op(s, tree[x][y1++]);
      if(~y2 & 1) s = op(s, tree[x][y2--]);
    }
    return s;
  }

public:
  segment_tree_2d(int n, T raw = T()) : sz(1 << __lg(n * 2 - 1)), raw(raw), tree(sz * 2, vector<T>(raw)) {}

  void set(int i, int j, T v) {
    tree[i + sz][j + sz] = v;
  }
  void init() {
    for(int i = sz;i < sz * 2;i++) for(int j = sz;--j;) tree[i][j] = op(tree[i][j * 2], tree[i][j * 2 + 1]);
    for(int i = sz;--i;) for(int j = 1;j < sz * 2;j++) tree[i][j] = op(tree[i * 2][j], tree[i * 2 + 1][j]);
  }

  void update(int i, int jj, T v) {
    i += sz; jj += sz;
    tree[i][jj] = v;
    for(int j = jj;j /= 2;) tree[i][j] = op(tree[i][j * 2], tree[i][j * 2 + 1]);
    while(i /= 2) for(int j = jj;j;j /= 2) tree[i][j] = op(tree[i * 2][j], tree[i * 2 + 1][j]);
  }

  T operator() (int x1, int y1, int x2, int y2) {
    x1 += sz; y1 += sz; x2 += sz; y2 += sz;
    T s = raw;
    for(;x1 <= x2;x1 /= 2, x2 /= 2) {
      if(x1 & 1) s = op(s, query(x1++, y1, y2));
      if(~x2 & 1) s = op(s, query(x2--, y1, y2));
    }
    return s;
  }
};