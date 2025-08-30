class lowest_common_ancestor {
  const int sz;
  static_graph<void> graph;
  struct lca_op {
    pair<int, int> operator() (pair<int, int> a, pair<int, int> b) {
      return min(a, b);
    }
  };
  segment_tree<pair<int, int>, lca_op> seg;
  vector<int> in;

public:
  lowest_common_ancestor(int n) : sz(n + 1), graph(n, n * 2 - 2), seg(sz * 2, {1e9, -1}), in(sz) {}

  void add(int a, int b) {
    graph.add(a, b);
  }

  void init(int root) {
    int ettn = 0;
    function<void(int, int, int)> ett = [&](int cur, int d, int pa) {
      seg.update(ettn, {d, cur});
      in[cur] = ettn++;
      for(int i : graph[cur]) if(i != pa) {
        ett(i, d + 1, cur);
        seg.update(ettn++, {d, cur});
      }
    };
    ett(root, 1, -1);
  }

  int operator() (int a, int b) {
    if(in[a] > in[b]) swap(a, b);
    return seg(in[a], in[b]).second;
  }
};

//https://infossm.github.io/blog/2022/08/19/farachcoltonbender/