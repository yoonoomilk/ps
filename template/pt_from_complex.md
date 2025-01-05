```cpp
using pt = complex<int>;
#define x real()
#define y imag()
```

# I/O stream
```cpp
istream &operator >> (istream &cin, pt &v) {
  int a, b; cin >> a >> b;
  v = pt(a, b);
  return cin;
}

ostream &operator << (ostream &cout, pt &v) { cout << v.x << ' ' << v.y; return cout; }
```

# calculate
```cpp
bool operator < (pt &a, pt &b) { return (a.x != b.x) ? a.x < b.x : a.y < b.y; }
```

# to remember
* find 함수는 `<complex>` 헤더에 포함되어 있으니 사용에 주의!