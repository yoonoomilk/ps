# 코드
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
