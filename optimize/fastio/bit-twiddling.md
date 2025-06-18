## input
```cpp
int readInt() {
  bool flag = false;
  if(*rp == '-') rp++, flag = true;
  u64 x; memcpy(&x, rp, 8);
  x ^= 0x3030303030303030;
  int t = countr_zero(x & 0xf0f0f0f0f0f0f0f0) >> 3;
  x <<= 64 - (t << 3);
  x = (x * 10 + (x >> 8)) & 0x00ff00ff00ff00ff;
  x = (x * 100 + (x >> 16)) & 0x0000ffff0000ffff;
  x = (x * 10000 + (x >> 32)) & 0x00000000ffffffff;
  rp += t + 1;
  return flag ? -x : x;
}

int readInt() {
  int ret = 0, flag = 0;
  if(*rp == '-') flag = 1, rp++;
  {
    u64 x; memcpy(&x, rp, 8);
    x ^= 0x3030303030303030;
    if(!(x & 0xf0f0f0f0f0f0f0f0)) {
      x = ((x * 10) + (x >> 8)) & 0x00ff00ff00ff00ff;
      x = ((x * 100) + (x >> 16)) & 0x0000ffff0000ffff;
      x = ((x * 10000) + (x >> 32)) & 0x00000000ffffffff;
      ret = x;
      rp += 8;
    }
  }
  {
    u32 x; memcpy(&x, rp, 4);
    x ^= 0x30303030;
    if(!(x & 0xf0f0f0f0)) {
      x = ((x * 10) + (x >> 8)) & 0x00ff00ff;
      x = ((x * 100) + (x >> 16)) & 0x0000ffff;
      ret = 10000 * ret + x;
      rp += 4;
    }
  }
  {
    u16 x; memcpy(&x, rp, 2);
    x ^= 0x3030;
    if(!(x & 0xf0f0)) {
      x = ((x * 10) + (x >> 8)) & 0x00ff;
      ret = 100 * ret + x;
      rp += 2;
    }
  }
  if(*rp & 16) ret = 10 * ret + (*rp++ & 15);
  rp++;
  return flag ? -ret : ret;
}
```

## output
```cpp
constexpr int p10[] = {
  0, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
};

int getSz(int n) {
  int t = bit_width(n) * 1233 >> 12;
  return t - (n < p10[t]) + 1;
}

void writeInt(int x) {
  if(wp - wbuf + 40 > sizeof wbuf) write(1, wbuf, wp - wbuf), wp = wbuf;
  if(x < 0) *wp++ = '-', x = -x;
  int sz = getSz(x);
  for(int i = sz - 1;i >= 0;i--) wp[i] = x % 10 | 48, x /= 10;
  wp += sz;
  wbuf[wp++] = ' ';
}
```

```cpp
constexpr auto lut = [] {
  array<array<char, 4>, 10000> res;
  for (int i = 0; i < 10000; i++) {
    res[i][0] = i / 1000 | 48;
    res[i][1] = i / 100 % 10 | 48;
    res[i][2] = i / 10 % 10 | 48;
    res[i][3] = i % 10 | 48;
  }
  return res;
}();

void write_4digit_trimmed(int x) {
  if (x > 999) {
    memcpy(wp, &lut[x], 4);
    wp += 4;
  }
  else if (x > 99) {
    memcpy(wp, &lut[x * 10], 3);
    wp += 3;
  }
  else if (x > 9) {
    memcpy(wp, &lut[x * 100], 2);
    wp += 2;
  }
  else {
    memcpy(wp, &lut[x * 1000], 1);
    wp += 1;
  }
}

void write_4digit(int x) {
  memcpy(wp, &lut[x], 4);
  wp += 4;
}

void writeInt(int x) {
  if (wp - wbuf + 40 > sizeof wbuf) write(1, wbuf, wp - wbuf), wp = wbuf;
  if (x < 0) *wp++ = '-', x = -x;
  if (x > 99999999) {
    write_4digit_trimmed(x / 10000 / 10000);
    write_4digit(x / 10000 % 10000);
    write_4digit(x % 10000);
  }
  else if (x > 9999) {
    write_4digit_trimmed(x / 10000);
    write_4digit(x % 10000);
  }
  else {
    write_4digit_trimmed(x);
  }
}
```