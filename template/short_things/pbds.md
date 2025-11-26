## include
```cpp
#include <bits/extc++.h>
```

## ordered_set
```cpp
template <typename T>
using ordered_set = __gnu_pbds::tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
```
multiset으로 쓰려면 pair에 넣기

## faster unordered_set
```cpp
template <typename Key, typename T, typename Hash = hash<Key>>
using hash_set = __gnu_pbds::gp_hash_table<Key, T, Hash>;
```
### custom hash function
```cpp
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct _hash {
  size_t operator() (T x) const { return x ^ RANDOM; }
};
```