/* LC#133. NCG3. Clone Graph
This is a easy problem. The graph is undirected and connected.

Whenever we have to clone a graph or a tree, we use a hash map to store the mapping between 
the original node and the cloned node as unordered_map<Node*, Node*> where the key is the original node
and the value is the cloned node.

Approaches:
1. DFS
2. BFS


### Approach: Clone Graph Using DFS
1. Use a hash map `unordered_map<Node*, Node*>` to store the mapping between the original
node and its cloned counterpart. The key is the original node, and the value is the
cloned node.
2. Implement a recursive DFS function that takes the current node and the hash map as
parameters.
3. In the DFS function:
   a. Create a clone of the current node and store it in the hash map.
   b. Iterate over all neighbors of the current node. If a neighbor is not already
   cloned (not present in the hash map), recursively call the DFS function for that
   neighbor.
   c. After visiting all neighbors, add the cloned neighbors to the `neighbors` list
   of the cloned node.
4. In the `cloneGraph` function:
   a. Handle the edge case where the input graph is empty (return `nullptr`).
   b. Initialize the hash map and call the DFS function starting from the given node.
   c. Return the clone of the starting node from the hash map.
5. The algorithm ensures that each node and edge is processed exactly once, resulting
in a time complexity of O(V + E), where V is the number of nodes and E is the number
of edges.
*/


// 1. DFS | Here we use the unordered_map itself as a visited array.
// Time Complexity: O(V + E) or O(n + m) | 0ms beats 100%
// - Each node is visited once, and all edges are traversed once during the DFS.
// - V = number of nodes, E = number of edges.

// Space Complexity: O(V) or O(n)
// - The space is used by the hash map `mp` and the recursion stack in DFS.

class Solution {
    void dfs(Node* u, unordered_map<Node*, Node*> &mp) {
        mp[u] = new Node(u->val);                      // Create a clone of the current node
        for(auto v: u->neighbors) {                    // Iterate over all neighbors of the current node
            if(mp.find(v) == mp.end()) {               // If the neighbor is not yet cloned
                dfs(v, mp);                            // Recursively clone the neighbor
            }
        }
        for(auto v: u->neighbors) {                    // Iterate over all neighbors again
            mp[u]->neighbors.push_back(mp[v]);         // Add the cloned neighbors to the cloned node
        }                                              // Note: we need two for loops since we need to clone the neighbors first
    }
public:
    Node* cloneGraph(Node* node) {
        if(node == nullptr) return nullptr;            // [#IMP] Handle the edge case of an empty graph
        unordered_map<Node*, Node*> mp;                // Hash map to store original-to-clone mapping
        dfs(node, mp);                                 // Start DFS from the given node
        return mp[node];                               // Return the clone of the starting node
    }
};


2. BFS | Here we use the unordered_map itself as a visited array. (TODO)