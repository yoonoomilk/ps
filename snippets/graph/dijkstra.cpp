auto dijkstra(int n, auto& edges, int s) {
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
  vector<ll> dist(n, LLONG_MAX);
  pq.push({0, s});
  dist[s] = 0;
  while(pq.size()) {
    auto [d, cur] = pq.top();
    pq.pop();
    if(d != dist[cur]) continue;
    for(auto [nxt, dd] : edges[cur]) if(dist[nxt] > d + dd) {
      dist[nxt] = d + dd;
      pq.push({dist[nxt], nxt});
    }
  }
  return dist;
}