// 오류가 있을지도?
template <typename T, typename Merge>
class persistent_segment_tree {
  const int sz;
  const T raw;
  struct node {
    int l, r;
    T v;
    node(const T& a) : l(-1), r(-1), v(a) {}
  };
  vector<node> tree;
  vector<int> root;
  Merge op;

  int append() {
    tree.push_back(node());
    return tree.size() - 1;
  }

  int update(int cur, int s, int e, int i, const T& v){
    int id = append();
    tree[id] = tree[cur];
    if(s == e){
      tree[id].v = v;
      return id;
    }
    int m=(s+e)/2;
    if(i <= m){
      int old = tree[cur].l;
      if(old == -1) old = append();
      tree[id].l = update(old, s, m, i, v);
    } else {
      int old = tree[cur].r;
      if(old == -1) old = append();
      tree[id].r = update(old, m+1, e, i, v);
    }
    tree[id].v = op(
      tree[id].l != -1 ? tree[tree[id].l].v : raw,
      tree[id].r != -1 ? tree[tree[id].r].v : raw
    );
    return id;
  }

  T query(int cur, int s, int e, int l, int r) {
    if(cur == -1 || r < s || e < l) return raw;
    if(l <= s && e <= r) return tree[cur].v;
    int m = (s + e) / 2;
    return op(
      query(tree[cur].l, s, m, l, r),
      query(tree[cur].r, m + 1, e, l, r)
    );
  }

public:
  persistent_segment_tree(int mx, const T& raw = T()) : sz(mx + 1), raw(raw) {
    root.push_back(append());
  }

  int update(int i, const T& v, int base_ver = 0){
    root.push_back(update(root[base_ver], 0, sz, i, v));
    return root.size() - 1;
  }

  T query(int ver, int l, int r) {
    return query(root[ver], 0, sz, l, r);
  }
};