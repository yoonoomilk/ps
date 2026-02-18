template <typename T, typename Cmp = less<T>>
class eraseable_pq {
  priority_queue<T, vector<T>, Cmp> pq, del;
  void flush() { while(del.size() && pq.top() == del.top()) pq.pop(), del.pop(); }
public:
  eraseable_pq() {}
  size_t size() { return pq.size() - del.size(); };
  void insert(const T& v) { pq.push(v); flush(); }
  void erase(const T& v) { del.push(v); flush(); }
  void pop() { del.pop(); flush(); }
  const T& top() { return pq.top(); }
};