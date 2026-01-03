#include "short_things/_hash.cpp"
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <typename Key, typename T>
using hash_map = gp_hash_table<Key, T, _hash<Key>>;