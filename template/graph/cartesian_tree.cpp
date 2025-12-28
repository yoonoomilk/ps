template <typename I, typename Compare>
auto cartesian_tree(I s, I e, Compare cmp = less<>()) {
  int n = distance(s, e);
  vector<int> pa(n, -1);
  stack<int> st;
  for(int i = 0;i < n;i++) {
    int j = -1;
    while(st.size() && cmp(s[i], s[st.top()])) {
      j = st.top();
      st.pop();
    }
    if(j != -1) pa[j] = i;
    if(st.size()) pa[i] = st.top();
    st.push(i);
  }
  while(st.size() > 1) st.pop();
  return pair{pa, st.top()};
}