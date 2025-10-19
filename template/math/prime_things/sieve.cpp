// segmented sieve
template <ll n, int chunk>
class sieve {
  bitset<chunk> is_prime;
  vector<int> pre_primes, add_primes;
  vector<ll> primes = {2};

public:
  sieve() {
    int sq = sqrt(n), pre = ((ll)sq * sq == n ? sq : sq + 1);
    is_prime.set();
    for(ll i = 2;i < pre;i++) if(is_prime[i]) {
      pre_primes.push_back(i);
      add_primes.push_back(i * 3);
      for(ll j = i * i;j < pre;j += i) is_prime[j] = false;
    }
    for(ll i = 0;i <= n;i += chunk) {
      is_prime.set();
      is_prime[1] = i != 0;
      for(int j = 1;j < pre_primes.size();j++) {
        for(;add_primes[j] < chunk;add_primes[j] += pre_primes[j] * 2) is_prime[add_primes[j]] = false;
        add_primes[j] -= chunk;
      }
      for(int j = 1;j < chunk;j += 2) {
        if(i + j > n) break;
        if(is_prime[j]) primes.push_back(i + j);
      }
    }
  }

  auto begin() { return primes.cbegin(); }
  auto end() { return primes.cend(); }
  ll operator[] (int i) { return primes[i - 1]; }
  bool operator() (ll i) { return binary_search(primes.begin(), primes.end(), i); }
  int count() {return primes.size(); }
};

// linear sieve
// https://github.com/justiceHui/icpc-teamnote/blob/master/code/Math/LinearSieve.cpp