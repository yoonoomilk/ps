class combination {
  const int sz, MOD = 1e9 + 7;
  vector<int> fact, inv;

  int _pow(ll n, int exp) {
    ll tmp = 1;
    while(exp) {
      if(exp & 1) tmp = tmp * n % MOD;
      n = n * n % MOD;
      exp /= 2;
    }
    return tmp;
  }

public:
  combination(int sz) : sz(sz), fact(sz + 1), inv(sz + 1) {
    fact[0] = 1;
    for(int i = 1;i <= sz;i++) fact[i] = ((ll)fact[i - 1] * i) % MOD;
    inv[sz] = _pow(fact[sz], MOD - 2);
    for(int i = sz;i;i--) inv[i - 1] = ((ll)inv[i] * i) % MOD;
  }

  int operator() (int n, int r) {
    return (ll)fact[n] * inv[r] % MOD * inv[n - r] % MOD;
  }
};