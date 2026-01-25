#include "string/suffix_array-nlogn.cpp"

string bwt(string_view s){
  int n = s.size();
  auto suf = get<1>(suffix_array(s));
  string tmp(n, '\0');
  for(int i = 0;i < suf.size();i++) tmp[i] = s[(suf[i] + n - 1) % n];
  return tmp;
}