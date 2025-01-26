```cpp
#include <unistd.h>

#define MAX (1 << 20)

char wbuf[MAX];
int wp;
```

# 코드
```cpp
void _flush() {
  write(1, wbuf, wp);
  wp = 0;
}

void _wc(char c) {
  wbuf[wp++] = c;
  if (wp == MAX) _flush();
}

void writeUInt(int n) {
  if (n/10) writeUInt(n/10);
  _wc(n%10 + 48);
}

void writeInt(int n) {
  if (n < 0) _wc('-');
  writeUInt(abs(n));
}
```