## mmap input
```cpp
#include <sys/stat.h>
#include <sys/mman.h>

struct stat st; fstat(0, &st);
char *rp = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);

int readInt() {
  int tmp = 0;
  for(char c = *rp++;c & 16;c = *rp++) tmp = tmp * 10 + (c & 15);
  return tmp; 
};

int readInt() {
  int tmp = 0;
  char c = *rp++;
  bool flag = 0;
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

char rc() {
  if(rp == rbuf + (1 << 20)) read(0, rp = rbuf, 1 << 20);
  return *rp++;
}

int readInt() {
  int tmp = 0;
  for(char c = rc();c & 16;c = rc()) tmp = tmp * 10 + (c & 15);
  return tmp; 
};

int readInt() {
  int tmp = 0;
  char c = rc();
  bool flag = 0;
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

int getSz(int n) {
  int tmp = 1;
  while(n /= 10) tmp++;
  return tmp;
};

void writeInt(int n) {
  int sz = getSz(n);
  if(wp + sz + 1 > (1 << 19)) write(1, wbuf, wp), wp = 0;
  if(n < 0) wbuf[wp++] = '-', n = -n;
  for(int i = sz;i--;n /= 10) wbuf[wp + i] = n % 10 | 48;
  wp += sz;
  wbuf[wp++] = ' ';
};
```