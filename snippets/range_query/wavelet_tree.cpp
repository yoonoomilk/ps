class wavelet_tree {
  const int sz, lg;
  vector<int> raw;
  vector<vector<int>> arr;
  vector<int> sum;

public:
  wavelet_tree(int n) : sz(n + 1), lg(__lg(sz * 2 - 1)), raw(sz), arr(lg, vector<int>(sz)), sum(lg, 0) {}

  void set(int i, int v) {
    raw[i] = v;
  }

  void init() {
    vector<int> tmp[2] = {raw, vector<int>(sz)};
    raw.erase(raw.begin());
    sort(raw.begin(), raw.end());
    raw.erase(unique(raw.begin(), raw.end()), raw.end());
    for(int i = 1;i < sz;i++) tmp[0][i] = lower_bound(raw.begin(), raw.end(), tmp[0][i]) - raw.begin();

    for(int d = lg, t = 0;d--;t ^= 1) {
      arr[d][0] = 0;
      for(int i = 1;i < sz;i++) {
        int bit = (tmp[t][i] >> d) & 1;
        arr[d][i] = arr[d][i - 1] + (bit == 0);
      }
      sum[d] = arr[d][sz - 1];
      int idx[2] = {1, arr[d][sz - 1] + 1};
      for(int i = 1;i < sz;i++) tmp[t ^ 1][idx[(tmp[t][i] >> d) & 1]++] = tmp[t][i];
    }
  }

  int kth(int l, int r, int k) {
    int s = 0;
    for(int d = lg;d--;) {
      int cnt = arr[d][r] - arr[d][l - 1];
      if(k <= cnt) {
        l = arr[d][l - 1] + 1;
        r = arr[d][r];
      } else {
        k -= cnt;
        l += sum[d] - arr[d][l - 1];
        r += sum[d] - arr[d][r];
        s |= 1 << d;
      }
    }
    return raw[s];
  }

  int leq(int l, int r, int v) {
    v = upper_bound(raw.begin(), raw.end(), v) - raw.begin();
    if(v == raw.size()) return r - l + 1;
    int s = 0;
    for(int d = lg;d--;) {
      int cnt = arr[d][r] - arr[d][l - 1];
      if(~(v >> d) & 1) {
        l = arr[d][l - 1] + 1;
        r = arr[d][r];
      } else {
        s += cnt;
        l += sum[d] - arr[d][l - 1];
        r += sum[d] - arr[d][r];
      }
    }
    return s;
  }

  int count(int l, int r, int v) {
    return leq(l, r, v) - leq(l, r, v - 1);
  }
};