template <typename T, typename Merge>
class const_rmq {
  const int sz, lg;
  vector<vector<T>> arr;
  Merge op;

public:
  template <typename I>
  const_rmq(I s, I e) : sz(distance(s, e)), lg(__lg(sz)), arr(lg + 1, vector<T>(sz)) {
    for(int i = 0;s != e;i++) arr[0][i] = *s++;
    for(int i = 1;i <= lg;i++) for(int j = 0;j + (1 << i - 1) < sz;j++) arr[i][j] = op(arr[i - 1][j], arr[i - 1][j + (1 << i - 1)]);
  }
  T query(int l, int r) {
    int d = r - l + 1, dd = __lg(d);
    int a = arr[dd][l], b = arr[dd][r - (1 << dd) + 1];
    return op(a, b);
  }
};