template <int P, int M>
class hashing {
  const int sz;
  vector<int> arr, _pow;

public:
  template <typename I>
  hashing(I s, I e) : sz(distance(s, e)), arr(sz + 1), _pow(sz + 1) {
    _pow[0] = 1;
    for(int i = 1;i <= sz;i++) {
      arr[i] = ((ll)arr[i - 1] * P + *s++) % M;
      _pow[i] = (ll)_pow[i - 1] * P % M;
    }
  }
  ll operator() (int s, int e) {
    s++; e++;
    return ((arr[e] - (ll)arr[s - 1] * _pow[e - s + 1]) % M + M) % M;
  }
};