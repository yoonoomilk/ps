template <typename T, int N, int M>
struct matrix : array<array<T, M>, N> {
  using super = array<array<T, M>, N>;

  matrix(bool identity = false) {
    for(int i = 0;i < N;i++) super::operator[](i).fill(T());
    if(identity) {
      assert(N == M);
      for(int i = 0;i < N;i++) super::operator[](i)[i] = 1;
    }
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
matrix<T, N, N> pow(matrix<T, N, N> v, long long exp) {
  matrix<T, N, N> tmp;
  for(int i = 0;i < N;i++) tmp[i][i] = 1;
  for(;exp;exp /= 2) {
    if(exp & 1) tmp = tmp * v;
    v = v * v;
  }
  return tmp;
}

// 피보나치 수열
ll fibo(ll n) {
  matrix<ll, 2, 2> a;
  matrix<ll, 2, 1> b;
  a[0][0] = a[0][1] = a[1][0] = b[0][0] = 1;

  return (pow(a, n) * b)[1][0];
}