## 다익스트라
```cpp
pq.push({0, s});
dist[s] = 0;
while(pq.size()) {
  auto [d, cur] = pq.top();
  pq.pop();
  if(d == dist[cur]) for(auto [nxt, dd] : edges[cur]) if(dist[nxt] > d + dd) pq.push({dist[nxt] = d + dd, nxt});
}
```

## SPFA
```cpp
q.push(s);
inq[s] = true;
while(q.size()) {
  int cur = q.front();
  q.pop();
  inq[cur] = false;
  if(++cnt[cur] >= n || dist[cur] < -INF) // cycle
  for(auto [nxt, dd]) if(dist[cur] + dd < dist[nxt]) {
    dist[nxt] = dist[cur] + dd;
    if(!inq[nxt]) {
      q.push(nxt);
      inq[nxt] = true;
    }
  }
}
```