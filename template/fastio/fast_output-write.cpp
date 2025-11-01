#include <unistd.h>

class OUTPUT {
  static const int sz = 1 << 18;
  char wbuf[sz], *wp = wbuf;
  int precision = 9;

  template <typename T>
  requires integral<T>
  int get_len(T v) {
    int tmp = 1;
    while(v /= 10) tmp++;
    return tmp;
  }
  void flush() {
    write(1, wbuf, wp - wbuf);
    wp = wbuf;
  }

public:
  OUTPUT() {}
  ~OUTPUT() { flush(); }

  int setprecision(int v) {
    swap(precision, v);
    return v;
  }

  OUTPUT& operator << (char v) {
    if(wp == wbuf + sz) flush();
    *wp++ = v;
    return *this;
  }

  template <typename T>
  requires unsigned_integral<T>
  OUTPUT& operator << (T v) {
    int len = get_len(v);
    if(wp + len > wbuf + sz) flush();
    for(int i = len;i--;v /= 10) wp[i] = v % 10 | 48;
    wp += len;
    return *this;
  }

  template <typename T>
  requires signed_integral<T>
  OUTPUT& operator << (T v) {
    int len = get_len(v);
    if(wp + len + 1 > wbuf + sz) flush();
    if(v < 0) {
      *wp++ = '-';
      v = abs(v);
    }
    for(int i = len;i--;v /= 10) wp[i] = v % 10 | 48;
    wp += len;
    return *this;
  }

  OUTPUT& operator << (string_view v) {
    for(auto it = v.begin();it != v.end();) {
      if(wp == wbuf + sz) flush();
      size_t len = min(wbuf + sz - wp, v.end() - it);
      memcpy(wp, it, len);
      it += len;
      wp += len;
    }
    return *this;
  }

  template <typename T>
  requires floating_point<T>
  OUTPUT& operator << (T v) {
    char tmp[50]{};
    sprintf(tmp, "%.*lf", precision, v);
    int len = strlen(tmp);
    if(wp + len > wbuf + sz) flush();
    memcpy(wp, tmp, len);
    wp += len;
    return *this;
  }

} _OUTPUT;

#define cout _OUTPUT