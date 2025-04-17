# 코드
```cpp
const double PI = acos(-1);
using base = complex<double>;

void FFT(vector<base> &v, bool inv) {
  for(int i = 1, j = 0;i < v.size();i++) {
    int bit = v.size() / 2;
    while(j >= bit) {
      j -= bit;
      bit /= 2;
    }
    j += bit;
    if(i < j) swap(v[i], v[j]);
  }
  for(int k = 1;k < v.size();k *= 2) {
    double angle = inv ? PI / k : -PI / k;
    base w(cos(angle), sin(angle));
    for(int i = 0;i < v.size();i += k*2) {
      base z(1, 0);
      for(int j = 0;j < k;j++) {
        base even = v[i+j], odd = v[i+j+k];
        v[i+j] = even + z * odd;
        v[i+j+k] = even - z * odd;
        z *= w;
      }
    }
  }

  if(inv) for(base &i : v) i /= v.size();
}

vector<base> mul(vector<base> a, vector<base> b) {
  int sz = 1;
  while(sz < a.size() + b.size()) sz *= 2;

  a.resize(sz); FFT(a, false);
  b.resize(sz); FFT(b, false);

  for(int i = 0;i < sz;i++) a[i] *= b[i];
  FFT(a, true);

  return a;
}
```

# 문제
* [큰 수 곱셈 (2)](https://boj.kr/15576)
  * http://boj.kr/
* [큰 수 곱셈 (3)](https://boj.kr/22289)
  * http://boj.kr/