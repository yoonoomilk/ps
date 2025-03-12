# 코드
```cpp
vector<int> kmp(string s, string p) {
  int n = s.size(), m = p.size();
  vector<int> pi(m), arr;
  for(int i = 1, j = 0;i < m;i++) {
    while(j > 0 && p[i] !=  p[j]) j = pi[j-1];
    if(p[i] == p[j]) pi[i] = ++j;
  }
  for(int i = 0, j = 0;i < n;i++) {
    while(j > 0 && s[i] != p[j]) j = pi[j-1];
    if(s[i] != p[j]) continue;
    if(j == m-1) {
      arr.push_back(i-m+1);
      j = pi[j];
    } else j++;
  }
  return arr;
}
```

# 문제
* [찾기](https://boj.kr/1786)
  * http://boj.kr/4a6a0e07276b4561b7886f5f949386b0