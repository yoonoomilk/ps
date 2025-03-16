# 코드
```cpp
class trie {
  int cnt;
  map<char, trie*> arr;
  bool have = false;

public:
  trie() {
    cnt = 0;
  }

  ~trie() {
    for (auto i = arr.begin();i != arr.end();i++) delete i->second;
  }

  bool insert(const char* s, const char* e) {
    if (s == e) {
      if (have) return false;
      cnt++;
      return have = true;
    } else {
      if (arr.find(*s) == arr.end()) arr[*s] = new trie;
      if (arr[*s]->insert(s + 1, e)) {
        cnt++;
        return true;
      }
      return false;
    }
  }
  bool insert(string& v) {
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

  int match(const char* s, const char* e) {
    if (s == e) return cnt;
    if (arr.find(*s) == arr.end()) return false;
    return arr[*s]->match(s + 1, e);
  }
  int match(string& v) {
    return match(v.c_str(), v.c_str() + v.size());
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