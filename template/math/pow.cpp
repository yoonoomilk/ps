int _pow(ll n, ll exp, int mod) {
  ll tmp = 1;
  for(;exp;exp /= 2) {
    if (exp & 1) tmp = tmp * n % mod;
    n = (n * n) % mod;
  }
  return tmp;
}