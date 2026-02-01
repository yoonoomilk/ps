// https://en.wikipedia.org/wiki/De_Bruijn_sequence

vector<int> de_bruijn(int k, int n) {
  vector<int> arr(n), tmp;
  auto dfs = [&](auto& self, int cur, int len) -> void {
    if(cur == n) {
      if(n % len == 0) for(int i = 0;i < len;i++) tmp.push_back(arr[i]);
    } else {
      int j = cur - len >= 0 ? arr[cur - len] : 0;
      arr[cur] = j;
      self(self, cur + 1, len);
      for(int i = j + 1;i < k;i++) {
        arr[cur] = i;
        self(self, cur + 1, cur + 1);
      }
    }
  };
  dfs(dfs, 0, 1);
  return tmp;
}