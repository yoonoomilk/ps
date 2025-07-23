template <int n>
class sieve {
  bitset<n / 2> not_prime;

public:
  vector<int> primes = {2};

  seive() {
    for(ll i = 3;i <= n;i += 2) if(!not_prime[i]) {
      primes.push_back(i);
      for(ll j = i * i;j <= n;j += i * 2) not_prime[j] = true;
    }
  }

  bool operator() (int i) {
    return i != 2 && i % 2 && !not_prime[i / 2];
  }
};