using base = complex<double>;

void fft(vector<base>& v, bool inv = false) {
  int sz = v.size();
  assert((sz & (sz - 1)) == 0);
  for(int i = 1, j = 0;i < sz;i++) {
    int bit = sz / 2;
    for(;j >= bit;bit /= 2) j -= bit;
    j += bit;
    if(i < j) swap(v[i], v[j]);
  }
  for(int k = 1;k < sz;k *= 2) {
    double angle = numbers::pi / k * (inv ? 1 : -1);
    base w(cos(angle), sin(angle));
    for(int i = 0;i < sz;i += k * 2) {
      base z(1, 0);
      for(int j = 0;j < k;j++) {
        base even = v[i + j], odd = v[i + j + k];
        v[i + j] = even + z * odd;
        v[i + j + k] = even - z * odd;
        z *= w;
      }
    }
  }
  if(inv) for(auto& i : v) i /= sz;
}

vector<base> mul(vector<base> a, vector<base> b) {
  int sz = bit_ceil(a.size() + b.size());
  a.resize(sz); fft(a);
  b.resize(sz); fft(b);
  for(int i = 0;i < sz;i++) a[i] *= b[i];
  fft(a, true);
  return a;
}