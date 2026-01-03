#include "math/matrix.cpp"

template <typename T, int N>
matrix<T, N, N> _pow(matrix<T, N, N> v, ll exp) {
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
  return (_pow(a, n) * b)[1][0];
}