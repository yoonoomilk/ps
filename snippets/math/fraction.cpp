class fraction {
  ll n, d;
public:
  fraction(ll a = 0, ll b = 1) : n(a / gcd(a, b)), d(b / gcd(a, b)) {}
  fraction operator+ (const fraction v) const { return fraction(n * v.d + d * v.n, d * v.d); }
  fraction operator+= (const fraction v) { return *this = *this + v; }
  fraction operator- (const fraction v) const { return fraction(n * v.d - d * v.n, d * v.d); }
  fraction operator-= (const fraction v) { return *this = *this - v; }
  fraction operator* (const fraction v) const { return fraction(n * v.n, d * v.d); }
  fraction operator*= (const fraction v) { return *this = *this * v; }
  fraction operator/ (const fraction v) const { return fraction(n * v.d, d * v.n); }
  fraction operator/= (const fraction v) { return *this = *this / v; }
  fraction operator- () const { return fraction(-n, d); }

  auto operator<=> (fraction v) { return n * v.d <=> d * v.n; }

  explicit operator bool() { return n != 0; }
  explicit operator double() { return (double)n / d; }

  friend istream& operator>> (istream& cin, fraction& v) {
    v.d = 1;
    return cin >> v.n;
  }
  friend ostream& operator<< (ostream& cout, fraction& v) { return cout << v.n << '/' << v.d; }

  friend ll floor(fraction v) { return v.n / v.d - ((v.n % v.d != 0) && ((v.n < 0) != (v.d < 0))); }
  friend ll ceil(fraction v) { return v.n / v.d + ((v.n % v.d != 0) && ((v.n > 0) == (v.d > 0))); }
  friend ll round(fraction v) { return (v.n + v.d / 2 * ((v.n > 0) == (v.d > 0))) / v.d; }
  friend fraction abs(fraction v) { return fraction(abs(v.n), abs(v.d)); }
};