# 코드
```cpp
class trie {
public:
  map<char, trie*> arr;
  bool have = false;

  trie() { }

  ~trie() {
    for (auto i = arr.begin();i != arr.end();i++) delete i->second;
  }

  void insert(const char* s, const char* e) {
    if (s == e) have = true;
    else {
      if (arr.find(*s) == arr.end()) arr[*s] = new trie;
      arr[*s]->insert(s + 1, e);
    }
  }
  void insert(string& v) {
    return insert(v.c_str(), v.c_str() + v.size());
  }

  bool find(const char* s, const char* e) {
    if (s == e) return have;
    if (arr.find(*s) == arr.end()) return false;
    return arr[*s]->find(s + 1, e);
  }
  bool find(string& v) {
    return find(v.c_str(), v.c_str() + v.size());
  }

  trie* child(char c) {
    if (arr.find(c) != arr.end()) return arr[c];
    return nullptr;
  }
};
```

# 문제
* [전화번호 목록](https://boj.kr/5052)
  * http://boj.kr/d1e5807caab4438180739661914e200b