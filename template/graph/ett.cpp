vector<int> raw[100005];
int arr[100005], arrn;
int in[100005], out[100005];

void ett(int cur) {
  in[cur] = ++arrn;
  arr[arrn] = cur;
  for(int i : raw[cur]) if(!in[i]) ett(i);
  out[cur] = arrn;
}

ett(1);