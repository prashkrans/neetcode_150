// LC#980. NC2DP1c. Unique Paths III

// Method 1: Recursion without memoization
// O(4^(m*n))
// O(m*n) - recursion stack only (Not O(m*n) since not using the visited 2D array)
class Solution {
    int dfsBacktrack(int i, int j, int m, int n, vector<vector<int>> &grid, int currLength, int &count) {
        if(i<0 || i==m || j<0 || j==n || grid[i][j] == -1) return 0;
        if(grid[i][j] == 1) grid[i][j] = -1; // this is used as we are not using a visited 2D Array
        if(grid[i][j] == 2) return (currLength == m*n-count+1) ? 1 : 0;
        grid[i][j] = -1;
        int res = 0;
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for(auto dir: dirs) {
            int vi = i + dir[0];    int vj = j + dir[1];
            res += dfsBacktrack(vi, vj, m, n, grid, currLength+1, count);
        }
        grid[i][j] = 0;     // Backtrack
        return res;
    }
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;
        int count = 0;
        for(auto i: grid)
            for(auto j: i) 
                if(j!=0) count++;
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == 1)
                    ans = dfsBacktrack(i, j, m, n, grid, 0, count);
            }
        }
        return ans;
    }
};