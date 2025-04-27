```cpp
#include <unistd.h>

#define MAX (1 << 20)

char rbuf[MAX];
char *rp = rbuf+MAX;
```

# 코드
```cpp
char _rc() {
  if (rp == rbuf + MAX) read(0, rp = rbuf, MAX);
  return *rp++;
}

int _sz(int n) {
  int tmp = 0;
  do tmp++;
  while(n /= 10);
  return tmp;
}

char readChar() {
  char tmp = _rc();
  // TODO
  while (tmp)
}

int readInt() {
  int tmp = 0;
  bool flag = 0;
  char c = _rc();
  if (c == '-') {
    flag = 1;
    c = _rc();
  }
  for (;c & 16;c = _rc()) tmp = tmp * 10 + c - 48;
  return flag ? -tmp : tmp;
}

int readUInt() {
  int tmp = 0;
  for (char c = _rc();c & 16;c = _rc()) tmp = tmp * 10 + c - 48;
  return tmp;
}

double readFloat() {
  double bef = 0;
  bool flag = 0;
  char c = _rc();
  if (c == '-') {
    flag = 1;
    c = _rc();
  }
  for (;c & 16;c = _rc()) bef = bef * 10 + c - 48;
  double aft = 0;
  if (c == '.') aft = readInt();
  for(int i = _sz(aft);--i;) aft /= 10;
  double tmp = bef + aft;
  return flag ? -tmp : tmp;
}

double readUFloat() {
  double bef = 0;
  char c = _rc();
  for (;c & 16;c = _rc()) bef = bef * 10 + c - 48;
  double aft = 0;
  if (c == '.') aft = readInt();
  for (int i = _sz(aft);--i;) aft /= 10;
  double tmp = bef + aft;
  return tmp;
}

```