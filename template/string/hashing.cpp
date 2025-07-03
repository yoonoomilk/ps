template <int P, int M>
class hashing {
  const int sz;
  vector<int> h, b;

public:
  template <typename I>
  hashing(I s, I e) : sz(distance(s, e)), h(sz + 1), b(sz + 1) {
    b[0] = 1;
    for(int i = 1;i <= sz;i++) {
      b[i] = (ll)b[i - 1] * P % M;
      h[i] = (h[i - 1] + (ll)b[i - 1] * *s++) % M;
    }
  }
  ll operator() (int s, int e) {
    s++; e++;
    return (h[e] - (ll)h[s - 1] * b[e - s + 1] + M) % M;
  }
  ll operator() () {
    return (*this)(0, sz - 1);
  }
};