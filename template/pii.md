```cpp
using pt = pair<int, int>;
#define x first
#define y second
istream &operator >> (istream &cin, pt &v) { cin >> v.x >> v.y; return cin; }
```
