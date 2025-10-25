modint combination(int n, int r) {
  if(r > n - r) r = n - r;
  modint x = 1, y = 1;
  for(int i = 0;i < r;i++) {
    x = x * (n - i);
    y = y * (i + 1);
  }
  return x / y;
}