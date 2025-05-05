// LC#63. NC2DP1b. Unique Paths II


// Method 3: Bottom up DP
// O(m*n)
// O(m*n)

// the addtion was giving an error hence used long long instead of int
typedef long long ll;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {   // Function to count unique paths with obstacles
        int m = obstacleGrid.size();                                    // Number of rows
        int n = obstacleGrid[0].size();                                 // Number of columns
        if(obstacleGrid[m-1][n-1] == 1) return 0;                       // If destination has obstacle, no path exists
        vector<vector<ll>> dp(m+1, vector<ll>(n+1, 0));                 // DP table with padding includes last row and col = 0
        for(int i=m-1; i>=0; i--) {                                     // Iterate from bottom row up
            for(int j=n-1; j>=0; j--) {                                 // Iterate from rightmost column left
                if(i==m-1 && j==n-1) dp[i][j] = 1;                      // Base case: destination cell has 1 path
                else if(obstacleGrid[i][j] == 0)                        // If current cell has no obstacle
                    dp[i][j] = dp[i][j+1] + dp[i+1][j];                 // Paths = paths from right + paths from below
                else dp[i][j] = 0;                                      // If obstacle present, no paths through this cell
            }
        }
        return dp[0][0];                                                // Return total paths from top-left to bottom-right
    }
};