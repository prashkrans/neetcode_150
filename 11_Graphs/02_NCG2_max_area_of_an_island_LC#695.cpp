/* LC#695. NCG2. Max Area of Island
Note: [#IMP] This problem uses dist for each nodes approach unlike LC#994. Rotting Oranges which uses dist for each levels approach.

// ### Approach: Breadth First Search Based Island Area Computation
// 1. Traverse the grid and identify unvisited land cells representing potential island starting points.
// 2. For each unvisited land cell, start a breadth first search to explore its entire connected component.
// 3. Use a queue to process cells level by level while marking visited land cells by setting them to zero.
// 4. Count each visited land cell during BFS to compute the current island area accurately.
// 5. Explore neighbors in four directions using predefined direction vectors for grid traversal.
// 6. Update the maximum area after processing each island completely.
// 7. This approach uses graph traversal, BFS, queue based processing, and in place grid modification.


Note: visited could not be an unordered map only ordered as pair<int, int> doesn't work with unordered_map
*/

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
                currArea++;     // if initial currArea = 0 then currArea++ is placed here
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
// Time Complexity: O(m * n) | 0ms, beats 100%
// Space Complexity: O(m * n)

class Solution {                                                                        
    int bfs(int i, int j, int m, int n, vector<vector<int>>& grid) {                        // BFS to compute island area
        static int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};                         // Direction vectors
        queue<pair<int, int>> q;                                                            // Queue for BFS traversal
        q.push({i, j});                                                                     // Push starting cell
        grid[i][j] = 0;                                                                     // Mark starting cell as visited
        int currArea = 1;                                                                   // Track current island area
        while(!q.empty()) {                                                                 // Continue BFS until queue empty
            int currLevelSize = q.size();                                                   // Number of nodes at current level
            for(int k = 0; k < currLevelSize; k++) {                                        // Process each node in level
                int ui = q.front().first, uj = q.front().second;                            // Extract current cell coordinates
                q.pop();                                                                    // Remove current cell from queue
                for(auto& dir: dirs) {                                                      // Explore all four directions
                    int vi = ui + dir[0], vj = uj + dir[1];                                 // Compute neighbor coordinates
                    if(vi >= 0 && vi < m && vj >= 0 && vj < n && grid[vi][vj] == 1) {       // Valid unvisited land check
                        q.push({vi, vj});                                                   // Add neighbor to queue
                        grid[vi][vj] = 0;                                                   // Mark neighbor as visited
                        currArea++;  // Since, initial currArea = 1, place currArea++; here // Increment island area count
                    }
                }
            }
        }
        return currArea;                                                                    // Return computed island area
    }
public:                                                                                    
    int maxAreaOfIsland(vector<vector<int>>& grid) {                                        // Finds maximum island area
        int maxArea = 0, m = grid.size(), n = grid[0].size();                               // Initialize max area and dimensions
        for(int i = 0; i < m; i++) {                                                        // Traverse grid rows
            for(int j = 0; j < n; j++) {                                                    // Traverse grid columns
                if(grid[i][j] == 1) {                                                       // Found unvisited land
                    int currArea = bfs(i, j, m, n, grid);                                   // Compute area using BFS
                    maxArea = max(maxArea, currArea);                                       // Update maximum area
                }
            }
        }
        return maxArea;                                                                     // Return maximum island area
    }
};
