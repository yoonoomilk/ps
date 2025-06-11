int in[100005], out[100005];

void ett(int cur) {
  in[cur] = ++ettn;
  for(int i : raw[cur]) if(!in[i]) ett(i);
  out[cur] = ettn;
}

int arr[200005], in[100005], out[100005];

void ett(int cur, int pa) {
  arr[ettn] = cur;
  in[cur] = ettn++;
  for(int i : raw[cur]) if(i != pa) ett(i, cur);
  arr[ettn] = cur;
  out[cur] = ettn++;
}

void ett(int cur, int pa) {
  arr[ettn] = cur;
  cnt[cur][0]++;
  in[cur] = ettn++;
  for(int i : raw[cur]) if(i != pa) {
    ett(i, cur);
    arr[ettn++] = cur;
    cnt[cur][0]++;
  }
  arr[ettn] = cur;
  cnt[cur][0]++;
  out[cur] = ettn++;
}