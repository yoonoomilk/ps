int cnt[100005];
pii csr[200005];

for(int i = 0;i < m;i++) {
  int a, b; cin >> a >> b;
  cnt[a]++;
  csr[i] = {a, b};
}
sort(csr, csr + m);

for(int i = 0;i < m;i++) {
  int a, b; cin >> a >> b;
  cnt[a]++, cnt[b]++;
  csr[i * 2] = {a, b};
  csr[i * 2 + 1] = {b, a};
}
sort(csr, csr + m * 2);

for(int i = 1;i <= n;i++) cnt[i] += cnt[i - 1];

for(int i = cnt[cur - 1];i < cnt[cur];i++)  {
  // nxt = csr[i].second
}