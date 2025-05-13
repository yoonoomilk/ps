vector<int> raw[100005];
int dep[100005];
int pa[100005][17];

void dfs(int x, int p) {
  pa[x][0] = p;
  dep[x] = dep[p] + 1;
  for(int i : raw[x]) if(i != p) dfs(i, x);
}

int lca(int a, int b) {
  if(dep[a] < dep[b]) swap(a, b);
  for(int i = 0, d = dep[a] - dep[b];i < 17;i++) {
    if(d & (1 << i)) a = pa[a][i];
  }
  if(a == b) return a;
  for(int i = 16;i >= 0;i--) if(pa[a][i] != pa[b][i]) {
    a = pa[a][i];
    b = pa[b][i];
  }
  return pa[a][0];
}

dfs(1, 0);
for(int i = 1;i < 17;i++) for(int j = 1;j <= n;j++) pa[j][i] = pa[pa[j][i - 1]][i - 1];