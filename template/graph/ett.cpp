int in[100005], out[100005];

void dfs(int cur) {
  in[cur] = dfsn++;
  for(int i : raw[cur]) if(!in[i]) dfs(i);
  out[cur] = dfsn;
}

int arr[200005], in[100005], out[100005];

void dfs(int cur, int pa) {
  arr[dfsn] = cur;
  in[cur] = dfsn++;
  for(int i : raw[cur]) if(i != pa) dfs(i, cur);
  arr[dfsn] = cur;
  out[cur] = dfsn++;
}

void dfs(int cur, int pa, int d) {
  dep[cur] = d;
  arr[dfsn] = cur;
  in[cur] = dfsn++;
  for(int i : raw[cur]) if(i != pa) {
    dfs(i, cur, d + 1);
    arr[dfsn++] = cur;
  }
  out[cur] = dfsn - 1;
}