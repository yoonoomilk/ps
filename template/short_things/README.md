## constants
```cpp
const double PI = acos(-1);
```

## iostream
### custom iostream
```cpp
istream& operator >> (istream &cin, T &v) {
  cin >> T;
  return cin;
}

ostream& operator << (ostream &cout, T &v) {
  cout << T;
  return cout;
}
```

### cout precision
```cpp
cout << fixed;

cout << setprecision(n);
```