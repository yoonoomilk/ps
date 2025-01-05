```cpp
using pt = pair<int, int>;
#define x first
#define y second
```

# I/O stream
```cpp
istream &operator >> (istream &cin, pt &v) { cin >> v.x >> v.y; return cin; }

ostream &operator << (ostream &cout, pt &v) { cout << v.x << ' ' << v.y; return cout; }
```

# calculate
```cpp
pt operator + (pt &a, pt &b) { return {a.x + b.x, a.y + b.y}; }

pt operator - (pt &a, pt &b) { return {a.x - b.x, a.y - b.y}; }

pt operator += (pt &a, pt &b) {
  a.x += b.x;
  a.y += b.y;
  return a;
}

pt operator -= (pt &a, pt &b) {
  a.x -= b.x;
  a.y -= b.y;
  return a;
}
```