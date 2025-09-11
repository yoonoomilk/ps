template <typename T>
class linked_list {
  struct node {
    node *l, *r;
    T v;
    node(T v = T()) : l(nullptr), r(nullptr), v(v) {}
  };
  node *s, *e;

public:
  linked_list() {
    s = new node();
    e = new node();
    s->r = e;
    e->l = s;
  }
  linked_list(node *s, node *e) : s(s), e(e) {}

  void cut(node *s, node* e) {
    node *l = s->l, *r = e->r;
    l->r = r;
    r->l = l;
  }

  void append(node *loc, node *cur = nullptr) {
    
  }

  node* front() { return s->r != e ? s->r : nullptr; }
  node* back() { return e->l != e ? e->l : nullptr; }
};