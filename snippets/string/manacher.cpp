vector<int> manacher(string_view s) {
  int sz = s.size() * 2 + 1;
  string str(sz, '\0');
  vector<int> arr(sz);
  for(int i = 1, j = 0;j < s.size();i += 2) str[i] = s[j++];
  int m = 0, r = 0;
  for(int i = 0;i < sz;i++) {
    int l = m * 2 - i;
    if(i < r) arr[i] = min(r - i, arr[l]);
    while(i - arr[i] - 1 >= 0 && i + arr[i] + 1 < sz && str[i - arr[i] - 1] == str[i + arr[i] + 1]) arr[i]++;
    if(i + arr[i] > r) {
      m = i;
      r = i + arr[i];
    }
  }
  return arr;
}