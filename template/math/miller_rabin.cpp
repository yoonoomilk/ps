ll _pow(__int128 n, ll exp, ll mod) {
  __int128 tmp = 1;
  for(n %= mod;exp;exp /= 2) {
    if(exp & 1) tmp = tmp * n % mod;
    n = (n * n) % mod;
  }
  return tmp;
}

bool miller_rabin(ll n) {
  if(n == 1) return false;
  if(n == 2) return true;
  for(ll a : {2, 7, 61}) if(a % n) {
    for(ll k = n - 1;;k /= 2) {
      ll tmp = _pow(a, k, n);
      if(tmp == n - 1) break;
      if(k % 2) {
        if(tmp == 1) break;
        else return false;
      }
    }
  }
  return true;
}

/*
n <= 2^32 -> {2, 7, 61}
n <= 2^64 -> {2, 325, 9375, 28178, 450775, 9780504, 1795265022}
*/