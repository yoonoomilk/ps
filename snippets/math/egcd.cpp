// [g, x, y] = egcd(a, b), ax + by = g
auto egcd(ll a, ll b) {
  auto cur = tuple{a, 1LL, 0LL}, nxt = tuple{b, 0LL, 1LL};
  while(get<0>(nxt)) {
    ll d = get<0>(cur) / get<0>(nxt);
    tie(cur, nxt) = tuple{
      nxt,
      tuple{
        get<0>(cur) - d * get<0>(nxt),
        get<1>(cur) - d * get<1>(nxt),
        get<2>(cur) - d * get<2>(nxt)
      }
    };
  }
  return cur;
}