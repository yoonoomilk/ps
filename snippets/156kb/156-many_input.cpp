#include <unistd.h>

extern "C" int __libc_start_main() {
  char buf[1 << 16], *rp = buf + (1 << 16), w = 0;

  auto rc = [&]() {
    if(rp == buf + (1 << 16)) read(0, rp = buf, 1 << 16);
    return *rp++;
  };
  auto ri = [&]() {
    int tmp = 0;
    for(char c = rc();c & 16;c = rc()) tmp = tmp * 10 + c - 48;
    return tmp;
  };

  int ans = 0;

  do buf[9 - ++w] = ans % 10 + 48;
  while(ans /= 10);
  write(1, buf + 9 - w, w);
  _Exit(0);
} int main() {}