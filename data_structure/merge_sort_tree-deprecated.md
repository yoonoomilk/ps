# 코드
```cpp
template <typename T>
struct op {
  vector<T> operator() (const vector<T> &a, const vector<T> &b) {
    vector<T> tmp(a.size() + b.size());
    merge(
      a.begin(), a.end(),
      b.begin(), b.end(),
      tmp.begin()
    );
    return tmp;
  }
};
segment_tree<vector<T>, op>
//but O(n) for query
```
##  deprecated
```cpp
template <typename T>
class merge_sort_tree {
  int sz = 1;
  vector<vector<T>> arr;

public:
  merge_sort_tree(vector<T> raw) {
    while (sz < raw.size()) sz *= 2;
    arr.resize(2 * sz);
    for(int i = 0;i < raw.size();i++) arr[i+sz].push_back(raw[i]);
    for(int i = sz-1;i;i--) {
        arr[i].resize(arr[i*2].size() + arr[i*2+1].size());
        merge(
            arr[i*2].begin(), arr[i*2].end(),
            arr[i*2+1].begin(), arr[i*2+1].end(),
            arr[i].begin()
        );
    }
  }

  int query(int l, int r, T k) {
    l += sz;
    r += sz;
    int s = 0;
    while (l <= r) {
      if (l % 2 == 1) {
        s += arr[l].end() - upper_bound(arr[l].begin(), arr[l].end(), k);
        l++;
      }
      if (r % 2 == 0) {
        s += arr[r].end() - upper_bound(arr[r].begin(), arr[r].end(), k);
        r--;
      }
      l /= 2;
      r /= 2;
    }
    return s;
  }
};
```

# 문제
* [수열과 쿼리 1](https://boj.kr/13537)
  * http://boj.kr/dcad82fba6374b9dac65cd3846be3d15
* [수열과 쿼리 3](https://boj.kr/13544)
  * http://boj.kr/b238a74b209a406486a82180f2793b47
* [K번째 수](https://boj.kr/7469)
  * http://boj.kr/2c605b1d357e4fcc9adac0e2b056a212