template <typename Func>
ll parametric_min(ll l, ll r, Func f = Func()) {
  assert(f(l) == false && f(r) == true);
  return *ranges::lower_bound(views::iota(l, r + 1), 0, [&](ll i, int _) { return !f(i); });
}

template <typename Func>
ll parametric_max(ll l, ll r, Func f = Func()) {
  assert(f(l) == true && f(r) == false);
  return *ranges::lower_bound(views::iota(l, r + 1), 0, [&](ll i, int _) { return f(i); }) - 1;
}