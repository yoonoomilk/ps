struct rational {
  ll n = 0, d = 1;
  rational(ll a = 0, ll b = 1) : n(a), d(b) {
    ll g = gcd(n, d);
    n /= g;
    d /= g;
  }
  rational operator+ (const rational v) const { return rational(n * v.d + d * v.n, d * v.d); }
  rational operator- (const rational v) const { return rational(n * v.d - d * v.n, d * v.d); }
  rational operator* (const rational v) const { return rational(n * v.n, d * v.d); }
  rational operator/ (const rational v) const { return rational(n * v.d, d * v.n); }
  double near() const { return (double)n / d; }
  double floor() const { return n / d; }
  double ceil() const { return n / d + (n % d != 0); }
  bool operator== (const rational v) const { return n == v.n && d == v.d; }
  bool operator< (const rational v) const { return n * v.d < d * v.n; }
};