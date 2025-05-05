// NCG14. Dijkstra's GFG
// https://www.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1
// 1. Using a set
// 2. Using a minHeap (priority queue)
// Running time: O(ElogV) or O(mlogn)
// Auxiliary space: O(V) or O(n)

// Note: There's no visited array in dijkstra's algorithm


class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<int>> &edges, int src) {
        unordered_map<int, vector<pair<int, int>>> adjL;
        for(int i=0; i<edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            int wt = edges[i][2];
            adjL[u].push_back({v, wt});
            adjL[v].push_back({u, wt});
        }
        set<pair<int, int>> st;
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;
        st.insert({dist[src], src});
        while(!st.empty()) {
            int u = st.begin()->second;
            st.erase(st.begin());
            for(auto i: adjL[u]) {
                int v = i.first;
                int wt = i.second;
                if(dist[u] != INT_MAX && dist[v] > dist[u] + wt) {
                    auto it = st.find({dist[v], v});
                    if(it != st.end()) st.erase(it);
                    dist[v] = dist[u] + wt;
                    st.insert({dist[v], v});
                }
            }
        }
        return dist;
    }
};


// ################################################

class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<int>> &edges, int src) {
        unordered_map<int, vector<pair<int, int>>> adjL;
        for(int i=0; i<edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            int wt = edges[i][2];
            adjL[u].push_back({v, wt});
            adjL[v].push_back({u, wt});
        }
        priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int, int>>> pq;
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;
        pq.push({dist[src], src});
        while(!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            for(auto i: adjL[u]) {
                int v = i.first;
                int wt = i.second;
                if(dist[u] != INT_MAX && dist[v] > dist[u] + wt) {
                    dist[v] = dist[u] + wt;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }
};