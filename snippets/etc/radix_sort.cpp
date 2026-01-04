template <typename I>
void radix_sort(I s, I e) {
  for(int t = 0;t < 32;t += 8) {
    queue<int> q[256];
    for(I it = s;it != e;++it) q[((*it) >> t) & 255].push(*it);
    I cur = s;
    for(int i = 0;i < 256;i++) for(;q[i].size();q[i].pop()) *cur++ = q[i].front();
  }
  stable_partition(s, e, [](int a){ return a < 0; });
}