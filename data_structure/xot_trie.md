# 코드
```cpp
class trie {
public:
  trie* arr[2];
  int cnt = 0;

  trie() {
    arr[0] = arr[1] = nullptr;
  }
  ~trie() {
    delete arr[0];
    delete arr[1];
  }

  void insert(int x, int delta) {
    trie* cur = this;
    cur->cnt += delta;
    for (int i = 30;i >= 0;i--) {
      bool bit = (x >> i) & 1;
      if (!cur->arr[bit]) cur->arr[bit] = new trie();
      cur = cur->arr[bit];
      cur->cnt += delta;
    }
  }
};
```