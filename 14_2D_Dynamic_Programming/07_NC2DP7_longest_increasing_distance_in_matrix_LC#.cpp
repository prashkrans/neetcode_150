// LC#329. NC2DP7. Longest Increasing Path in a Matrix

// Approach (DFS in each cell + Backtrack):
// If we move from one cell to an adjacent cell with a greater value, we won't revisit a cell, as the path is strictly 
// increasing. A brute force approach would be to run a dfs from every cell and return the longest path found. 
// This approach is exponential. 

// Three methods: 1. Rec wo memo 2. Rec w memo 3. Modified Kahn's Algo. There's no Bottom up DP algo.

// 1. Rec without memo
// O(4^(n*m))
// O(n*m) due to the recursion stack

class Solution {
    int dfs(int i, int j, int n, int m, vector<vector<int>> &matrix, vector<vector<int>> &visited) {
        visited[i][j] = 1;
        int res = 0;
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for(auto dir: dirs) {
            int vi = i + dir[0];    int vj = j + dir[1];
            if(vi>=0 && vi<n && vj>=0 && vj<m && !visited[vi][vj] && matrix[vi][vj] > matrix[i][j]) 
                res = max(res, 1 + dfs(vi, vj, n, m, matrix, visited));
        }
        visited[i][j] = 0; // Backtrack
        return res;
    }
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        int ans = 1; // Base case: minimum length: any cell itself = 1
        vector<vector<int>>visited(n, vector<int>(m, 0));
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                ans = max(ans, 1 + dfs(i, j, n, m, matrix, visited));       // 1 + dfs() not simply dfs
            }
        }
        return ans;
    }
};


// Rec with memo (easy got it right the first try)
// O(n*m)
// O(n*m)

class Solution {
    int dfs(int i, int j, int n, int m, vector<vector<int>> &matrix, vector<vector<int>> &visited, vector<vector<int>> &dp) {
        if(dp[i][j] != -1) return dp[i][j];
        visited[i][j] = 1;
        int res = 0;
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for(auto dir: dirs) {
            int vi = i + dir[0];    int vj = j + dir[1];
            if(vi>=0 && vi<n && vj>=0 && vj<m && !visited[vi][vj] && matrix[vi][vj] > matrix[i][j]) 
                res = max(res, 1 + dfs(vi, vj, n, m, matrix, visited, dp));
        }
        visited[i][j] = 0; // Backtrack
        return dp[i][j] = res;
    }
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        int ans = 1; // Base case: minimum length: any cell itself = 1
        vector<vector<int>> visited(n, vector<int>(m, 0));
        vector<vector<int>> dp(n, vector<int>(m, -1));
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                ans = max(ans, 1 + dfs(i, j, n, m, matrix, visited, dp));       // 1 + dfs() not simply dfs
            }
        }
        return ans;
    }
};



