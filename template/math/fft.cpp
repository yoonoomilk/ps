using base = complex<double>;

template<typename I>
requires same_as<typename iterator_traits<I>::value_type, base>
void fft(I s, I e, bool inv = false) {
  int sz = distance(s, e);
  for(int i = 1, j = 0;i < sz;i++) {
    int bit = sz / 2;
    while(j >= bit) {
      j -= bit;
      bit /= 2;
    }
    j += bit;
    if(i < j) swap(s[i], s[j]);
  }
  for(int k = 1;k < sz;k *= 2) {
    double angle = inv ? numbers::pi / k : -numbers::pi / k;
    base w(cos(angle), sin(angle));
    for(int i = 0;i < sz;i += k * 2) {
      base z(1, 0);
      for(int j = 0;j < k;j++) {
        base even = s[i + j], odd = s[i + j + k];
        s[i + j] = even + z * odd;
        s[i + j + k] = even - z * odd;
        z *= w;
      }
    }
  }
  if(inv) while(s != e) *s++ /= sz;
}

vector<base> mul(vector<base> a, vector<base> b) {
  int sz = 1;
  while(sz < a.size() + b.size()) sz *= 2;

  a.resize(sz); fft(a.begin(), a.end());
  b.resize(sz); fft(b.begin(), b.end());

  for(int i = 0;i < sz;i++) a[i] *= b[i];
  fft(a.begin(), a.end(), true);

  return a;
}