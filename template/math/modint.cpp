using ll = long long;

template <int mod = 1'000'000'007>
class modint {
  ll val;

  modint _pow(ll exp) const {
    ll n = val, tmp = 1;
    for(;exp;exp /= 2) {
      if (exp & 1) tmp = tmp * n % mod;
      n = (n * n) % mod;
    }
    return modint(tmp);
  }

  modint _inv() const {
    return _pow(mod - 2);
  }

public:
  modint(ll n = 0) : val((n %= mod) < 0 ? n + mod : n) {}

  modint operator+ (const modint v) {
    int tmp = val + v.val;
    if(tmp >= mod) tmp -= mod;
    return modint(tmp);
  }
  modint operator- (const modint v) {
    int tmp = val + mod - v.val;
    if(tmp >= mod) tmp -= mod;
    return modint(tmp);
  }
  modint operator* (const modint v) { return modint(val * v.val % mod); }
  modint operator/ (const modint v) { return *this * v._inv(); }
  modint operator- () { return modint(val ? mod - val : val); }

  bool operator! () { return val == 0; }
  explicit operator bool() { return val != 0; }

  friend istream& operator>> (istream& cin, modint& v) {
    cin >> v.val;
    if((v.val %= mod) < 0) v.val += mod;
    return cin;
  }
  friend ostream& operator<< (ostream& cout, const modint v) {
    cout << v.val;
    return cout;
  }
};

template <int mod = 1'000'000'007>
modint<mod> comb(int n, int r) {
  if(r > n - r) r = n - r;
  modint<mod> x = 1, y = 1;
  for(int i = 0;i < r;i++) {
    x = x * (n - i);
    y = y * (i + 1);
  }
  return x / y;
}