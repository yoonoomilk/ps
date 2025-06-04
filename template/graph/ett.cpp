vector<int> raw[100005];
int ett[200005], dfsn;
int dep[100005], in[100005];

void dfs(int cur, int d) {
  dep[cur] = d;
  ett[dfsn] = cur;
  in[cur] = dfsn++;
  for(int i : raw[cur]) {
    if(dep[i]) continue;
    dfs(i, d + 1);
    ett[dfsn++] = cur;
  }
}

dfs(1, 1);