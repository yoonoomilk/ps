#include <x86intrin.h>

class dynamic_bitset {
  int sz, wsz;
  vector<ull> arr;

public:
  class reference {
    friend class dynamic_bitset;
    ull *ptr;
    int idx;
    reference(dynamic_bitset& v, int i) : ptr(&v.arr[i >> 6]), idx(i & 63) {}
  public:
    operator bool() const { return (*ptr >> idx) & 1; }
    reference& operator= (bool v) {
      if(v) *ptr |= 1ULL << idx;
      else *ptr &= ~1ULL << idx;
      return *this;
    }
    void flip() { *ptr ^= 1ULL << idx; }
  };

  dynamic_bitset(int n = 0, bool raw = false) {
    init(n, raw);
  }

  void init(int n = 0, bool raw = false) {
    sz = n;
    wsz = sz + 63 >> 6;
    arr.assign(wsz, raw ? -1 : 0);
  }

  int size() const { return sz; }

  int count() const {
    int tmp = 0;
    for(int i = 0;i < wsz;i++) tmp += __builtin_popcountll(arr[i]);
    return tmp;
  }

  reference operator[] (int i) { return reference(*this, i); }
  bool operator[] (int i) const { return (arr[i >> 6] >> (i & 63)) & 1; }
  dynamic_bitset operator& (const dynamic_bitset& v) const {
    assert(sz == v.sz);
    dynamic_bitset tmp = *this;
    for(int i = 0;i < wsz;i++) tmp.arr[i] &= v.arr[i];
    return tmp;
  }
  dynamic_bitset& operator&= (const dynamic_bitset& v) { return *this = *this & v; }
  dynamic_bitset operator| (const dynamic_bitset& v) const {
    assert(sz == v.sz);
    dynamic_bitset tmp = *this;
    for(int i = 0;i < wsz;i++) tmp.arr[i] |= v.arr[i];
    return tmp;
  }
  dynamic_bitset& operator|= (const dynamic_bitset& v) { return *this = *this | v; }
  dynamic_bitset operator^ (const dynamic_bitset& v) const {
    assert(sz == v.sz);
    dynamic_bitset tmp = *this;
    for(int i = 0;i < wsz;i++) tmp.arr[i] ^= v.arr[i];
    return tmp;
  }
  dynamic_bitset& operator^= (const dynamic_bitset& v) { return *this = *this ^ v; }
  dynamic_bitset operator<< (int v) const {
    if(v >= sz) return dynamic_bitset(sz);
    dynamic_bitset tmp = *this;
    if(v == 0) return tmp;
    int wshift = v >> 6, offset = v & 63, sub_offset = 64 - offset;
    if(offset == 0) for(int i = wsz - 1;i >= wshift;i--) tmp.arr[i] = tmp.arr[i - wshift];
    else {
      for(int i = wsz - 1;i > wshift;i--)
        tmp.arr[i] = tmp.arr[i - wshift] << offset | tmp.arr[i - wshift - 1] >> sub_offset;
      tmp.arr[wshift] = tmp.arr[0] << offset;
    }
    fill(tmp.arr.begin(), tmp.arr.begin() + wshift, 0);
    if(sz & 63) tmp.arr[wsz - 1] &= (1ULL << (sz & 63)) - 1;
    return tmp;
  }
  dynamic_bitset& operator<<= (int v) { return *this = *this << v; }
  dynamic_bitset operator>> (int v) const {
    if(v >= sz) return dynamic_bitset(sz);
    dynamic_bitset tmp = *this;
    if(v == 0) return tmp;
    int wshift = v >> 6, offset = v & 63, lim = wsz - wshift - 1, sub_offset = 64 - offset;
    if(offset == 0) for(int i = 0;i <= lim;i++) tmp.arr[i] = tmp.arr[i + wshift];
    else {
      for(int i = 0;i < lim;i++)
        tmp.arr[i] = tmp.arr[i + wshift] >> offset | tmp.arr[i + wshift + 1] << sub_offset;
      tmp.arr[lim] = tmp.arr[wsz - 1] >> offset;
    }
    fill(tmp.arr.begin() + lim + 1, tmp.arr.end(), 0);
    return tmp;
  }
  dynamic_bitset& operator>>= (int v) { return *this = *this >> v; }
  dynamic_bitset operator+ (const dynamic_bitset& v) const {
    assert(sz == v.sz);
    dynamic_bitset tmp = *this;
    for(int i = 0, c = 0;i < wsz;i++) c = _addcarry_u64(c, tmp.arr[i], v.arr[i], &tmp.arr[i]);
    return tmp;
  }
  dynamic_bitset& operator+= (const dynamic_bitset& v) { return *this = *this + v; }
  dynamic_bitset operator- (const dynamic_bitset& v) const {
    assert(sz == v.sz);
    dynamic_bitset tmp = *this;
    for(int i = 0, c = 0;i < wsz;i++) c = _subborrow_u64(c, tmp.arr[i], v.arr[i], &tmp.arr[i]);
    return tmp;
  }
  dynamic_bitset& operator-= (const dynamic_bitset& v) { return *this = *this - v; }
};