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
    for(int i = 30;i >= 0;i--) {
      bool bit = (x >> i) & 1;
      if(!cur->arr[bit]) cur->arr[bit] = new trie();
      cur = cur->arr[bit];
      cur->cnt += delta;
    }
  }
} root;

// x와 xor했을 때의 최댓값
int max(int x) {
  int tmp = 0;
  trie* cur = &root;
  for(int i = 30;i >= 0;i--) {
    bool bit = x >> i & 1;
    if(cur->arr[!bit] && cur->arr[!bit]->cnt > 0) {
      tmp |= (1 << i);
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