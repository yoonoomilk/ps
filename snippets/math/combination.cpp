#include "math/_pow-constant_mod.cpp"

template <int sz, int mod>
class combination {
  int fact[sz + 1], inv[sz + 1];

public:
  constexpr combination() {
    fact[0] = 1;
    for(int i = 1;i <= sz;i++) fact[i] = (ll)fact[i - 1] * i % mod;
    inv[sz] = _pow<mod>(fact[sz], mod - 2);
    for(int i = sz;i;i--) inv[i - 1] = (ll)inv[i] * i % mod;
  }

  ll operator() (int n, int r) const {
    return (ll)fact[n] * inv[r] % mod * inv[n - r] % mod;
  }
};