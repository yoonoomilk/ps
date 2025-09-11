template <typename T>
class linked_list {
  struct node {
    node *l, *r;
    T v;
    node(T v = T()) : l(nullptr), r(nullptr), v(v) {}
  };
  node *s = new node(), *e = new node();

public:
  linked_list() {
    s->r = e;
    e->l = s;
  }
  linked_list(node *l, node *r) {
    s->r = l;
    e->l = r;
    l->l = s;
    r->r = e;
  }

  linked_list sub(node *s, node* e) {
    node *l = s->l, *r = e->r;
    l->r = r;
    r->l = l;
    return linked_list(s, e);
  }

  void append(node *loc, node *cur = nullptr) {
    
  }

  node* front() { return s->r != e ? s->r : nullptr; }
  node* back() { return e->l != e ? e->l : nullptr; }
};