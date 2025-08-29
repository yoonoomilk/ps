## directional
```cpp
T operator() (int a, int b) {
  T s1 = raw, s2 = raw;
  while(top[a] != top[b]) {
    if(dep[top[a]] > dep[top[b]]) {
      s1 = op(seg(in[top[a]], in[a]), s1);
      a = pa[top[a]];
    } else {
      s2 = op(seg(in[top[b]], in[b]), s2);
      b = pa[top[b]];
    }
  }
  if(dep[a] > dep[b]) s1 = op(seg(in[a], in[b]), s1);
  else s2 = op(seg(in[a], in[b]), s2);
  // reverse s1
  return op(s1, s2);
}
```