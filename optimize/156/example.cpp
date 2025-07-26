// https://www.acmicpc.net/problem/15922

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