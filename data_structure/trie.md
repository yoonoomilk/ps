# 코드
```cpp
class trie {
public:
  vector<pair<char, trie>> arr;
  bool have = false;

  trie() { }

  trie* child(char c) {
    for(auto& [k, v] : arr) if(k == c) return &v;
    return nullptr;
  }

  template <typename I>
  void insert(I s, I e) {
    trie* cur = this;
    for(;s != e;s++) {
      trie* nxt = cur->child(*s);
      if(nxt == nullptr) {
        cur->arr.push_back({*s, trie()});
        nxt = &cur->arr.back().second;
      }
      cur = nxt;
    }
    cur->have = true;
  }
};
```

# 문제
* [전화번호 목록](https://boj.kr/5052)
  * http://boj.kr/d1e5807caab4438180739661914e200b
* [전설](https://boj.kr/19585)
  * http://boj.kr/a470a4fb004f44f1be80fb77310aea3f
