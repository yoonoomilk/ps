## 1-base
```cpp
for(int i = 1;i <= n;i++) {
  cin >> raw[i];
  arr[i] = raw[i];
}
sort(arr+1, arr+n+1);
auto yap = unique(arr+1, arr+n+1);
for(int i = 1;i <= n;i++) raw[i] = 1 + lower_bound(arr+1, yap, raw[i]) - (arr+1);
```

## 0-base
```cpp
for(int i = 0;i < n;i++) {
  cin >> raw[i];
  arr[i] = raw[i];
}
sort(arr, arr+n);
auto yap = unique(arr, arr+n);
for(int i = 0;i < n;i++) raw[i] = 1 + lower_bound(arr, yap, raw[i]) - arr;
```