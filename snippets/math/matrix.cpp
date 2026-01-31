template <typename T, int N, int M>
struct matrix : array<array<T, M>, N> {
  using super = array<array<T, M>, N>;

  matrix() {
    for(int i = 0;i < N;i++) (*this)[i].fill(T());
  }

  matrix<T, N, M> operator+ (matrix<T, N, M>& v) {
    matrix<T, N, M> tmp;
    for(int i = 0;i < N;i++) for(int j = 0;j < M;j++) {
      tmp[i][j] = ((*this)[i][j] + v[i][j]);
    }
    return tmp;
  }

  template <int K>
  matrix<T, N, K> operator* (matrix<T, M, K>& v) {
    matrix<T, N, K> tmp;
    for(int i = 0;i < N;i++) for(int j = 0;j < K;j++) for(int k = 0;k < M;k++) {
      tmp[i][j] += (*this)[i][k] * v[k][j];
    }
    return tmp;
  }

  friend istream& operator>> (istream& cin, matrix<T, N, M>& v) {
    for(int i = 0;i < N;i++) for(int j = 0;j < M;j++) cin >> v[i][j];
    return cin;
  }
  friend ostream& operator<< (ostream& cout, const matrix<T, N, M>& v) {
    for(int i = 0;i < N;i++) for(int j = 0;j < M;j++) cout << v[i][j] << " \n"[j + 1 == M];
    return cout;
  }
};
/* dont forget to use modular */