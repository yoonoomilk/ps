class trie {
public:
  vector<pair<char, trie>> arr;
  bool have = false;

  trie() { }

  trie* child(char c) {
    for (auto& [k, v] : arr) if (k == c) return &v;
    return nullptr;
  }

  template <typename I>
  void insert(I s, I e) {
    trie* cur = this;
    for (;s != e;s++) {
      trie* nxt = cur->child(*s);
      if (nxt == nullptr) {
        cur->arr.push_back({*s, trie()});
        nxt = &cur->arr.back().second;
      }
      cur = nxt;
    }
    cur->have = true;
  }
};