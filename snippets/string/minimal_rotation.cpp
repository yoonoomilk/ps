// https://en.wikipedia.org/wiki/Lexicographically_minimal_string_rotation

string minimal_rotation(string s) {
  int n = s.size();
  vector<int> idx(n * 2, -1);
  int k = 0;
  for(int j = 1;j < n * 2;j++) {
    int i = idx[j - k - 1];
    for(;i != -1 && s[j % n] != s[(k + i + 1) % n];i = idx[i]) {
      if(s[j % n] < s[(k + i + 1) % n]) k = j - i - 1;
    }
    if(i == -1 && s[j % n] != s[(k + i + 1) % n]) {
      if(s[j % n] < s[(k + i + 1) % n]) k = j;
      idx[j - k] = -1;
    } else idx[j - k] = i + 1;
  }
  rotate(s.begin(), s.begin() + k % n, s.end());
  return s;
}