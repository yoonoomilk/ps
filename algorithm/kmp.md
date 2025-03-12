# 코드
```cpp
class kmp {
  string s, p;
  
public:
  vector<int> pi, arr;

  kmp(string s, string p) : s(s), p(p) {
    int n = s.size(), m = p.size();
    pi.resize(m);
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
  }
};
```

# 문제
* [찾기](https://boj.kr/1786)
  * http://boj.kr/4a6a0e07276b4561b7886f5f949386b0
* [광고](https://boj.kr/1305)
  * http://boj.kr/652c19b2baad413e812e6970f50f1336
* [문자열 제곱](https://boj.kr/4354)
  * http://boj.kr/7a62f9a082ff4a52845d6c48fd79999f