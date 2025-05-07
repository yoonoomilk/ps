## header
```cpp
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2")
```

## short & fast IO

### mmap fast input
```cpp
#include <sys/stat.h>
#include <sys/mman.h>

struct stat st; fstat(0, &st);
char *rp = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);

auto readInt = [&]() {
  int tmp = 0;
  for(char c = *rp++;c & 16;c = *rp++) tmp = tmp * 10 + (c & 15);
  return tmp; 
};

auto readInt = [&]() {
  int tmp = 0;
  char c = *rp++;
  bool flag = 0;
  if(c == '-') flag = 1, c = *rp++;
  for(;c & 16;c = *rp++) tmp = tmp * 10 + (c & 15);
  return flag ? -tmp : tmp;
};
```

### fast output
```cpp
#include <unistd.h>

char wbuf[1 << 18];
int wp = 0;

auto getSz = [](int n) {
  int tmp = 1;
  while(n /= 10) tmp++;
  return tmp;
};

auto writeInt = [&](int n) {
  int sz = getSz(n);
  if(wp + sz + 2 > (1 << 19)) write(1, wbuf, wp), wp = 0;
  if(n < 0) wbuf[wp++] = '-', n = -n;
  for(int i = sz;i--;n /= 10) wbuf[wp + i] = n % 10 | 48;
  wp += sz;
  wbuf[wp++] = ' ';
};
```

## fast IO
```cpp
int getSz(int n) {
  int tmp = 1;
  while(n /= 10) tmp++;
  return tmp;
}

void writeInt(int n) {
  int sz = getSz(n);
  if(wp + sz + 2 > (1 << 19)) write(1, wbuf, wp), wp = 0;
  if(n < 0) wbuf[wp++] = '-', n = -n;
  for(int i = sz;i--;n /= 10) wbuf[wp + i] = n % 10 | 48;
  wp += sz;
  wbuf[wp++] = ' ';
}
```