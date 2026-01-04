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
  if(dep[a] > dep[b]) s1 = op(seg(in[b], in[a]), s1);
  else s2 = op(seg(in[a], in[b]), s2);
  // reverse s1
  return op(s1, s2);
}
```

## edge instead of vertex
```cpp
void update(int a, int b, T v) {
  if(dep[a] < dep[b]) swap(a, b);
  seg.update(in[a], v);
}

seg.update(in[a] + 1, in[b], v);

return op(s, seg(in[a] + 1, in[b]));
```