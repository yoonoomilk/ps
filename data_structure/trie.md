# 코드
```cpp
class trie {
  int sz, cnt = 0;
  vector<trie*> arr;
  function<int(char)> op;
  bool have = false;

public:
  trie(int sz, function<int(char)> op) : sz(sz), op(op) {
    arr.resize(sz);
  }

  ~trie() {
    for (int i = 0;i < sz;i++) if (arr[i] != nullptr) delete arr[i];
  }

  bool insert(const char* s, const char* e) {
    if (s == e) {
      if (have) return false;
      cnt++;
      return have = true;
    } else {
      int nxt = op(*s);
      if (arr[nxt] == nullptr) arr[nxt] = new trie(sz, op);
      if (arr[nxt]->insert(s + 1, e)) {
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
    int nxt = op(*s);
    if (arr[nxt] == nullptr) return false;
    return arr[nxt]->find(s + 1, e);
  }
  bool find(string& v) {
    return find(v.c_str(), v.c_str() + v.size());
  }

  int match(const char* s, const char* e) {
    if (s == e) return cnt;
    int nxt = op(*s);
    if (arr[nxt] == nullptr) return false;
    return arr[nxt]->match(s + 1, e);
  }
  int match(string& v) {
    return match(v.c_str(), v.c_str() + v.size());
  }
};
```

# 문제
* [전화번호 목록](https://boj.kr/5052)
  * http://boj.kr/d1e5807caab4438180739661914e200b