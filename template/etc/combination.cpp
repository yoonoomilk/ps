template <int sz>
class combination {
  const int MOD = 1e9 + 7;
  int fact[sz + 1], inv[sz + 1];

  int _pow(int n, int exp) {
    ll tmp = 1;
    for(ll i = n;exp;exp /= 2) {
      if(exp & 1) tmp = tmp * i % MOD;
      i = i * i % MOD;
    }
    return tmp;
  }

public:
  combination() {
    fact[0] = 1;
    for(int i = 1;i <= sz;i++) fact[i] = (ll)fact[i - 1] * i % MOD;
    inv[sz] = _pow(fact[sz], MOD - 2);
    for(int i = sz;i;i--) inv[i - 1] = (ll)inv[i] * i % MOD;
  }

  int operator() (int n, int r) {
    return (ll)fact[n] * inv[r] % MOD * inv[n - r] % MOD;
  }
};