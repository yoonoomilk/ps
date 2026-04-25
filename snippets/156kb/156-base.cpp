#include <unistd.h>

extern "C" int __libc_start_main() {
  char buf[1000], *p = buf, w = 0;
  read(0, buf, 1000);

  auto ri = [&]() {
    int tmp = 0;
    for(char c = *p++;c & 16;c = *p++) tmp = tmp * 10 + c - 48;
    return tmp;
  };

  int ans = ri();

  do buf[9 - ++w] = ans % 10 + 48;
  while(ans /= 10);
  write(1, buf + 9 - w, w);
  _exit(0);
} int main() {}