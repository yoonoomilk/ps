ll _pow(__int128 n, ll exp, ll mod) {
  __int128 tmp = 1;
  for(n %= mod;exp;exp /= 2) {
    if(exp & 1) tmp = tmp * n % mod;
    n = (n * n) % mod;
  }
  return tmp;
}