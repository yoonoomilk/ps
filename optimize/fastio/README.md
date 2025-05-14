## mmap input
```cpp
#include <sys/stat.h>
#include <sys/mman.h>

struct stat st; fstat(0, &st);
char *rp = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);

static inline int readInt() {
  int tmp = 0;
  for(char c = *rp++;c & 16;c = *rp++) tmp = tmp * 10 + (c & 15);
  return tmp; 
}

static inline int readInt() {
  int tmp = 0;
  char c = *rp++, flag = 0;
  if(c == '-') flag = 1, c = *rp++;
  for(;c & 16;c = *rp++) tmp = tmp * 10 + (c & 15);
  return flag ? -tmp : tmp;
}
```

## unistd input
```cpp
#include <unistd.h>

char rbuf[1 << 20];
char *rp = rbuf + (1 << 20);

static inline char rc() {
  if(rp == rbuf + (1 << 20)) read(0, rp = rbuf, 1 << 20);
  return *rp++;
}

static inline int readInt() {
  int tmp = 0;
  for(char c = rc();c & 16;c = rc()) tmp = tmp * 10 + (c & 15);
  return tmp; 
}

static inline int readInt() {
  int tmp = 0;
  char c = rc(), flag = 0;
  if(c == '-') flag = 1, c = rc();
  for(;c & 16;c = rc()) tmp = tmp * 10 + (c & 15);
  return flag ? -tmp : tmp;
}
```

## unistd output
```cpp
#include <unistd.h>

char wbuf[1 << 18];
int wp = 0;

static inline int getSz(int n) {
  int tmp = 1;
  while(n /= 10) tmp++;
  return tmp;
}

static inline void writeInt(int n) {
  int sz = getSz(n);
  if(wp + sz + 1 > (1 << 18)) write(1, wbuf, wp), wp = 0;
  for(int i = sz;i--;n /= 10) wbuf[wp + i] = n % 10 | 48;
  wp += sz;
  wbuf[wp++] = ' ';
}

static inline void writeInt(int n) {
  int sz = getSz(n);
  if(wp + sz + 2 > (1 << 18)) write(1, wbuf, wp), wp = 0;
  if(n < 0) wbuf[wp++] = '-', n = -n;
  for(int i = sz;i--;n /= 10) wbuf[wp + i] = n % 10 | 48;
  wp += sz;
  wbuf[wp++] = ' ';
}
```

## 156/0
```cpp
#define REREAD if (__builtin_expect(rp == len, 0)) len = read(0, buf, sizeof buf), rp = 0
int main;
int __libc_start_main() {
  char buf[1 << 15];
  int rp = 0, len = read(0, buf, sizeof buf);
  for(;;rp++) {
    REREAD;
    if(buf[rp] < '0' || '9' < buf[rp]) break;
    cur = cur * 10 + (buf[rp] & 15);
  }
}
```