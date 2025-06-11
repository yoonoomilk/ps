## input
```cpp
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
}
```