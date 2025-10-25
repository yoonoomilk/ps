// TODO

template <typename T>
class static_graph {
  struct edge {
    int u;
    T v;
    edge() = default;
    edge(int u, T& v) : u(u), v(v) {}
    operator int() const { return u; }
  };
  struct edges {
    using I = vector<edge>::const_iterator;
    I s, e;
    I begin() { return s; }
    I end() { return e; }
    size_t size() { return e - s; }
    decltype(auto) operator[] (int i) { return s[i]; }
  };

  const int n, m;
  vector<int> cnt;
  vector<pair<int, edge>> raw;
  vector<edge> arr;

public:
  static_graph(int n, int m) : n(n), m(m), cnt(n + 2), arr(m) {
    raw.reserve(m);
  }

  template <typename... Args>
  void add(int u, Args&&... args) {
    raw.emplace_back(u, edge{forward<Args>(args)...});
    cnt[u]++;
    if(raw.size() == m) {
      for(int i = 1;i < cnt.size();i++) cnt[i] += cnt[i - 1];
      for(auto& [u, v] : raw) arr[--cnt[u]] = v;
      raw.clear();
    }
  }

  edges operator[] (int i) {
    return {arr.begin() + cnt[i], arr.begin() + cnt[i + 1]};
  }
};

class static_graph {
  struct edge {
    int u;
    edge() = default;
    edge(int u) : u(u) {}
    operator int() const { return u; }
  };
  struct edges {
    using I = vector<edge>::const_iterator;
    I s, e;
    I begin() { return s; }
    I end() { return e; }
    size_t size() { return e - s; }
    decltype(auto) operator[] (int i) { return s[i]; }
  };

  const int n, m;
  vector<int> cnt;
  vector<pair<int, edge>> raw;
  vector<edge> arr;

public:
  static_graph(int n, int m) : n(n), m(m), cnt(n + 2), arr(m) {
    raw.reserve(m);
  }

  void add(int u, int v) {
    raw.emplace_back(u, v);
    cnt[u]++;
    if(raw.size() == m) {
      for(int i = 1;i < cnt.size();i++) cnt[i] += cnt[i - 1];
      for(auto& [u, v] : raw) arr[--cnt[u]] = v;
      raw.clear();
    }
  }

  edges operator[] (int i) {
    return {arr.begin() + cnt[i], arr.begin() + cnt[i + 1]};
  }
};