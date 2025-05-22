template <typename T>
class manacher {
  const int sz;
  vector<T> str;

public:
  vector<int> arr;

  template <typename I>
  manacher(I s, I e) : sz(distance(s, e) * 2 + 1), arr(sz), str(sz, '\0') {
    for(int i = 1;s != e;i += 2) str[i] = *s++;
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
  }
};