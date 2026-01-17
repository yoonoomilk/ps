template <typename T>
struct _hash {
  inline static size_t SEED = chrono::high_resolution_clock::now().time_since_epoch().count();
  size_t operator() (const T& v) const { return hash<T>()(v) ^ SEED + 0x9e3779b97f4a7c15; }
};