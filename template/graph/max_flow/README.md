## 최소 컷 찾기
```cpp
queue<int> q;
q.push(0);
while(q.size()) {
  int cur = q.front();
  q.pop();
  if(visited[cur]) continue;
  visited[cur] = true;
  for(auto& i : flow.edges[cur]) if(i.cap > i.flow) q.push(i.loc);
}
```