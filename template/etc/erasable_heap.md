# 코드
```cpp
template<typename T, typename Compare = less<T>>
class erasable_heap {
  priority_queue<T, vector<T>, Compare> pq, del;

  void organize() {
    while(del.size() && pq.top() == del.top()) {
      pq.pop();
      del.pop();
    }
  }

public:
  erasable_heap() {}

  size_t size() {
    return pq.size() - del.size();
  }

  void insert(const T& v) {
    pq.push(v);
    organize();
  }

  void erase(const T& v) {
    del.push(v);
    organize();
  }

  T top() {
    return pq.top();
  }
};
```

## 참고
이미 `insert`한 값만 `erase` 할 수 있음. 없는 값을 `erase`하면 undefined behavior.

# 문제
* [이중 우선순위 큐](https://boj.kr/7662)