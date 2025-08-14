// https://justicehui.github.io/ps/2019/10/25/BOJ13159/
// TODO

template <typename T, typename Compare>
class splay_tree {
  struct node {
    int l, r, p;
    T v;
    node(T &v) : v(v) {
      l = r = p = -1;
    }
  };
  int root;
  vector<node> tree;
  Compare cmp;

  int append(T &v) {
    tree.push_back(node(v));
    return tree.size() - 1;
  }

  void rotate(int i) {
    int p = tree[i].p, b = -1;
    if(p == -1) return;
    if(i == tree[p].l) {
      tree[p].l = b = tree[i].r;
      tree[i].r = p;
    } else {
      tree[p].r = b = tree[i].l;
      tree[i].l = p;
    }
    tree[i].p = tree[p].p;
    tree[p].p = i;
    if(b != -1) tree[b].p = p;
    if(tree[i].p != -1) {
      if(p == tree[tree[i].p].l) tree[tree[i].p].l = i;
      else tree[tree[i].p].r = i;
    } else root = a;
  }

  void splay(int i) {
    while(tree[i].p != -1) {
      int p = tree[i].p, pp = tree[p].p;
      if(pp != -1) {
        if((i == tree[p].l) == (p == tree[pp].l)) rotate(p);
        else rotate(i);
      }
      rotate(i);
    }
  }

public:
  splay_tree() {
    root = append();
  }

  void insert(T v) {
    
  }
};