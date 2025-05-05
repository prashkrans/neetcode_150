// LC# 200. NCG1. Number of Islands

// Method 1. DFS
// Running time: O(row x cols) i.e. O(n*m) i.e. 2D Array
// Auxiliary space: O(n*m) due to the recursion stack | Note - we are not using visited separately here

class Solution {
    public:
        void dfs(int i, int j, int n, int m, vector<vector<char>> &grid) {
            if(i<0||i==n||j<0||j==m) return;
            else if (grid[i][j]=='0'||grid[i][j]=='2') return ;
            else {
                grid[i][j]='2';
                dfs(i, j+1, n, m, grid);
                dfs(i+1, j, n, m, grid);
                dfs(i, j-1, n, m, grid);
                dfs(i-1, j, n, m, grid);
            }
    
        }
    
    
        int numIslands(vector<vector<char>>& grid) {
            int n = grid.size();
            int m = grid[0].size();
            int ans = 0;
            for(int i=0; i<n; i++) {
                for(int j=0; j<m; j++) {
                    cout<<"i, j: "<<i<<" "<<j<<" ";
                    if(grid[i][j]=='1') {
                        dfs(i, j, n, m, grid);
                        ans++;
                    }
                }
            }
            return ans;
        }   
    };
    