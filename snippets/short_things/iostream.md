## more iostream

### pair
```cpp
template <typename T1, typename T2>
istream& operator>> (istream& cin, pair<T1, T2>& v) {
  return cin >> v.first >> v.second;
}

template <typename T1, typename T2>
ostream& operator<< (ostream& cout, const pair<T1, T2>& v) {
  return cout << format("({}, {})", v.first, v.second);
}
```

### __float128
```cpp
istream& operator>> (istream& cin, __float128& v) {
  long double a; cin >> a;
  v = a;
  return cin;
}
ostream& operator<< (ostream& cout, const __float128& v) {
  return cout << (long double)v;
}
```

## cout precision
```cpp
cout << fixed;

cout << setprecision(n);
```