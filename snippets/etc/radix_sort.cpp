template <random_access_iterator I>
requires integral<iter_value_t<I>>
void radix_sort(I s, I e) {
  using T = iter_value_t<I>;
  using U = make_unsigned_t<T>;
  constexpr int bits = sizeof(T) * 8;
  constexpr U sign = U(1) << bits - 1;

  size_t sz = distance(s, e);
  vector<T> tmp1(s, e), tmp2(sz);
  if constexpr (signed_integral<T>) for(T& i : tmp1) i = T(U(i) ^ sign);
  for(int t = 0;t < bits;t += 8) {
    size_t cnt[256]{};
    for(size_t i = 0;i < sz;i++) cnt[(U(tmp1[i]) >> t) & 255]++;
    for(int i = 1;i < 256;i++) cnt[i] += cnt[i - 1];
    for(size_t i = sz;i--;) tmp2[--cnt[(U(tmp1[i]) >> t) & 255]] = tmp1[i];
    swap(tmp1, tmp2);
  }
  transform(tmp1.begin(), tmp1.end(), s, [](const T& i) {
    if constexpr (signed_integral<T>) return T(U(i) ^ sign);
    else return i;
  });
}