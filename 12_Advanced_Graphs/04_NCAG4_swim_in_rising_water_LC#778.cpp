/**
LC#778. NCG4. Swim in Rising Water:


// Approach: This is simply a variation of MST of an Undirected Graph
// Could use a. Kruskal's algo (Disjoint Set Union) or b. Modified Prim's Algo (Variation of Dijkstra's algo)
// It seems complex but we only need to convert the matrix to a graph using the logic that an undirected edge 
// exists between u and v with length = max(grid[ui][uj], grid[vi][vj])

// Running time: O(mlogm) ~ O(n^2log(n^2)) = O(n^2logn)
// Auxiliary space: O(n^2) due to the subset map


**/

// Method 1. Kruskal's Algo

class cmp {
    public:
    bool operator() (const vector<int> &a, const vector<int>time &b) const {
        return a[4] < b[4];
    }
};

class Solution {
    pair<int, int> findSet(pair<int, int> u, map<pair<int, int>, pair<pair<int, int>, int>> &subset) {
        pair<int, int> parent = subset[u].first;
        if(u == parent) return u;
        else return subset[u].first = findSet(parent, subset);
    }

    void unionOfSets(pair<int, int> u, pair<int ,int> v, map<pair<int, int>, pair<pair<int, int>, int>> &subset) {
        pair<int, int> uRoot = findSet(u, subset);  pair<int, int> vRoot = findSet(v, subset);
        int uRank = subset[uRoot].second;               int vRank = subset[vRoot].second;
        int mergedRank = uRank + vRank;
        pair<int, int> newRoot = (uRank <= vRank) ? vRoot : uRoot;
        subset[uRoot] = {newRoot, mergedRank};
        subset[vRoot] = {newRoot, mergedRank};
    }

public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> edges;
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for(int ui=0; ui<n; ui++) {
            for(int uj=0; uj<n; uj++) {
                for(auto dir: dirs) {
                    int vi = ui + dir[0];
                    int vj = uj + dir[1];
                    if(vi>=0 && vi<n && vj>=0 && vj<n) {
                        int wt = max(grid[ui][uj], grid[vi][vj]);
                        edges.push_back({vi, vj, ui, uj, wt}); // edge from v to u
                        edges.push_back({ui, uj, vi, vj, wt}); // edge from u to v
                    }
                }
            }
        }
        sort(edges.begin(), edges.end(), cmp());
        // for(auto edge: edges) cout<<edge[0]<<", "<<edge[1]<<" -> "<<edge[2]<<", "<<edge[3]<<" | "<<edge[4]<<endl;

        int maxTime = grid[0][0];
        pair<int, int> src = {0, 0};
        pair<int, int> dest = {n-1, n-1};
        map<pair<int, int>, pair<pair<int, int>, int>> subset;
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                subset[{i, j}] = {{i, j}, 1};
            }
        }
        for(auto edge: edges) {
            pair<int, int> u = {edge[0], edge[1]};
            pair<int, int> v = {edge[2], edge[3]};
            int wt = edge[4];
            if(findSet(src, subset) == findSet(dest, subset)) return maxTime;
            else if(findSet(u, subset) != findSet(v, subset)) {
                unionOfSets(u, v, subset);
                maxTime = max(maxTime, wt);
            }
        }

        return maxTime;
    }
};
    