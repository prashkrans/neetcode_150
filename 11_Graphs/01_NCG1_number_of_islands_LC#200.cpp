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

// Method 2. BFS (+ DFS)
// Running time: O(row x cols) i.e. O(n*m) i.e. 2D Array
// Auxiliary space: O(min(n, m)) i.e. the size of the queue can grow upto min(n, m) in case of diagonal island

class Solution {
    void bfs(int i, int j, int m, int n, vector<vector<char>> &grid) {
        vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
        queue<pair<int, int>> q;
        q.push({i, j});
        grid[i][j] = '2';
        while(!q.empty()) {
            int ui = q.front().first;
            int uj = q.front().second;
            q.pop();
            for(auto dir: dirs) {
                int vi = ui + dir.first;
                int vj = uj + dir.second;
                if(vi >= 0 && vj >= 0 && vi < m && vj < n && grid[vi][vj] == '1') {
                    q.push({vi, vj});
                    grid[vi][vj] = '2';
                }
            }
        }
    }

    void dfs(int i, int j, int m, int n, vector<vector<char>> &grid) {
        if(i < 0 || j < 0 || i >= m || j >= n || grid[i][j] != '1') return;
        grid[i][j] = '2';
        dfs(i+1, j, m, n, grid);
        dfs(i, j+1, m, n, grid);
        dfs(i-1, j, m, n, grid);
        dfs(i, j-1, m, n, grid);
    }

public: 
    int numIslands(vector<vector<char>> &grid) {
        int numOfConnComp = 0;
        int m = grid.size(), n = grid[0].size();
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == '1') {
                    // bfs(i, j, m, n, grid); // Both bfs and dfs work
                    dfs(i, j, m, n, grid);
                    numOfConnComp++;
                }
            }
        }
        return numOfConnComp;
    }
};


    