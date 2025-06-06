vector<int> raw[1005];
int cap[1005][1005], flow[1005][1005];
int bef[1005];
int s, e;
int ans;

while(1) {
  memset(bef, -1, sizeof bef);
  queue<int> q;
  q.push(s);
  while(q.size()) {
    int cur = q.front();
    q.pop();
    for(int i : raw[cur]) if(cap[cur][i] > flow[cur][i] && bef[i] == -1) {
      bef[i] = cur;
      q.push(i);
      if(i == e) break;
    }
  }
  if(pre[e] == -1) break;
  int tmp = 1e9;
  for(int i = e;i != s;i = bef[i]) tmp = min(tmp, cap[bef[i]][i] - flow[bef[i]][i]);
  for(int i = e;i != s;i = bef[i]) {
    flow[bef[i]][i] += tmp;
    flow[i][bef[i]] -= tmp;
  }
  ans += tmp;
}