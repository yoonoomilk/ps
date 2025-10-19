struct trie {
  map<char, trie*> arr;
  bool have = false;

  trie() { }

  trie* child(char c) {
    if(auto it = arr.find(c);it != arr.end()) return it->second;
    return nullptr;
  }

  template <typename I>
  void insert(I s, I e) {
    trie* cur = this;
    for(;s != e;s++) {
      trie* nxt = cur->child(*s);
      if(nxt == nullptr) {
        trie* tmp = new trie();
        cur->arr[*s] = tmp;
        nxt = tmp;
      }
      cur = nxt;
    }
    cur->have = true;
  }
};