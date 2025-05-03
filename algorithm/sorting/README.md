# 종류
* [radix sort](#radix-sort)
  * [수 정렬하기 2](http://boj.kr/2628384ad9d94edfa59cdff3a782d9a3)
    * 204ms
* merge sort



# 코드

## radix sort
```cpp
void radix_sort(vector<int>& v) {
  for(int t = 0;t < 32;t += 8) {
    queue<int> q[256];
    for(int i : v) q[(i >> t) & 255].push(i);
    int cur = 0;
    for(int i = 0;i < 256;i++) while(q[i].size()) {
      v[cur++] = q[i].front();
      q[i].pop();
    }
  }
}
```