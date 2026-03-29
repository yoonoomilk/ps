## max flow

### min cut
s~e 최소 컷 이후 s 쪽 정점 찾기
```cpp
queue<int> q;
q.push(s);
while(q.size()) {
  int cur = q.front();
  q.pop();
  if(visited[cur]) continue;
  visited[cur] = true;
  for(auto& i : flow.edges[cur]) if(i.left) q.push(i.loc);
}
```