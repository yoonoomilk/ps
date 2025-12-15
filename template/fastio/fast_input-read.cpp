#include <unistd.h>

class _istream {
  static const int sz = 1 << 20;
  char rbuf[sz], *rp = rbuf + sz;
  bool END_FLAG = false;

  constexpr bool is_blank(char c) { return c == ' ' || c == '\n'; }
  constexpr bool is_eof(char c) { return c == '\0'; }
  char rc() {
    if(rp == rbuf + sz) read(0, rp = rbuf, sz);
    return *rp++;
  }

public:
  explicit operator bool() { return !END_FLAG; }
  _istream() {}

  void tie(int i) {}

  _istream& operator >> (char& v) {
    v = rc();
    while(is_blank(v)) v = rc();
    if(is_eof(v)) END_FLAG = true;
    return *this;
  }

  template <typename T>
  requires integral<T>
  _istream& operator >> (T& v) {
    v = 0;
    char c = rc();
    bool flag = false;
    while(is_blank(c)) c = rc();
    if(c == '-') flag = true, c = rc();
    for(;!is_blank(c) && !is_eof(c);c = rc()) v = v * 10 + (c & 15);
    if(is_eof(c)) END_FLAG = true;
    if(flag) v = -v;
    return *this;
  }

  _istream& operator >> (string& v) {
    v.clear();
    char c = rc();
    while(is_blank(c)) c = rc();
    for(;!is_blank(c) && !is_eof(c);c = rc()) v.push_back(c);
    if(is_eof(c)) END_FLAG = true;
    return *this;
  }

  template <typename T>
  requires floating_point<T>
  _istream& operator >> (T& v) {
    string s;
    *this >> s;
    v = stod(s);
    return *this;
  }

} _cin;

#define cin _cin
#define istream _istream