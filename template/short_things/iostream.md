## pair iostream
```cpp
template <typename T1, typename T2>
istream& operator >> (istream& cin, pair<T1, T2>& v) {
  return cin >> v.first >> v.second;
}

template <typename T1, typename T2>
ostream& operator<< (ostream& cout, pair<T1, T2> v) {
  return cout << format("({}, {})", v.first, v.second);
}
```

## cout precision
```cpp
cout << fixed;

cout << setprecision(n);
```
