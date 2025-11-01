#include <unistd.h>

class INPUT {
  static const int sz = 1 << 20;
  char rbuf[sz], *rp = rbuf + sz;
  bool END_FLAG = false;

  bool is_blank(char c) { return c == ' ' || c == '\n'; }
  bool is_eof(char c) { return c == '\0'; }
  char rc() {
    if(rp == rbuf + sz) read(0, rp = rbuf, sz);
    return *rp++;
  }

public:
  explicit operator bool() { return !END_FLAG; }
  INPUT() {}

  INPUT& operator >> (char& v) {
    v = rc();
    while(is_blank(v)) v = rc();
    if(is_eof(v)) END_FLAG = true;
    return *this;
  }

  template <typename T>
  requires unsigned_integral<T>
  INPUT& operator >> (T& v) {
    v = 0;
    char c = rc();
    while(is_blank(c)) c = rc();
    for(;!is_blank(c) && !is_eof(c);c = rc()) v = v * 10 + (c & 15);
    if(is_eof(c)) END_FLAG = true;
    return *this;
  }

  template <typename T>
  requires signed_integral<T>
  INPUT& operator >> (T& v) {
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

  INPUT& operator >> (string& v) {
    v.clear();
    char c = rc();
    while(is_blank(c)) c = rc();
    for(;!is_blank(c) && !is_eof(c);c = rc()) v.push_back(c);
    if(is_eof(c)) END_FLAG = true;
    return *this;
  }

  template <typename T>
  requires floating_point<T>
  INPUT& operator >> (T& v) {
    string s;
    *this >> s;
    v = stod(s);
    return *this;
  }

} _input;

#define cin _input