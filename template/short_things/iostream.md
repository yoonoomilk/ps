## custom iostream
```cpp
istream& operator >> (istream& cin, T& v) {
  return cin >> T;
}

ostream& operator << (ostream& cout, T& v) {
  return cout << T;
}
```

## cout precision
```cpp
cout << fixed;

cout << setprecision(n);
```
