struct fraction {
  ll n = 0, d = 1;
  fraction(ll a = 0, ll b = 1) : n(a), d(b) {
    ll g = gcd(n, d);
    n /= g;
    d /= g;
  }
  fraction operator+ (const fraction v) const { return fraction(n * v.d + d * v.n, d * v.d); }
  fraction operator- (const fraction v) const { return fraction(n * v.d - d * v.n, d * v.d); }
  fraction operator* (const fraction v) const { return fraction(n * v.n, d * v.d); }
  fraction operator/ (const fraction v) const { return fraction(n * v.d, d * v.n); }
  strong_ordering operator<=> (const fraction v) const { return n * v.d <=> d * v.n; }
  friend ostream& operator<< (ostream& cout, fraction& v) { return cout << v.n << '/'<< v.d; }
  friend ll floor(const fraction& v) const { return v.n / v.d; }
  friend ll ceil(const fraction& v) const { return v.n / v.d + (v.n % v.d != 0); }
  friend double round(const fraction& v) const { return (double)v.n / v.d; }
};