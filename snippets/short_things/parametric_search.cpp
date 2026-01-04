template <typename Func>
ll parametric_min(ll l, ll r, Func f = Func()) {
  return *ranges::lower_bound(views::iota(l, r + 1), 0, [&](int i, int _) { return !f(i); });
}

template <typename Func>
ll parametric_max(ll l, ll r, Func f = Func()) {
  return *ranges::lower_bound(views::iota(l, r + 1), 0, [&](int i, int _) { return f(i); }) - 1;
}