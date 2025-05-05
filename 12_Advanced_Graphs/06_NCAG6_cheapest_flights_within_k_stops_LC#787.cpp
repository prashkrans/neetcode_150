// LC#787. NCAG6. Cheapest Flights Within K Stops
// Approach: Bellman Ford Slightly modified -> Uses two arrays, tempDist and dist
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