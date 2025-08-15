template <typename T, typename comp = greater<T>>
class eraseable_pq {
  priority_queue<T, vector<T>, comp> pq, del;

public:
  eraseable_pq() {}
  size_t size() { return pq.size() - del.size(); };
  void insert(T v) { pq.push(v); }
  void erase(T v) { del.push(v); }
  T top() {
    while(del.size() && pq.top() == del.top()) {
      pq.pop();
      del.pop();
    }
    return pq.top();
  }
}
