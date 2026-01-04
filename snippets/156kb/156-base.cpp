#include <unistd.h>

extern "C" int __libc_start_main() {
  char buf[1000], *p = buf, w = 0;
  read(0, buf, 1000);

  auto I = [&]() {
    int n = 0;
    while(*p & 16) n = n * 10 + *p++ - 48;
    p++;
    return n;
  };

  int ans = I();

  do buf[9 - ++w] = ans % 10 + 48;
  while(ans /= 10);
  write(1, buf + 9 - w, w);
  _Exit(0);
} int main() {}