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

## 추가
```cpp
// x와 xor했을 때의 최댓값
int max(int x) {
  trie* cur = this;
  int tmp = 0;
  for (int i = 30;i >= 0;i--) {
    bool bit = x >> i & 1;
    if (cur->arr[!bit] && cur->arr[!bit]->cnt > 0) {
      tmp |= (1 << j);
      cur = cur->arr[!bit];
    } else cur = cur->arr[bit];
  }
  return tmp;
}

// x와 xor했을 때 k 미만인 경우의 수
int cnt(int x, int k) {
  int tmp = 0;
  trie *cur = &root;
  for(int i = 30;i >= 0;i--) {
    bool bit = x >> i & 1;
    if(k >> i & 1) {
      if(cur->arr[bit]) tmp += cur->arr[bit]->cnt;
      if(cur->arr[!bit]) cur = cur->arr[!bit];
      else break;
    } else if(cur->arr[bit]) cur = cur->arr[bit];
    else break;
  }
  return tmp;
}
```

# 문제
* [xor 쿼리](https://boj.kr/30865)
  * http://boj.kr/a451f87e42d442b6b2390b1a3c2c69bd
* [부분 수열 XOR](https://boj.kr/13445)
  * http://boj.kr/9dc738a2b0cf4b0fad93b688cfd9a868
* [XOR 합](https://boj.kr/13504)
  * http://boj.kr/ab6ee6b1e8564632a31796a9cf08714c
* [XOR 자료구조](https://boj.kr/20919)
  * http://boj.kr/adcbb71bde954d49b1005130cf25f2b3
* [두 수 XOR](https://boj.kr/13505)
  * http://boj.kr/0872041452fe42e99da23f262119a6ef