#define I(x) int x = 0; while(*p & 16) x = x * 10 + *p++ - 48; p++;

int ans;

__libc_start_main() {
  char buf[1000], *p = buf, w = 0;
  read(0, buf, 1000);

  do buf[9 - ++w] = ans % 10 + 48;
  while(ans /= 10);
  write(1, buf + 9 - w, w);
  _Exit(0);
} main;