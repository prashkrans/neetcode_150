// LC# 1584. NCAG3. Min Cost to Connect All Points

// Method 1. Kruskal's Algo
// Method 2. Modified Prim's Algo

// Approach: Convert the math problem to edges so, that Kruskal's algo can be used to find MST from the graph. 
// No need to create adjacency list
// Two methods to find Minimum Spanning Tree for an undirected graph. a. Kruskal's Algo     b. Modified Prim's Algo

// Method 1. Kruskal's Algo
// Running time: O(mlogm + m*(find()+union())) where m * (find() + union()) → O(m * α(n)) ≈ O(m) Thus, R.T. becomes O(mlogm) where 
// m = (n(n-1))/2 thus R.T. = O(n^2log(n^2)) = O(2(n^2logn)) ~ O(n^2logn)
// Auxiliary space: O(m) ~ O(n^2) due to the edges array

// Note: Where α(n) is the inverse Ackermann function, which grows extremely slowly. 
// For all practical values of n (even up to the size of the universe), α(n) ≤ 5

class cmp {
public:
    bool operator()(vector<int> &a, vector<int> &b) const {
        return a[2] < b[2];
    }
};

class Solution {
public:
    int find(int u, vector<pair<int, int>> &subset) {
        int parent = subset[u].first;
        if(u==parent) return u;
        else return subset[parent].first = find(parent, subset);
    }

    void unionOfSets(int u, int v, vector<pair<int, int>> &subset) {
        int uRoot = find(u, subset);        int vRoot = find(v, subset);
        int uRank = subset[uRoot].second;   int vRank = subset[vRoot].second;
        int mergedRank = uRank + vRank;
        int newRoot = (uRank <= vRank) ? vRoot : uRoot;
        subset[uRoot] = {newRoot, mergedRank};
        subset[vRoot] = {newRoot, mergedRank};
    }

    int minCostConnectPoints(vector<vector<int>>& points) {
        int minCostMST = 0;
        int n = points.size();  // Each point represents a node say 0 to n-1
        int m = (n*(n-1))/2;       // There would be an edge between each pair of points i.e. nC2
        vector<vector<int>> edges; // 2D array where each row is u, v, wt
        for(int i=0; i<n; i++) {
            for(int j=i+1; j<n; j++) {
                int x1 = points[i][0];  int x2 = points[j][0];
                int y1 = points[i][1];  int y2 = points[j][1];
                int manhattanDist = abs(x1-x2) + abs(y1-y2);
                edges.push_back({i, j, manhattanDist});
            }
        }
        // for(auto i: edges) cout<<i[0]<<", "<<i[1]<<" | "<<i[2]<<endl;
        sort(edges.begin(), edges.end(), cmp());
        // for(auto i: edges) cout<<i[0]<<", "<<i[1]<<" | "<<i[2]<<endl;

        vector<pair<int, int>> subset(n, pair<int, int>());
        for(int i=0; i<n; i++) subset[i] = {i, 1};

        for(int i=0; i<edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            int wt = edges[i][2];
            if(find(u, subset) != find(v, subset)) {
                minCostMST += wt;
                unionOfSets(u, v, subset);
            }
        }
        return minCostMST;
    }
};

// Method 2a. Modified Prim's Algo (using a set for min heap)
// Time Complexity: O(n^2 * log(n)) 
// - Building adjacency list: O(n^2)
// - Prim's algorithm: O(n^2 * log(n)) due to set operations

// Space Complexity: O(n^2)
// - Adjacency list: O(n^2)
// - Distance vector, set, and MST set: O(n)

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int ans = 0;                                    // Initialize total cost of MST
        int n = points.size();                          // Number of points
        unordered_map<int, vector<pair<int, int>>> adjL; // Adjacency list to store graph
        for(int i=0; i<n; i++) {                        // Iterate over all points
            for(int j=i+1; j<n; j++) {                  // Iterate over pairs of points
                int x1 = points[i][0], y1 = points[i][1]; // Coordinates of point i
                int x2 = points[j][0], y2 = points[j][1]; // Coordinates of point j
                int wt = abs(x2 - x1) + abs(y2 - y1);   // Calculate Manhattan distance
                adjL[i].push_back({j, wt});             // Add edge i -> j
                adjL[j].push_back({i, wt});             // Add edge j -> i (undirected graph)
            }
        }
        vector<int> dist(n, INT_MAX);                   // Distance vector initialized to infinity
        set<pair<int, int>> st;                         // Set to act as a priority queue
        unordered_set<int> inMst;                       // Set to track nodes in MST
        int src = 0;                                    // Start from node 0
        dist[src] = 0;                                  // Distance to source is 0
        st.insert({dist[src], src});                    // Insert source into the set
        inMst.insert(src);                              // Add source to MST
        while(!st.empty()) {                            // While there are nodes to process
            int u = st.begin()->second;                 // Get the node with the smallest distance
            int wt = st.begin()->first;                 // Get the weight of the smallest distance
            st.erase(st.begin());                       // Remove the node from the set
            inMst.insert(u);                            // Mark the node as included in MST
            ans += wt;                                  // Add the weight to the total cost
            if(inMst.size() == n) break;                // Stop if all nodes are in MST
            for(auto i: adjL[u]) {                      // Iterate over neighbors of the current node
                int v = i.first;                        // Neighbor node
                int wtUtoV = i.second;                  // Weight of the edge to the neighbor
                if(inMst.find(v) == inMst.end() && dist[v] > wtUtoV) { // If neighbor not in MST and has smaller weight
                    auto it = st.find({dist[v], v});    // Find the neighbor in the set
                    if(it != st.end()) st.erase(it);    // Remove the neighbor from the set if found
                    dist[v] = wtUtoV;                   // Update the distance to the neighbor
                    st.insert({dist[v], v});            // Reinsert the neighbor with updated distance
                }
            }
        }
        return ans;                                     // Return the total cost of the MST
    }
};

/*
### Approach: Modified Prim's Algorithm for Minimum Spanning Tree
1. Represent the points as an undirected graph as an adjacency list (unordered_map), where each node is connected
to every other node with an edge weight equal to the Manhattan distance.
2. Initialize a distance vector with INT_MAX for all nodes, except the source node, which
is set to 0. This vector tracks the minimum distance of each node from the MST.
3. Use a set (acting as a priority queue) to store pairs of {distance, node}, allowing
efficient retrieval of the node with the smallest distance.
4. Maintain a set of nodes already included in the MST to avoid processing them again.
5. Start with the source node, add its distance to the total cost, and mark it as included
in the MST.
6. For each neighbor of the current node, if the neighbor is not in the MST and the edge
weight is smaller than its current distance, update the distance and reinsert it into
the priority queue.
7. Repeat the process until all nodes are included in the MST or the priority queue is
empty.
8. Return the total cost of the MST as the final result.
*/

// Method 2b. Modified Prim's Algo (using a priority_queue for min heap)
// Time Complexity: O(n^2 * log(n)) 
// - Building adjacency list: O(n^2)
// - Prim's algorithm: O(n^2 * log(n)) due to set operations

// Space Complexity: O(n^2)
// - Adjacency list: O(n^2)
// - Distance vector, set, and MST set: O(n)


class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int ans = 0;
        int n = points.size();
        unordered_map<int, vector<pair<int, int>>> adjL;
        for(int i=0; i<n; i++) {
            for(int j=i+1; j<n; j++) {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];
                int wt = abs(x2 - x1) + abs(y2 - y1);   // edge weight = manhattan distance
                adjL[i].push_back({j, wt});             // undirected graph
                adjL[j].push_back({i, wt});
            }
        }
        vector<int> dist(n, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        unordered_set<int> inMst;
        int src = 0;
        dist[src] = 0;
        pq.push({dist[src], src});
        while(!pq.empty()) {
            int u = pq.top().second;
            int wt = pq.top().first;
            pq.pop();
            if (inMst.find(u) != inMst.end()) continue; // Ignore outdated distances. [#IMP] diff from set
            inMst.insert(u);
            ans += wt;
            if(inMst.size() == n) break;
            for(auto i: adjL[u]) {
                int v = i.first;
                int wtUtoV = i.second;
                if(inMst.find(v) == inMst.end() && dist[v] > wtUtoV) {
                    dist[v] = wtUtoV;
                    pq.push({dist[v], v});
                }
            }
        }
        return ans;        
    }
};