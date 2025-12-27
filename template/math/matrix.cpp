template <typename T, int N, int M>
struct matrix : array<array<T, M>, N> {
  using super = array<array<T, M>, N>;

  matrix() {
    for(int i = 0;i < N;i++) super::operator[](i).fill(T());
  }

  matrix<T, N, M> operator+ (matrix<T, N, M>& v) {
    matrix<T, N, M> tmp;
    for(int i = 0;i < N;i++) for(int j = 0;j < M;j++) {
      tmp[i][j] = (super::operator[](i)[j] + v[i][j]) % MOD;
    }
    return tmp;
  }

  template <int K>
  matrix<T, N, K> operator* (matrix<T, M, K>& v) {
    matrix<T, N, K> tmp;
    for(int i = 0;i < N;i++) for(int j = 0;j < K;j++) for(int k = 0;k < M;k++) {
      tmp[i][j] += super::operator[](i)[k] * v[k][j];
    }
    return tmp;
  }
};

template <typename T, int N>
matrix<T, N, N> pow(matrix<T, N, N> v, ll exp) {
  matrix<T, N, N> tmp = v;
  for(exp--;exp;exp /= 2) {
    if(exp & 1) tmp = tmp * v;
    v = v * v;
  }
  return tmp;
}

// f(n) = x * f(n - 1) + y * f(n - 2) (aka 피보나치 수열)
/*
a = |x y|, b = |f(1)|
    |1 0|      |f(0)|
*/
ll fibo(ll n) {
  matrix<ll, 2, 2> a;
  matrix<ll, 2, 1> b;
  a[0][0] = a[0][1] = a[1][0] = b[0][0] = 1;
  return (pow(a, n) * b)[1][0];
}

template <typename T, int N, int M>
istream& operator>> (istream& cin, matrix<T, N, M>& v) {
  for(int i = 0;i < N;i++) for(int j = 0;j < M;j++) cin >> v[i][j];
  return cin;
}

template <typename T, int N, int M>
ostream& operator<< (ostream& cout, matrix<T, N, M>& v) {
  for(int i = 0;i < N;i++) for(int j = 0;j < M;j++) cout << v[i][j] << " \n"[j + 1 == M];
  return cout;
}