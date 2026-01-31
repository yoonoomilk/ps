## https://www.acmicpc.net/problem/15922
```cpp
char *rp;

int readInt() {
  int tmp = 0;
  char c = *rp++, flag = 0;
  if(c == '-') flag = 1, c = *rp++;
  for(;c & 16;c = *rp++) tmp = tmp * 10 + (c & 15);
  return flag ? -tmp : tmp;
}

int max(int a, int b) {
  return a > b ? a : b;
}

#define PROT_READ 0x1
#define MAP_SHARED 0x01

#pragma pack(1)
struct stat {
    unsigned char pad0[48];
    unsigned long long st_size;
    unsigned char pad1[88];
};

__libc_start_main() {
  struct stat st; syscall(5, 0, &st, 0);
  rp = (char*)syscall(9, 0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);

  int lst = -1e9, ans = 0;
  int n = readInt();
  while(n--) {
    int x = readInt(), y = readInt();
    ans += max(lst, y) - max(lst, x);
    lst = max(lst, y);
  }

  char buf[10];
  int w = 0;
  do buf[10 - ++w] = ans % 10 + 48;
  while(ans /= 10);
  syscall(1, 1, buf + 10 - w, w);

  syscall(231, 0);
} main;
```

## https://www.acmicpc.net/problem/21737
```cpp
#include <unistd.h>
#define REREAD if (__builtin_expect(offset == len, 0)) len = read(0, buf, sizeof buf), offset = 0
int main;
int __libc_start_main() {
  char buf[1 << 15], obuf[1 << 16], tmp[12], op = 0;
  int len, offset = 0, v, cur, olen, ocur = 0, once = 0, i, count;
  long ext;
  len = read(0, buf, sizeof buf);
  while (buf[offset++] != '\n');
  for(;;) {
    cur = 0;
    for (;; offset++) {
      REREAD;
      if (buf[offset] < '0' || buf[offset] > '9') break;
      cur = cur * 10 + buf[offset] - '0';
    }
    switch (op) {
    case 0:
      v = cur;
      break;
    case 'S':
      v -= cur;
      break;
    case 'M':
      v *= cur;
      break;
    case 'U':
      v /= cur;
      break;
    case 'P':
      v += cur;
      break;
    }
    for (count = 0;; count++, offset++) {
      REREAD;
      if (buf[offset] != 'C') break;
    }
    if (count) {
      once = 1;
      ext = v < 0 ? -(long) v : v;
      olen = sizeof tmp;
      tmp[--olen] = ' ';
      do {
        tmp[--olen] = ext % 10 + '0';
        ext /= 10;
      } while (ext);
      if (v < 0) tmp[--olen] = '-';
      while (count--) {
        if (__builtin_expect(ocur + (sizeof tmp - olen) > sizeof obuf, 0)) {
          write(1, obuf, ocur);
          ocur = 0;
        }
        for (i = olen; i < sizeof tmp; i++)
          obuf[ocur++] = tmp[i];
      }
    }
    REREAD;
    if (buf[offset] > '9') op = buf[offset++];
    REREAD;
    if (buf[offset] == '\n') {
      if (ocur) write(1, obuf, ocur);
      if (!once) write(1, "NO OUTPUT", 9);
      _exit(0);
    }
  }
}

```