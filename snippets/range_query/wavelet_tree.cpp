class wavelet_tree {
  const int sz, lg;
  vector<int> raw;
  vector<vector<int>> pre;
  vector<int> zero;

public:
  wavelet_tree(int n) : sz(n + 1), lg(__lg(sz * 2 - 1)), raw(sz) {}

  void set(int i,int v) {
    raw[i] = v;
  }

  void init() {
    vector<int> arr[2] = {raw, vector<int>(sz)};
    raw.erase(raw.begin());
    sort(raw.begin(), raw.end());
    raw.erase(unique(raw.begin(), raw.end()), raw.end());
    for(int i = 1;i < sz;i++) arr[0][i] = lower_bound(raw.begin(), raw.end(), arr[0][i]) - raw.begin();

    pre.assign(lg, vector<int>(sz));
    zero.assign(lg, 0);

    for(int d = lg, t = 0;d--;t ^= 1) {
      pre[d][0] = 0;
      for(int i = 1;i < sz;i++) {
        int bit = (arr[t][i] >> d) & 1;
        pre[d][i] = pre[d][i - 1] + (bit == 0);
      }
      zero[d] = pre[d][sz - 1];
      int idx[2] = {1, zero[d] + 1};
      for(int i = 1;i < sz;i++) {
        int bit = (arr[t][i] >> d) & 1;
        if(bit == 0) arr[t ^ 1][idx[0]++] = arr[t][i];
        else arr[t ^ 1][idx[1]++] = arr[t][i];
      }
    }
  }

  int kth(int l, int r, int k) {
    int s = 0;
    for(int d = lg;d--;) {
      int cnt = pre[d][r] - pre[d][l - 1];
      if(k <= cnt) {
        l = pre[d][l - 1] + 1;
        r = pre[d][r];
      } else {
        k -= cnt;
        l += zero[d] - pre[d][l - 1];
        r += zero[d] - pre[d][r];
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
      int cnt = pre[d][r] - pre[d][l - 1];
      if(~(v >> d) & 1) {
        l = pre[d][l - 1] + 1;
        r = pre[d][r];
      } else {
        s += cnt;
        l += zero[d] - pre[d][l - 1];
        r += zero[d] - pre[d][r];
      }
    }
    return s;
  }

  int count(int l, int r, int v) {
    return leq(l, r, v) - leq(l, r, v - 1);
  }
};