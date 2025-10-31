template <int mod>
class _modint {
  ll val;

public:
  _modint(ll n = 0) : val((n %= mod) < 0 ? n + mod : n) {}
  _modint(_modint v) : val(v.val) {}
  _modint operator+ (const _modint v) const { return _modint(val + v.val); }
  _modint operator+= (const _modint v) { return *this = _modint(val + v.val); }
  _modint operator- (const _modint v) const { return _modint(val - v.val); }
  _modint operator-= (const _modint v) { return *this = _modint(val - v.val); }
  _modint operator* (const _modint v) const { return _modint(val * v.val); }
  _modint operator*= (const _modint v) { return *this = _modint(val * v.val); }
  _modint operator/ (const _modint v) const { return _modint(val * _pow<mod>(v.val, mod - 2)); }
  _modint operator/= (const _modint v) { return *this = _modint(val * _pow<mod>(v.val, mod - 2)); }
  _modint operator- () { return _modint(-val); }

  friend istream& operator>> (istream& cin, _modint& v) {
    ll a; cin >> a;
    v = _modint(a);
    return cin;
  }
  friend ostream& operator<< (ostream& cout, _modint v) { return cout << v.val; }
};
using modint = _modint<mod>;