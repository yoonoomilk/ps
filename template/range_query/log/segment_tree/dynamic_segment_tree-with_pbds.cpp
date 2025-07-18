#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

// MLE 이슈 + TLE 이슈 = 쓰레기
template <typename T, typename Merge>
class dynamic_segment_tree {
  const int sz = 1;
  const T raw;
  cc_hash_table<int, T> tree;
  Merge op;

  T get(int a) {
    if(tree.find(a) != tree.end()) return tree[a];
    return raw;
  }

public:
  dynamic_segment_tree(int mx, T raw = T()) : sz(1 << __lg(mx * 2 - 1)), raw(raw) {}

  void update(int a, T x) {
    a += sz;
    tree[a] = x;
    while(a /= 2) tree[a] = op(get(a * 2), get(a * 2 + 1));
  }

  T query(int l, int r) {
    l += sz; r += sz;
    T s1 = raw, s2 = raw;
    for(;l <= r;l /= 2, r /= 2) {
      if(l & 1) s1 = op(s1, get(l++));
      if(~r & 1) s2 = op(get(r--), s2);
    }
    return op(s1, s2);
  }
};