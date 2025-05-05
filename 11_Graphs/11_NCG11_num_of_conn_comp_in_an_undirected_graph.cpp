// LintCode#3651. NCG9. Number of Connected Components in an Undirected Graph
// Leetcode premium

// Method 1. BFS
// Running time: O(V+E) i.e O(n+m)
// Auxiliary space: O(V+E) i.e. O(n+m) due to the adjacency list created


void bfs(int src, vector<vector<int>> &adjL, vector<int> &visited) {
    queue<int> q;
    q.push(src);
    visited[src] = 1;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(auto v: adjL[u]) {
            if(!visited[v]) {
                q.push(v);
                visited[v] = 1;
            }
        }
    }
}

int countComponents(int n, vector<vector<int>>& edges) {
    int m = edges.size();
    vector<vector<int>> adjL(n, vector<int>());
    vector<int> visited(n, 0);
    for(int i=0; i<m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adjL[u].push_back(v);
        if(u!=v) adjL[v].push_back(u);
    }
    int numOfConnComp = 0;
    for(int u=0; u<n; u++) {
        if(!visited[u]) {
            bfs(u, adjL, visited);
            numOfConnComp++;
        }
    }
    return numOfConnComp;

    

// Method 1. DFS
// Running time: O(V+E) i.e O(n+m)
// Auxiliary space: O(V+E) i.e. O(n+m) due to the adjacency list created

class Solution {
    public:
        void dfs(int u, vector<vector<int>> &adjL, vector<int> &visited) {
            visited[u] = 1;
            for(auto v: adjL[u])
                if(!visited[v]) dfs(v, adjL, visited);    
        }
    
        int countComponents(int n, vector<vector<int>>& edges) {
            int m = edges.size();
            vector<vector<int>> adjL(n, vector<int>());
            vector<int> visited(n, 0);
            for(int i=0; i<m; i++) {
                int u = edges[i][0];
                int v = edges[i][1];
                adjL[u].push_back(v);
                if(u!=v) adjL[v].push_back(u);
            }
            int numOfConnComp = 0;
            for(int u=0; u<n; u++) {
                if(!visited[u]) {
                    dfs(u, adjL, visited);
                    numOfConnComp++;
                }
            }
            return numOfConnComp;
        }
    };
    