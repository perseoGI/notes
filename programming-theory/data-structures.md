# Data structures

## Links

- [BigOCheatsheet](https://www.bigocheatsheet.com/)
- [8 common data structures](https://towardsdatascience.com/8-common-data-structures-every-programmer-must-know-171acf6a1a42)

## Basic data structure

### Record / Struct

Heterogeneous collection of data

### Abstract Data Type (ADT)

Collection of data and operations on that data (methods)

## Array

Fixed size

- Applications:
  - Build other Data Structures (array list, vector, heap, hash table, matrix)
  - Sorting algorithms: insertion sort, quick sort, bubble sort, merge sort
- Operations:
  - Access: O(1)
  - Search: O(N)
  - Update: O(N)
  - Insert and delete: needs copy of hole array O(N)

## Linked List

Sequential structure of items in linear order linked to each other

- Types:
  - Single linked list
  - Doubly linked list
  - Circular linked list
- Operations:
  - Traverse: O(N)
  - Search: O(N)
  - Insert: O(1)
  - Delete: O(1)

## Stack

Last In First Out

- Operations:
  - Push / Insert: O(1)
  - Pop / Delete: O(1)
  - Peek: O(1)
  - Access: O(N)
  - Search: O(N)
- Applications:
  - Function call in recursion programming
  - Evaluate mathematical expressions

## Queue

First In First Out

- Operations:
  - Enqueue / Insert: O(1)
  - Dequeue / Delete: O(1)
  - Access: O(N)
  - Search: O(N)
- Applications:
  - Manage threads in multithreading
  - Priority queue

## Hash Table

Store pair of key-value entries
Make use of Hash Function in order to overcome direct addressing problem (limited space)
This will map any key to a table index -> O(1)
Collisions may occur when hash function gives same table index for two
different entries

Solve collisions: structure table as an array of linked list (or other Data
Structure) Access array is always O(1). If there is no collision in that
position, access to value will be O(1).  If there are collisions, search in
that linked list O(N)

- Operations (average case) vs all O(N) in worst case
  - Access: O(1)
  - Search: O(1)
  - Insert: O(1)
  - Delete: O(1)

- Applications:
  - Database indexes
  - Associative arrays (dictionaries)
  - Implement Set data structure

## Tree

Hierarchal structure where data are organized hierarchically and linked together

- Types:
  - Binary Search Tree (BST)
  - B-tree: BST with more than two children
  - Treaps: wireless networking
  - Red-Black tree: self balanced BST with two colors. Worst case O(logN) for
    all operations
  - Splay tree
  - AVL tree: Adelson-Velsky and Landis. Self balancing binary search tree in
    which the height of two child subtrees of any node differ by at most one
    (worst case all O(logN))
  - N-ary tree

- Operations: (in worst case, all O(N))
  - Access: O(logN)
  - Search: O(logN)
  - Insert: O(logN)
  - Delete: O(logN)

## Binary Search Tree (BST)

- Store data in sorted order
- `left < root < right`
- Applications:
  - Expression parsers
  - Search applications where data are entering and leaving

### Heap

Binary tree where parent nodes are compared with children and arranged accordingly

- Types:
  - Min-Heap: root will be lowest node
  - Max-Heap: root will be higher node
- Operations:
  - Search: O(N)
  - Insert: O(1) - O(logN) needs to balance until satisfies condition
  - Find min/max: O(1)
  - Delete min/max: O(logN)
- Applications:
  - JVM to store Java Objects
  - Heap sort algorithm
  - Priority queues
  - Find the k-th smallest/biggest value in an array
      `
             1
           /   \
          2     3
        /   \ /   \
       4    5 6    7
      `
      Array representation:
      [1, 2, 3, 4, 5, 6, 7]


## Graph

Finite set of vertices or nodes and set of edges connecting these vertices.

- Order: number of vertices
- Size: number of edges
- Adjacent nodes: connected by same edge
- Isolated node: non connected to any other graph
- Cycle: path where start and end node are the same
- Simple path: nodes appear only once
- Connected: exist a path between any two nodes
- Component: connected parts of a graph
- Tree: connected graph with n nodes and n-1 edges (only exist a unique path between any two nodes)
- Directed graph: paths can be traversed only in one direction
- Weighted graph: each edge of the graph has a value (distance or cost typically)
- Neighbor of node: any node which is adjacent to the node (edge between them)
- Degree of node: number of node neighbors

- Sum of degrees in graph: 2m (m = number of edges)
- Regular graph: degree of each node is a constant
- Complete graph: degree of each node is n - 1 (n = number of nodes)

Directed graph:
- Indegree: number of edges which ends in the node
- Outdegree: number of edges that start at the node

- Coloring: assign each node a color so no adjacent nodes have same color
- Bipartite graph: only two colors required to color the graph
  - When not contain a cycle with an odd number of edges
- Simple graph: there is no edges starting and ending in same node and any two nodes have more than one edge connecting each other

- Types:
  - Directed Graph: all edges has a direction (start, end)
  - Undirected Graph: all edges has no direction
- Applications:
  - Social media networks
  - Represent web pages and links by search engines -> page ranking in Google
  - Locations and routes in GPS -> calculate shortest route between two nodes
