// LC#62. NC2DP1a. Unique Paths I

// Method 3: Bottom up DP
// O(m*n)
// O(m*n)

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for(int i=0; i<=m; i++) dp[i][n] = 0; // Redundant as all values are 0 when declared
        for(int j=0; j<=n; j++) dp[m][j] = 0;
        for(int i=m-1; i>=0; i--) {
            for(int j=n-1; j>=0; j--) {
                if(i==m-1 && j==n-1) dp[i][j] = 1;          // use if and else here         
                else dp[i][j] = dp[i][j+1] + dp[i+1][j];    // Use j+1 and i+1 here
            }
        }
        return dp[0][0];
    }
};



// Method 2: Rec + Memo
// O(m*n)
// O(m*n)

class Solution {
public:
    int dfsBacktrack(int i, int j, int m, int n, vector<vector<int>> &dp) {
        if(i==m || j==n) return dp[i][j] = 0;
        if(i==m-1 && j==n-1) return dp[i][j] = 1;
        return dp[i][j] = dfsBacktrack(i, j+1, m, n, dp) + dfsBacktrack(i+1, j, m, n, dp); 
    }
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m+1, vector<int>(n+1, -1));
        return dfsBacktrack(0, 0, m, n, dp); // src = {0, 0} to dest = {m-1, n-1}
    }
};
        


// Method 1: Recursion without memoization
// O(2^(m+n))
// O(m+n)

class Solution {
public:
    int dfsBacktrack(int i, int j, int m, int n, vector<vector<int>> &visited) {
        // if(i<0 || i==m || j<0 || j==n || visited[i][j] == 1) return 0; 
        if(i==m || j==n) return 0; // Note i and j never decreases so we don't need to check i<0 and j<0
        if(i==m-1 && j==n-1) return 1;
        visited[i][j] = 1;
        int ans = dfsBacktrack(i, j+1, m, n, visited) + dfsBacktrack(i+1, j, m, n, visited); 
        visited[i][j] = 0; // Backtrack
        return ans;
    }
    int uniquePaths(int m, int n) {
        int ans =  0;
        vector<vector<int>> visited(m, vector<int>(n, 0));
        return dfsBacktrack(0, 0, m, n, visited); // src = {0, 0} to dest = {m-1, n-1}
    }
};

// Compact version of the code above
// Since its only allowed to go either right or down we don't need:
// a. visited 2D vector
// b. i<0 and j<0 condition
// So, the 2D matrix becomes a simple binary tree instead of a graph.

class Solution {
public:
    int dfsBacktrack(int i, int j, int m, int n) {
        if(i==m || j==n) return 0;
        if(i==m-1 && j==n-1) return 1;
        return dfsBacktrack(i, j+1, m, n) + dfsBacktrack(i+1, j, m, n); 
    }
    int uniquePaths(int m, int n) {
        return dfsBacktrack(0, 0, m, n); // src = {0, 0} to dest = {m-1, n-1}
    }
};
    