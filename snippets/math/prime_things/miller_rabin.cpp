bool miller_rabin(ll n) {
  if(n == 1) return false;
  if(n == 2) return true;
  for(ll a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) if(a % n) {
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