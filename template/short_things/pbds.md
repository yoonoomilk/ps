## ordered_set
```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, splay_tree_tag, tree_order_statistics_node_update>;
```
multiset으로 쓰려면 pair에 넣기

## faster unordered_set
```cpp
#include <ext/pb_ds/assoc_container.hpp>
template <typename Key, typename T, typename Hash = hash<Key>>
using hash_set = gp_hash_table<Key, T, Hash>;
```
### custom hash function
```cpp
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct _hash {
  size_t operator() (T x) const { return x ^ RANDOM; }
};
```