# C++ Data Structures

## vector

- push_back(T)
- pop_back(T)
- T front()
- T back()
- assign(n, val)
- insert(pos, startIt, endIt);
- erase(pos)

### Concatenate two vectors

```cpp
vector<int> v1;
vector<int> v2;

v1.insert(v1.end(), v2.begin(), v2.end());
```

### Declare and initialize two dimensional vector

m x n vector

```cpp
vector<vector<int>> vec (m, vector<int>(n, 42));
```

## dequeue

- ...vector
- push_front(T)
- pop_front()

## map

- insert(key, value)
- erase(key)
- int count(key) (max 1)
- it find(key)  O(log(N))

## multimap

- ...map
Find matches in multimap:
```cpp
multimap<int,int> mp;
auto eqr = boards.equal_range(val);
for (auto it = eqr.first; it != eqr.second; ++it) {}
```

## set / unordered_set

- insert(T)
- erase(pos) || erase(T)
- int count(T) (max 1)
- it find(T)

### Intersection

```cpp
set<T> s1, s2;
set<T> intersect;
set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(intersect, intersect.begin()));
```

## queue

- T front()
- T back()
- push(T)
- pop()

## stack

- T top()
- push(T)
- pop()

## priority_queue

Max heap by default (find and remove biggest element)

- push(T)  O(log(N))
- T top()  O(1)
- pop()    O(log(N))

```cpp
priority_queue<T> pq;
```

Min heap (needs to be declared `operator> T`)

```cpp
priority_queue<T, vector<T>, greater<T>> pq;
```

## String manipulations

- pos find('T')
- substr(startPos, endPos)
- erase(pos), erase(startPos, endPos)
-

## Common

- copy(startSource, endSource, startDest)

- copy_if(startSource, endSource, back_inserter(startDest), lambda_condition)

```cpp
copy_if(adj, adj + n, back_inserter(res), [](const vector<vector<int>> &v){
return v.size() == 1;
});
```
- reverse(begin, end)

- remove(startIt, endIt, val) -> iterator to last element

```cpp
vector<int> vec{1,2,3,4,5};
distance(vec.begin(), remove(vec.begin(), vec.end(), 4));
```

- Sum elements in vector
```cpp
int sum = accumulate(vec.begin(), vec.end(), 0);
```
