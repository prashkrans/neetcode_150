/* LC#547. NCG15. Number of Provinces

Note: The given isConnected matrix is itself an adjacency matrix so
subset or visited array would be of size n (0 to n-1) not n^2

This is the simplest problem of the concept of connected components

Approaches:
1. DFS
2. BFS
3. Union Find Algo
*/

/*
### Approach 1: Depth-First Search (DFS) for Connected Components
1. Represent the graph as an adjacency matrix `isConnected`, where `isConnected[u][v]`
is 1 if there is a direct connection between nodes u and v.
2. Use a `visited` array to track which nodes have already been visited during the DFS
traversal.
3. Define a recursive DFS function:
   - Mark the current node as visited.
   - Iterate through all possible neighbors of the current node.
   - If a neighbor is connected and not visited, recursively call the DFS function for
that neighbor.
4. Iterate through all nodes in the graph:
   - If a node is not visited, it represents the start of a new connected component.
   - Perform a DFS traversal starting from that node to visit all nodes in the connected
component.
   - Increment the count of connected components.
5. Return the total number of connected components as the result.
6. Time Complexity:
   - The nested loop over the adjacency matrix takes O(n^2).
   - The DFS function is called once for each node, and each edge is traversed once.
   - Overall complexity is O(n^2).
7. Space Complexity:
   - The `visited` array requires O(n) space to track visited nodes.
   - The recursion stack can go as deep as the number of nodes in the worst case.
*/

// 1. DFS
// O(n*n) = O(n^2) | 0ms beats 100%
// O(n) due to the visited array and the recursion stack which is atmost n (max no. of neighbours of u)

class Solution {
    void dfs(int u, int n, vector<vector<int>> &isConnected, vector<int> &visited) {
        visited[u] = 1;                                // Mark the current node as visited
        for(int v = 0; v < n; v++) {                   // Iterate through all possible neighbors
            if(isConnected[u][v] == 1 && !visited[v]) {// If there's a connection and the neighbor is not visited
                dfs(v, n, isConnected, visited);       // Recursively visit the neighbor
            }
        }
    }
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int numOfConnectedComponents = 0;             // Initialize the count of connected components
        int n = isConnected.size();                   // Number of nodes in the graph
        vector<int> visited(n, 0);                    // Array to track visited nodes
        for(int u = 0; u < n; u++) {                  // Iterate through all nodes
            if(!visited[u]) {                         // If the node is not visited
                dfs(u, n, isConnected, visited);      // Perform DFS to visit all nodes in the connected component
                numOfConnectedComponents++;           // Increment the count of connected components
            }
        }
        return numOfConnectedComponents;              // Return the total number of connected components
    }
};

/*
### Approach 2: Union-Find Algorithm with Path Compression and Union by Rank
1. Represent the graph as a union-find data structure, where each node is initially its
own parent, and the rank is 1.
2. Use the `findSet` function to determine the root of the set containing a node:
   - If the node is its own parent, it is the root.
   - Otherwise, recursively find the root and apply path compression to update the
parent of the node to the root.
3. Use the `unionOfSets` function to merge two sets:
   - Find the roots of the sets containing the two nodes.
   - Compare the ranks of the roots to determine the new root.
   - Update the parent and rank of the merged set.
4. Iterate over the adjacency matrix `isConnected`:
   - For each pair of nodes (u, v), if they are connected and belong to different sets,
merge their sets using `unionOfSets`.
5. Count the number of connected components:
   - Iterate over all nodes and count how many nodes are their own parent. [#IMP]
   - Each such node represents a distinct connected component.
6. Return the total number of connected components as the result.

7. Time Complexity:
   - The nested loop over the adjacency matrix takes O(n^2).
   - The `findSet` and `unionOfSets` operations are nearly O(1) due to path compression
and union by rank.
   - Overall complexity is O(n^2).
8. Space Complexity:
   - The `subset` vector requires O(n) space to store parent and rank information for
each node.
*/

// 3. Union Find Algo (in the vector subset, if the node is a parent of itself its a different connected component)
// O(n*n + n) ~ O(n*n) = O(n^2) where n = no. of nodes from 0 to n-1 | Note: find() and union() both run in constant time i.e. O(1)
// O(n) due to the subset vector that stores parent and rank information for each node, requiring O(n) space. 

class Solution {
    int findSet(int u, vector<pair<int, int>> &subset) {
        int parent = subset[u].first;                   // Get the parent of the current node
        if(u == parent) return u;                       // If the node is its own parent, return it
        return subset[u].first = findSet(parent, subset); // Path compression: update parent to root
    }

    void unionOfSets(int u, int v, vector<pair<int, int>> &subset) {
       int uRoot = findSet(u, subset);                  // Find the root of the set containing u
       int vRoot = findSet(v, subset);                  // Find the root of the set containing v
       int uRank = subset[uRoot].second;                // Get the rank of u's root
       int vRank = subset[vRoot].second;                // Get the rank of v's root
       int newRoot = (uRank <= vRank) ? vRoot : uRoot;  // Choose the new root based on rank
       int mergedRank = uRank + vRank;                  // Update the rank of the merged set
       subset[uRoot] = {newRoot, mergedRank};           // Update uRoot's parent and rank
       subset[vRoot] = {newRoot, mergedRank};           // Update vRoot's parent and rank
    }
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();                     // Number of nodes in the graph
        vector<pair<int, int>> subset(n);               // Initialize subset array for union-find
        for(int i = 0; i < n; i++) subset[i] = {i, 1};  // Each node is its own parent with rank 1 initially
        for(int u = 0; u < n; u++) {                    // Iterate over all rows (nodes)
            for(int v = 0; v < n; v++) {                // Iterate over all columns (connections)
                if(u != v && isConnected[u][v] == 1) {  // If nodes u and v are connected
                    if(findSet(u, subset) != findSet(v, subset)) // If they belong to different sets
                        unionOfSets(u, v, subset);      // Merge the sets
                }
            }
        }
        int numOfConnectedComponents = 0;               // Count the number of connected components
        for(int i = 0; i < n; i++) {                    // Iterate over all nodes
            if(subset[i].first == i)                    // If the node is its own parent
                numOfConnectedComponents++;             // Increment the count of connected components
        }
        return numOfConnectedComponents;                // Return the total number of connected components
    }
};

// or, same as above but without comments

class Solution {
    int findSet(int u, vector<pair<int, int>> &subset) {
        int parent = subset[u].first;
        if(u == parent) return u;
        return subset[u].first = findSet(parent, subset);
    }

    void unionOfSets(int u, int v, vector<pair<int, int>> &subset) {
       int uRoot = findSet(u, subset);
       int vRoot = findSet(v, subset);
       int uRank = subset[uRoot].second;
       int vRank = subset[vRoot].second; 
       int newRoot = (uRank <= vRank) ? vRoot : uRoot;
       int mergedRank = uRank + vRank;
       subset[uRoot] = {newRoot, mergedRank};
       subset[vRoot] = {newRoot, mergedRank};
    }

public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<pair<int, int>> subset(n);
        for(int i=0; i<n; i++) subset[i] = {i, 1}; 
        for(int u=0; u<n; u++) {
            for(int v=0; v<n; v++) {
                if(u != v && isConnected[u][v] == 1) {
                    if(findSet(u, subset) != findSet(v, subset)) unionOfSets(u, v, subset);
                }
            }
        }
        int numOfConnectedComponents = 0;
        for(int i=0; i<n; i++) {
            if(subset[i].first == i) numOfConnectedComponents++;
        }
        return numOfConnectedComponents;
    }
};