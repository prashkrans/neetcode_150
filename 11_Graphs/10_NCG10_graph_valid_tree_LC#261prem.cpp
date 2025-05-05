/* LC#261. Premium NCG10. Graph Valid Tree
  
Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), 
write a function to check whether these edges make up a valid tree.

A valid tree should have exactly n - 1 edges and all nodes should be connected.

Example 1:
Input: n = 5, edges = [[0,1],[0,2],[0,3],[1,4]]
Output: true

Example 2:
Input: n = 5, edges = [[0,1],[1,2],[2,3],[1,3],[1,4]]
Output: false

Constraints:
1 <= n <= 2000
0 <= edges.length <= n - 1
  
Approach:
A tree is a graph that is undirected + connected (all nodes are visited) + has no cycles.
This is baisically a problem of checking if an undirected graph has no cycle and all nodes are connected.

1. DFS + Parent Variable    
2. BFS + Parent Array
3. Union Find Algorithm or Disjoint Set Union (DSU) + Path Compression + Union by Rank

Note: We can't use Kahn's BFS algo to check for a cycle in undirected graph, but simple BFS with a parent array.

*/

// Approach: A tree is a graph that is 
// 1. undirected +  2. connected (all nodes are visited) + 3. has no cycles

class Solution {
    bool isCyclicDfs(int u, vector<vector<int>> &adjL, vector<int> &visited, int parent) {
        visited[u] = 1;
        for(auto v: adjL[u]) {
            if(!visited[v]) {
                if(isCyclicDfs(v, adjL, visited, u)) return true;
            } 
            else {
                if(parent != v) return true;
            }
        }
        return false;
    }
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adjL(n, vector<int>());
        for(int i=0; i<edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            adjL[u].push_back(v);
            adjL[v].push_back(u);
        }
        vector<int> visited(n, 0);
        bool isCyclic = isCyclicDfs(0, adjL, visited, -1); // using parent of 0 as 0 fails for the case n = 1 and edges = [0, 0]
        for(int i=0; i<n; i++) if(visited[i] == 0) return false;
        return !isCyclic;
    }
};
