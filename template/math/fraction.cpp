class fraction {
  ll n, d;
public:
  fraction(ll a = 0, ll b = 1) : n(a), d(b) {
    assert(d != 0);
    ll g = gcd(a, b);
    n /= g;
    d /= g;
  }

  fraction operator+ (fraction v) { return fraction(n * v.d + d * v.n, d * v.d); }
  fraction operator+= (fraction v) { return *this + v; }
  fraction operator- (fraction v) { return fraction(n * v.d - d * v.n, d * v.d); }
  fraction operator-= (fraction v) { return *this - v; }
  fraction operator* (fraction v) { return fraction(n * v.n, d * v.d); }
  fraction operator*= (fraction v) { return *this * v; }
  fraction operator/ (fraction v) { return fraction(n * v.d, d * v.n); }
  fraction operator/= (fraction v) { return *this / v; }
  fraction operator- () { return fraction(-n, d); }

  strong_ordering operator<=> (fraction v) { return n * v.d <=> d * v.n; }

  explicit operator bool() { return n != 0; }
  explicit operator double() { return (double)n / d; }

  friend ostream& operator<< (ostream& cout, fraction& v) { return cout << v.n << '/'<< v.d; }

  friend ll floor(fraction v) { return v.n / v.d - ((v.n % v.d != 0) && ((v.n < 0) != (v.d < 0))); }
  friend ll ceil(fraction v) { return v.n / v.d + ((v.n % v.d != 0) && ((v.n > 0) == (v.d > 0))); }
  friend ll round(fraction v) { return (v.n + v.d / 2 * ((v.n > 0) == (v.d > 0))) / v.d; }
  friend fraction abs(fraction v) { return fraction(abs(v.n), abs(v.d)); }

  friend struct formatter<fraction>;
};

namespace std {
  template <>
  struct formatter<fraction> : formatter<string_view> {
    auto format(fraction f, auto& ctx) {
      return formatter<string_view>::format(
        string_view(to_string(f.n) + "/" + to_string(f.d)),
        ctx
      );
    }
  };
}