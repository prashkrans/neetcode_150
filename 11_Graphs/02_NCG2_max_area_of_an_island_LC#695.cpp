// NC G2 
// LC#695


// Note: visited could not be an unordered map only ordered as pair<int, int> doesn't work with unordered_map
// Method 1: Using a separate visited map or 2D array

class Solution {
    public:
        bool isValid(pair<int, int> v, int n, int m, vector<vector<int>> &grid, map<pair<int, int>, int> &visited) {
            int i = v.first;
            int j = v.second;
            if(i<0 || i==n || j<0 || j==m || grid[i][j] == 0 || visited.count(v)) return false;
            else return true;
        }
    
        int bfs(int i, int j, int n, int m, vector<vector<int>> &grid, map<pair<int, int>, int> &visited) {
            queue<pair<int, int>> q;
            pair<int, int> src = {i, j};
            q.push(src);
            visited[src] = 1;
            vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
            int currArea = 0;
            while(!q.empty()) {
                pair<int, int> u = q.front();
                q.pop();
                currArea++;
                for (int x = 0; x<4; x++) {
                    pair<int, int> v = {u.first+dirs[x].first, u.second+dirs[x].second};
                    if(isValid(v, n, m, grid, visited)) {
                        q.push(v);
                        visited[v] = 1;
                    }
                }
            }
            return currArea;
        }
    
        int maxAreaOfIsland(vector<vector<int>>& grid) {
            int maxArea = 0;
            int n = grid.size();
            int m = grid[0].size();
            map<pair<int, int>, int> visited;
            for(int i=0; i<n; i++) {
                for(int j=0; j<m; j++) {
                    if(grid[i][j] == 1 && visited.count({i, j})==0) 
                        maxArea = max(maxArea, bfs(i, j, n, m, grid, visited));
                }
            }
            return maxArea;
        }
    };


// Method 2 without using any visited 2D vector or map and using the grid itself to mark nodes as visited

class Solution {
    public:
        bool isValid(pair<int, int> v, int n, int m, vector<vector<int>> &grid) {
                int i = v.first;
                int j = v.second;
                if(i<0 || i==n || j<0 || j==m || grid[i][j] == 0 || grid[i][j] == -1) return false;
                else return true;
            }
        
            int bfs(int i, int j, int n, int m, vector<vector<int>> &grid) {
                queue<pair<int, int>> q;
                pair<int, int> src = {i, j};
                q.push(src);
                grid[i][j] = -1;
                vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
                int currArea = 0;
                while(!q.empty()) {
                    pair<int, int> u = q.front();
                    q.pop();
                    currArea++;
                    for (int x = 0; x<4; x++) {
                        pair<int, int> v = {u.first+dirs[x].first, u.second+dirs[x].second};
                        if(isValid(v, n, m, grid)) {
                            q.push(v);
                            grid[v.first][v.second] = -1; // Mark v as visited
                        }
                    }
                }
                return currArea;
            }
        
            int maxAreaOfIsland(vector<vector<int>>& grid) {
                int maxArea = 0;
                int n = grid.size();
                int m = grid[0].size();
                for(int i=0; i<n; i++) {
                    for(int j=0; j<m; j++) {
                        if(grid[i][j] == 1) 
                            maxArea = max(maxArea, bfs(i, j, n, m, grid));
                    }
                }
                return maxArea;
            }
    };

