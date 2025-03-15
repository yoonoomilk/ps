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

  bool insert(string &v, int idx) {
    if(idx == v.size() - 1) {
      if(have) return false;
      cnt++;
      return have = true;
    }
    else {
      int nxt = op(v[idx]);
      if(arr[nxt] == nullptr) arr[nex] = new trie(sz, op);
      if(arr[nxt]->insert(v, idx + 1)) {
        cnt++;
        return true;
      }
    }
  }
  void insert(string &v) {
    insert(v, 0);
  }

  bool find(string &v, int idx) {
    if(idx == v.size() - 1) return have;
    int nxt = op(v[idx]);
    if(arr[nxt] == nullptr) return false;
    return arr[nxt]->find(v, idx + 1);
  }
  void find(string &v) {
    find(v, 0);
  }

  int match(string &v, int idx) {
    if(idx == v.size() - 1) return cnt;
    int nxt = op(v[idx]);
    if(arr[nxt] == nullptr) return false;
    return arr[nxt]->find(v, idx + 1);
  }
  void match(string &v) {
    match(v, 0);
  }
};
```

# 문제
* [뭐시기](https://boj.kr/1000)
  * http://boj.kr/