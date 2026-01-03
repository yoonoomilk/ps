template <typename I>
void radix_sort(I s, I e) {
  for(int t = 0;t < 32;t += 8) {
    queue<int> q[256];
    for(I i = s;i != e;i++) q[((*i) >> t) & 255].push(*i);
    I cur = s;
    for(int i = 0;i < 256;i++) while(q[i].size()) {
      *cur++ = q[i].front();
      q[i].pop();
    }
  }
}