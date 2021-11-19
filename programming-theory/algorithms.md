# Algorithms

## Sorting Algorithms

### Bubble sort

O(n^2)

```cpp
for (int i = 0; i < n; ++i)
  for(int j = 0; j < n - 1; ++j)
    if (arr[j] > arr[j + 1])
      swap(arr[j], arr[j + 1]);
```

### Merge sort

O(n log(n))

TODO

Sorting lower bound: n logn

### Counting sort

Only for arrays where arr[i] in 0..c and c = O(n)

```cpp
int bookkeeping[n] = {0};
vector<int> ordered;

// 1. Create bookkeeping array with frequencies of each element
for (int i = 0; i < n; ++i){
  ++bookkeeping[arr[i]];
}

// Create result array
for (int i = 0; i < n; ++i){
  fill_n(back_inserter(ordered), bookkeeping[i], i);
}
```

### C++ sort

Always better than implementing your sorting algorithm.

```cpp
sort(v.begin(), v.end());
sort(v.rbegin(), v.rend()); // Reverse order

// If pair or tuple, will compare from left to right if it is smaller

// User defined structs needs to implement a operator<

// Also a comparator function can be passed to sort

bool comp(string a, string b){
  if(a.size() != b.size()) return a.size() < b.size(); // size comparator
  return a < b; // standard lexicographic comparator
}
string s ("hello");
sort(s.begin(), s.end(), comp);
```

## Search algorithms

### Input not sorted

Best time complexity = O(n) -> linear iteration

### Sorted Input

#### Binary search

O(log(n))

```cpp
int l = 0, r = arr.size(), m;

while (l <= r){
  m = (l + r) / 2;
  if (arr[m] == x)      // found
  else if (arr[m] > x)  r = m - 1;
  else                  l = m + 1;
}
```

O(log(n)) but more efficient, make jumps and slow speed when reaching x

```cpp
int k = 0;

for (int jumpLength = n / 2; jumpLength >= 1; jumpLength /= 2){
  while (k + jumpLength < n && arr[k + jumpLength] <= x)  k += jumpLength;
}

if (arr[k] == x) // found
```

### C++

```cpp

// Assuming sorted array
// lower_bound -> pointer to first element whose value is at least x
// upper_bound -> pointer to first element whose value is at larger than x
// equal_range -> both pointers

auto a = lower_bound(arr, arr + n, x) - arr;
if(a < n && arr[a] == x) // found

auto b = upper_bound(arr, arr + n, x) - arr;

// number of elements whose value is x
cout << b - a << '\n';

auto r = equal_range(array, array + n, x);
cout << r.second - r.first << '\n';

```

#### Find smallest solution

```
Given a function ok(n) which
  false when n < k
  true when n >= k
```

```cpp
int x = -1;
for (int b = z; b >= 1; b /= 2){
  while (!ok(x+b)) x += b;
}
int sol = x + 1;
```

#### Find max value of function (firt increase then decrease)

Not repeated values are allowed

```
f (x) < f (x+1) when x < k, and
f (x) > f (x+1) when x ≥ k.
```

```cpp

int x = -1;
for (int b = z; b >= 1; b /= 2) {
  while (f(x+b) < f(x+b+1)) x += b;
}
int sol = x+1;
```

## Complete search

### Generate all combinations

O(2^n)

Bitset way

```cpp
vector<set<int>> generateAllSubsets(const vector<int> &vec){
  int n = vec.size();
  vector<set<int>> subsets;
  for (int b = 0; b < (1 << n); ++b){
    set<int> subset;
    for (int i = 0; i < n; ++i)
      if (b & (1 << i)) subset.insert(vec[i]);
    subsets.push_back(subset);
  }
  return subsets;
}
```

Recursive way

```cpp
vector<int> subsets;
void search(int k, int n){
  if (k == n){
    PRINT_VEC(subsets);
  }
  else{
    search(k + 1, n);
    subsets.push_back(k);
    search(k+1, n);
    subsets.pop_back();
  }
}

int n = 3;  // Generate until number 3
search(0, n);
```

### Generate all permutations

O(n!)

C++ way

```cpp
vector<int> permutations {1, 3, 4, 42};

do {
  // process permutation
} while(next_permutation(permutations.begin(), permutations.end));
```

Recursive way

```cpp
vector<int> permutations {1, 3, 4, 42};
vector<bool> chosen(n, false);

void search() {
  if (permutations.size() == n) {
    // process permutation
  }
  else {
    for (int i = 0; i < n; i++) {
      if (chosen[i]) continue;
      chosen[i] = true;
      permutations.push_back(i);
      search();
      chosen[i] = false;
      permutations.pop_back();
    }
  }
}

```

### Backtracking

Begins with empty solution and extends the solution step by step.
Recursively search through all different ways a solution can be constructed.

**Very important to prune the search**, specially on the first iterations.
Pruning means to cancel a search when a partial solution cannot be extended to
complete solution.

## Greedy algorithms

Construct a solution by always making the best choice possible in each step
and never backtracking.
Pretty efficient but hard to design and harder to theoretically ensure it will
always works.

### Minimizing sum

```
Given:
|a1 - x| + |a2 - x| + |a2 - x| + ... + |an - x|

Choose x to minimize sum -> x = median of numbers
```

```
Given:
(a1 - x)^2 + (a2 - x)^2 + (a2 - x)^2 + ... + (an - x)^2

Choose x to minimize sum -> x = average of numbers
```


### Huffman coding

Greedy algorithm that constructs an optimal code for compressing a string by
building a binary tree based on the frequencies of the characters in the
string.

Each character codeword can be read by following a path from root to the
corresponding node.

Moves to left: bit 0
Moves to right: bit 1


TODO

## Dynamic Programming

Combines correctness of complete search and the efficiency of greedy algorithms
by dividing into overlapping subproblems that can be solved independently.

It will go through all possibilities but using memoization (calculates answer
of each subproblem once)

### Finding optimal solution

Given an array of different coins, return the minimum number  of coins to sum
an amount.

```
coinCalc(x):
  INF                                           if x < 0
  0                                             if x = 0
  min(coinCalc(x - c) + 1) forEach c in Coins   if x > 0
```

Recursive way:

```cpp
map<int, int> r_historic;
int coinChange(vector<int>& coins, int amount) {
    int res = coinCalc(coins, amount);
    return  res == INF? -1 : res;
}
int coinCalc(const vector<int> &coins, int target) {
    if (r_historic.count(target) == 1) return r_historic[target];
    if (target < 0) return INF;
    if (target == 0) return 0;
    int best = INF;
    for (int coin : coins){
        best = min(best, coinCalc(coins, target - coin) + 1);
    }
    // Memoization
    r_historic[target] = best;
    return best;
}
```

Iterative way (much more efficient):

```cpp
int coinChange(vector<int>& coins, int amount) {
    vector<int> values(amount + 1);

    values[0] = 0;
    for(int i = 1; i <= amount; ++i){
        values[i] = INF;
        for(int coin : coins){
            if (i - coin >= 0){
                values[i] = min(values[i], values[i - coin] + 1);
            }
        }
    }
    return values[amount] == INF? -1 : values[amount];
}
```

### Counting number of solutions

Same problem but get all total solutions:

```
coinCalc(x):
  INF                                       if x < 0
  1                                         if x = 0 (no other solution but empty)
  min(coinCalc(x - c)) forEach c in Coins   if x > 0
```

```cpp
int coinChange(vector<int>& coins, int amount) {
    vector<int> count(amount + 1);

    count[0] = 1;
    for(int i = 1; i <= amount; ++i){
        for(int coin : coins){
            if (i - coin >= 0){
                count[i] = min(count[i], count[i - coin]);
            }
        }
    }
    return count[amount] == INF? -1 : count[amount];
}
```

### Paths in grid

```cpp
int grid[N][N];
int sum[N][N];

int sum(int x, int y){
  if (x == 0 || y == 0){
    return 0;
  }
  if (sum[x][y] != 0){
    return sum[x][y];
  }
  int res = max(sum(x-1, y), sum(x, y-1)) + grid[x][y];
  sum[x][y] = res;
  return res;
}


```

### Knapsack problem

Given an array of numbers, return boolean array with true position on valid
index as sum of any possible combination of elements.

O(nW) with W total sum of array

```cpp
int n = 3;
vector<int> arr {1, 5, 8};
int W = accumulate(arr.begin(), arr.end(), 0);
vector<bool> possible(W, false);

// possible(x, k) = possible(x - w_k, k - 1) or possible(x, k - 1)
possible[0] = true;
for (int k = 0; k < n; ++k){
  for (int x = W - 1; x >= 0; --x){
    if(possible[x] && x + arr[k] < W) possible[x + arr[k]] = true;
  }
}
```


### Two pointer method

### 3SUM Problem

Two pointer problem applied to 3 pointers.
Find 3 different numbers in nums that sums target.

```cpp
vector<vector<int>> threeSum(vector<int>& nums, target) {
    sort(nums.begin(), nums.end());

    int n = nums.size() - 1;
    int l = 0;
    int r = n;
    int c = r / 2;
    int sum;

    while (c != 0 and c != n){
        sum = nums[l] + nums[c] + nums[r];
        if (sum == target){
            return vector<int>{nums[l], nums[c], nums[r]};
        }
        if(sum > target){
            --r;
            if (r == c){
                r = n;
                --c;
            }
        }
        if(sum < target){
            ++l;
            if (l == c){
                l = 0;
                ++c;
            }
        }
    }

    return vector<int>();
}
```

### Minimum sliding window

TODO

## Range queries

Calculate a value based on a subarray of an array.

If we only have to calculate a value once (one query), O(n) is best we can
achieve.

Multiple query problems can be solved by preevaluating an static array with all
answers for any possible query.

### Sum queries

Construct array of sums until k-th position -> O(n)

sum(0, k): sum from 0 to k index

Queries can be performed as:

sum(a, b) = sum(0, b) - sum(0, a - 1)


### Binary Indexed Tree / Fenwick Tree

Dynamic variant of prefix sum array (above).
O(log n):

- Range sum query
- Updating value

Compared with Segment Tree, Binary Indexed Tree requires less space and is
easier to implement.

tree[k] = sum(k - p(k) + 1, k)
p(k) = largest power of 2 that divides k (easily achieved by k & -k)

```cpp
class BinaryIndexedTree {
public:
  BinaryIndexedTree(const vector<int> &vec): r_len(vec.size() + 1){
    r_arr.resize(r_len, 0);
    for (int i = 0; i < r_len - 1; ++i){
      update(i, vec[i]);
    }
  }

  void update(int index, int value){
    ++index; // needs 1 more space
    while (index <= r_len){
      r_arr[index] += value;
      index += index & -index;
    }
  }

  int querySumRange(int a, int b){
    return getSum(b) - getSum(a - 1);
  }

  int getSum(int k){
    int res = 0;
    while(k >= 1){
      res += r_arr[k];
      k -= k & -k;
    }
    return res;
  }

  friend ostream & operator<<(ostream& os, const BinaryIndexedTree &bit){
    string res;
    for (int i = 1; i < bit.r_len; ++i){
      res += to_string(bit.r_arr[i]) + " ";
    }
    return os << res;
  }

private:
  vector<int> r_arr;
  int r_len;
};
```

#### Segment tree

Support sum, maximum, minimum, mcd, etc. queries but requieres more memory than BIT.

TODO

#### Range updates

Increase / decrease a range of an array by given value.

Work with *difference array*: array representing the difference between values

3 3 1 1 1 5 2 2

Diff array:

3 0 -2 0 0 4 -3 0

Value at index = sum(diff[0], diff[i])

Modify range[a, b]:
diff[a]     += value
diff[b + 1] -= value

## Graphs

### Representation

#### Adjacent list

Advantage: find / move between all nodes adjacent of current node

```cpp
int N; // Number of nodes
vector<int> adj[N]
adj[0].push_back(2);  // 0 node is connected to 2
```

If undirected graph, each edge is added in both directions.

Weighted graph (b, w)

```cpp
vector<pair<int,int>> adj[N];
```

#### Adjacent matrix

PRO: check if two nodes are connected
CONS: space complexity is O(n^2) and most of elements are 0 (cant be used for large graphs)

```cpp
bool adj[N][N];
adj[0][2] = true;  // 0 node is connected to 2

// Or weighted graph

int adj[N][N];
adj[0][2] = 42;   // 42 is the weight of edge between 0 and 2
adj[0][1] = 0;    // 0 and 1 are not connected
```

#### Edge list representation

Useful when algorithm needs to process all edges of a graph and in is NOT needed
to find edges that start at a given node.

```cpp
vector<pair<int,int>> edges;
edges.push_back({0, 2});   // 0 is connected to 2

// Or weighted graph
vector<tuple<int,int,int>>> edges;
edges.push_back({0, 2, 42});
```

### Graph traversal

#### Deep First Search (DFS)

O(n + m)  (n = number of nodes and m = number of edges)

```cpp
vector<int> adj[N];     // adjacent list representation
vector<bool> visited(N, false);

void dfs(int s){
  if (visited[s]) return;
  visited[s] = true;

  // Process node s

  for (auto node : adj[s]){
    dfs(node);
  }
}
```

Adjacent matrix DFS:

```cpp
int adj[N][N];
vector<bool> visited(N, false);

void dfs(int s){
  if (visited[s]) return;
  visited[s] = true;
  // Process node
  for(auto node : adj[s]){
    if (node != 0){
      dfs(node);
    }
  }
}
```

#### Breadth First Search (BFS)

O(n + m)

Visit the nodes in increasing order of their distance from starting node.
PRO: calculate distances from starting node to all other nodes.

```cpp
vector<int> adj[N];
queue<int> q;
bool visited[N];
int distance[N];

int s = 0; // starting node
visited[s] = true;
distance[s] = 0;
q.push(s);

while (!q.empty()){
  int node = q.front(); q.pop();

  // Process node

  for (auto u : adj[node]){
    if(visited[node]) continue;
    visited[u] = true;
    distance[u] = distance[node] + 1;
    q.push(u);
  }
}
```

#### Applications

##### Get graph components

In this case, nodes could have any value so an array/vector could not be used
to index.

```cpp
class Graph {
  public:
    Graph(vector<vector<int>> edges) {
        for(vector<int> edge : edges){
            if (adj.count(edge[0]) == 0)
                adj[edge[0]] = {edge[1]};
            else adj[edge[0]].push_back(edge[1]);

            if (adj.count(edge[1]) == 0)
                adj[edge[1]] = {edge[0]};
            else adj[edge[1]].push_back(edge[0]);
        }

        // Initiate visited map
        for (auto e : adj){
            visited[e.first] = 0;
        }
    }

    void dfs(int s, int componentIndex){
        if(visited[s] != 0) return;
        visited[s] = componentIndex;

        for(auto node : adj[s])
            dfs(node, componentIndex);
    }
    vector<vector<int>> getComponents(){
        vector<vector<int>> components;
        int s;
        int componentIndex = 1;
        while((s = getNextNonVisitedNode()) != -1){
            dfs(s, componentIndex);
            vector<int> iComponents;
            for(pair<int,int> v : visited)
                if (v.second == componentIndex)
                    iComponents.push_back(v.first);
            if(iComponents.size() > 0)
                components.push_back(iComponents);
            ++componentIndex;
        }
        return components;
    }

    int getNextNonVisitedNode(){
        for(pair<int,int> v : visited)
            if (v.second == 0)
                return v.first;
        return -1;
    }

  private:
    unordered_map<int, vector<int>> adj;
    unordered_map<int, int> visited;
};
```

##### Find cycles

TODO

##### Bipartiteness check

TODO

### Shortest paths

#### Bellman-Ford algorithm

Calculate minimum distance from starting node to all other nodes

Limitation: there cant be a negative cycle in the graph because it could loop
infinitely.

O(n*m)

```cpp
vector<tuple<int,int,int>> edges = {
  {0, 1, 5},
  {0, 2, 3},
  {0, 3, 7},
  {1, 3, 3},
  {2, 3, 1},
  {1, 4, 2},
  {3, 4, 2}
}; // (a, b, weight)
int N = 5;
vector<int> distances(N, INT_MAX);

int s = 0; // starting node (could be any)
int a, b, w;

distances[s] = 0;

bool distanceReduced = true; // if no distance were reduced on a round, finish
for (int i = 1; i < N - 1 && distanceReduced; ++i){
  distanceReduced = false;
  for (auto e : edges){
    tie(a, b, w) = e;
    int distance = min(distances[b], distances[a] + w);
    if (distance < distances[b]){
      distances[b] = distance;
      distanceReduced = true;
    }
  }
}
```

Bellman-Ford can be used to detect negative cycles.
If in the Nth iteration still decrease any distance, it means that there is a
negative cycle.

```cpp
bool distanceReduced = true; // if no distance were reduced on a round, finish
for (int i = 1; i < N; ++i){
  distanceReduced = false;
  for (auto e : edges){
    tie(a, b, w) = e;
    int distance = min(distances[b], distances[a] + w);
    if (distance < distances[b]){
      distances[b] = distance;
      distanceReduced = true;
      if(i == N - 1){
        // Negative cycle found!
      }
    }
  }
}
```

#### Disktra's algorithm

More efficient than Bellman-Ford but input graph must NOT contain negative weights.
It only process each edge once.

```cpp
int N = 5;
vector<pair<int,int>> adj[] = {
  {{1, 5}, {3, 9}, {4, 1}},
  {{0, 5}, {2, 2}},
  {{1, 2}, {3, 6}},
  {{0, 9}, {2, 6}, {4, 2}},
  {{0, 1}, {3, 2}}
};   // (b, w)
vector<int> distances(N, INT_MAX);
vector<bool> processed(N, false);
priority_queue<pair<int,int>> q;

int s = 0; // start node
distances[s] = 0;
q.push({0, s});
int b, w;

while (!q.empty()){
  int a = q.top().second; q.pop();
  if (processed[a]) continue;
  processed[a] = true;
  for (pair<int,int> edge : adj[a]){
    tie(b,w) = edge;
    if (distances[b] > distances[a] + w){
      distances[b] = distances[a] + w;
      q.push({-distances[b], b});
    }
  }
}
```

#### Floyd-Warshall algorithm

Find all shortest path between the nodes in a single run.
2D array with all distances between nodes.

1. Distances calculated using direct edges.
2. Algorithm reduce distances by using intermediate nodes.

TODO

### Trees

Acyclic graph with no isolated nodes.

#### Traversal

```cpp
dfs(x, 0);

void dfs (int s, int parent){
  // Visit node
  for (auto u : adj[start]){
    if (u != parent) dfs(u, s);
  }
}
```

#### Number of nodes in subtree

```cpp
int count[N];

void dfs(int s, int parent){
  count[s] = 1;
  for (auto u : adj[s]){
    if (u != parent) {
      dfs(u, s);
      coun[s] += count[u];
    }
  }
}
```

#### Diameter of tree

Path with maximum length

```cpp
int b;
dfs(0, 0);

void dfs(int s, int parent){

}
```

## Miscellanea

### Problems solutions

#### Get number of chars with odd frequency

```cpp
string s ("hello");

uint mask = 0;
for (char c : s)
  mask ^= 1 << (c - 'a'); // xor will put 1 if is even

return __builtin_popcount(mask); // C++ std::popcount()
```
