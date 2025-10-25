template <int sz, int mod>
class combination {
  int fact[sz + 1], inv[sz + 1];

  static constexpr int _pow(ll n, int exp) {
    ll tmp = 1;
    for(;exp;exp /= 2) {
      if (exp & 1) tmp = tmp * n % mod;
      n = (n * n) % mod;
    }
    return tmp;
  }

public:
  constexpr combination() {
    fact[0] = 1;
    for(int i = 1;i <= sz;i++) fact[i] = (ll)fact[i - 1] * i % mod;
    inv[sz] = _pow(fact[sz], mod - 2);
    for(int i = sz;i;i--) inv[i - 1] = (ll)inv[i] * i % mod;
  }

  ll operator() (int n, int r) const {
    return (ll)fact[n] * inv[r] % mod * inv[n - r] % mod;
  }
};