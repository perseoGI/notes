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

