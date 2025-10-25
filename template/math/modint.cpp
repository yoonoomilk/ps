template <int mod>
class _modint {
  ll val;

public:
  _modint(ll n = 0) : val((n %= mod) < 0 ? n + mod : n) {}

  _modint operator+ (const _modint v) { return _modint(val + v.val); }
  _modint operator- (const _modint v) { return _modint(val - v.val); }
  _modint operator* (const _modint v) { return _modint(val * v.val); }
  _modint operator/ (const _modint v) { return _modint(val * _pow(v.val, mod - 2)); }
  _modint operator- () { return _modint(val ? mod - val : val); }

  friend istream& operator>> (istream& cin, _modint& v) {
    cin >> v.val;
    if((v.val %= mod) < 0) v.val += mod;
    return cin;
  }
  friend ostream& operator<< (ostream& cout, const _modint v) { return cout << v.val; }
};
using modint = _modint<mod>