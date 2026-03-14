ll parametric_min(ll l, ll r, auto f) {
  assert(f(l) == false && f(r) == true);
  return *ranges::lower_bound(views::iota(l, r + 1), 0, [&](ll i, int) { return !f(i); });
}

ll parametric_max(ll l, ll r, auto f) {
  assert(f(l) == true && f(r) == false);
  return *ranges::lower_bound(views::iota(l, r + 1), 0, [&](ll i, int) { return f(i); }) - 1;
}