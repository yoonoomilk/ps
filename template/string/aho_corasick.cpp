// TODO

struct aho_corasick {
  map<char, aho_corasick*> arr;
  aho_corasick* fail = nullptr;
  int have = 0;

  aho_corasick() { }
  ~aho_corasick() {
    for(auto [c, nxt] : arr) delete nxt;
  }

  aho_corasick* child(char c) {
    if(auto it = arr.find(c);it != arr.end()) return it->second;
    return nullptr;
  }

  template <typename I>
  void insert(I s, I e) {
    aho_corasick* cur = this;
    for(;s != e;s++) {
      aho_corasick* nxt = cur->child(*s);
      if(nxt == nullptr) {
        aho_corasick* tmp = new aho_corasick();
        cur->arr[*s] = tmp;
        nxt = tmp;
      }
      cur = nxt;
    }
    cur->have++;
  }

  void init() {
    queue<aho_corasick*> q;
    q.push(this);
    while(q.size()) {
      aho_corasick *cur = q.front();
      q.pop();
      for(auto [c, nxt] : cur->arr) {
        if(cur == this) nxt->fail = this;
        else {
          aho_corasick *dest = cur->fail;
          while(dest != this && !dest->child(c)) dest = dest->fail;
          if(dest->child(c)) dest = dest->child(c);
          else dest = this;
          nxt->fail = dest;
        }
        nxt->have += nxt->fail->have;
        q.push(nxt);
      }
    }
  }

  template <typename I>
  int count(I s, I e) {
    int tmp = 0;
    aho_corasick *cur = this;
    for(;s != e;s++) {
      aho_corasick *nxt = cur->child(*s);
      while(cur != this && !nxt) {
        cur = cur->fail;
        nxt = cur->child(*s);
      }
      if(nxt) cur = nxt;
      tmp += cur->have;
    }
    return tmp;
  }
};