// LC#787. NCAG6. Cheapest Flights Within K Stops (Directed graph)

// ### Approach: Bellman Ford with Limited Edge Relaxations
// 1. Model flights as a directed weighted graph using an adjacency list for efficient edge traversal.
// 2. Initialize distance array with infinity except source node set to zero.
// 3. Perform exactly k plus one iterations to simulate at most k intermediate stops allowed.
// 4. Use a copy of previous iteration distances to prevent same iteration multi edge chaining.
// 5. Relax all edges in every iteration using previous distances only for correctness.
// 6. After iterations, check destination distance to determine reachable cheapest cost.
// 7. Return minus one if destination remains unreachable within allowed stop constraint.


// Approach 1a: Bellman Ford Slightly modified -> Uses two arrays, prevDist (or tempDist) and dist
// Time Complexity: o(k * e)
// Space Complexity: o(n)

class Solution {                                                                           
    int bellmanFordAlgo(int n, unordered_map<int, vector<pair<int, int>>>& adjL, int src, int dst, int k) { // Bellman Ford with stop constraint                                      
        vector<int> dist(n, INT_MAX);                                                       // Distance array for shortest paths
        dist[src] = 0;                                                                      // Distance to source is zero
        for(int i = 0; i < k + 1; i++) {                                                    // Relax edges at most k+1 times
            vector<int> prevDist = dist;                                                    // Snapshot of previous iteration distances
            for(auto j: adjL) {                                                             // Iterate over all nodes
                int u = j.first;                                                            // Current source node
                for(auto k: adjL[u]) {                                                      // Traverse outgoing edges
                    int v = k.first, uTovWt = k.second;                                     // Destination node and edge weight
                    if(prevDist[u] != INT_MAX &&                                            // Ensure source reachable
                       dist[v] > prevDist[u] + uTovWt) {                                    // Relaxation condition
                        dist[v] = prevDist[u] + uTovWt;                                     // Update shortest distance
                    }
                }
            }
        }
        return (dist[dst] == INT_MAX) ? -1 : dist[dst];                                     // Return result or unreachable
    }

public:                                                                                     
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {   // Finds cheapest price with stops
        unordered_map<int, vector<pair<int, int>>> adjL;                                    // Adjacency list representation
        for(int u = 0; u < n; u++) adjL[u] = vector<pair<int, int>>();                      // Initialize adjacency list
        for(auto& flight: flights) {                                                        // Build graph from flights
            int u = flight[0], v = flight[1], wt = flight[2];                               // Extract edge information
            adjL[u].push_back({v, wt});                                                     // Add directed edge
        }
        return bellmanFordAlgo(n, adjL, src, dst, k);                                       // Apply Bellman Ford algorithm
    }
};


// Approach 1b: Bellman Ford Slightly modified -> Uses two arrays, prevDist (or tempDist) and dist
// Running time: O(k*(n+m))
// Auxiliary space: O(n+m) due to the adjL

class Solution {
    void printVec(vector<int> &arr) {
        for(auto i: arr) cout<<i<<" ";
        cout<<endl;
    }
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int, int>>> adjL(n, vector<pair<int, int>>());
        int m = flights.size();
        for(int i=0; i<m; i++) {
            int u = flights[i][0];
            int v = flights[i][1];
            int wt = flights[i][2];
            adjL[u].push_back({v, wt});
        }
        // Bellman Ford Algo:
        vector<int> dist(n, INT_MAX);
        dist[src] = 0;
        for(int i=0; i<=k; i++) {
            vector<int> tmpDist = dist;
            for(int u = 0; u<n; u++) { // u will vary from 0 to n-1 not src to n-1
                for(auto x: adjL[u]) {
                    if(dist[u]==INT_MAX) continue; // skip unreachable nodes here itself
                    else {
                        int v = x.first;
                        int wt_uTov = x.second;
                        tmpDist[v] = min(tmpDist[v], dist[u] + wt_uTov);       
                    }             
                }
            }
            // printVec(tmpDist);
            // printVec(dist);
            dist = tmpDist;
        }
        return (dist[dst] == INT_MAX) ? -1 : dist[dst];
    }
};