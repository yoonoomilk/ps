template <typename T, typename Merge>
class const_rmq {
  const int sz, lg;
  vector<vector<T>> arr;
  Merge op;

public:
  const_rmq(int n) : sz(n + 1), lg(__lg(sz)), arr(lg + 1, vector<T>(sz)) {}

  void set(int i, T v) {
    arr[0][i] = v;
  }
  void init() {
    for(int i = 1;i <= lg;i++) for(int j = 0;j + (1 << i - 1) < sz;j++) arr[i][j] = op(arr[i - 1][j], arr[i - 1][j + (1 << i - 1)]);
  }

  T operator() (int l, int r) {
    int d = r - l + 1, dd = __lg(d);
    int a = arr[dd][l], b = arr[dd][r - (1 << dd) + 1];
    return op(a, b);
  }
};