#include "math/modint.cpp"

modint comb(int n, int r) {
  if(n < r) return 0;
  if(r > n - r) r = n - r;
  modint x = 1, y = 1;
  for(int i = 0;i < r;i++) {
    x *= (n - i);
    y *= (i + 1);
  }
  return x / y;
}