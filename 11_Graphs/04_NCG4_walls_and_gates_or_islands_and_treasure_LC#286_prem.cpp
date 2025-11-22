/* LC#286. NCG4. Premium Walls and Gates (Neetcode: Islands and Treasure)
LintCode#663 · Walls and Gates
https://neetcode.io/problems/islands-and-treasure
Note: This question is similar to is oranges rotten (LC#994)

Approaches:
1. Multi-Source BFS + dist variable + foor loop within the BFS
2. Multi-Source BFS + Update distance of child as 1 + distance of parent

### Approach 1: Multi-Source BFS for Distance Propagation
1. Identify all cells with value 0 (gates) in the grid and add them to a queue. These
act as the starting points for the BFS traversal.
2. Use a queue to perform a multi-source BFS. Each gate propagates its distance to
reachable cells in all four directions (up, down, left, right).
3. Maintain a `dist` variable to track the current distance being propagated. Start
with `dist = 1` and increment it after processing each BFS level.
4. For each cell processed in the BFS:
   a. Check its four neighbors. If a neighbor is within bounds, not a wall (-1), not
a gate (0), and its current value is greater than `dist`, update its value to `dist`.
   b. Add the updated neighbor to the queue for further processing.
5. Continue the BFS until the queue is empty, ensuring that all reachable cells are
updated with the shortest distance to a gate.
6. The algorithm ensures that each cell is processed at most once, resulting in a time
complexity of O(m * n), where n is the number of rows and m is the number of columns.
*/

// Method 1. Multi-Source BFS for Distance Propagation + using dist variable and for loop within the BFS
// Time Complexity: O(m * n)
// - Each cell is processed at most once during the BFS traversal.
// - n = number of rows, m = number of columns.

// Space Complexity: O(m * n)
// - The BFS queue can hold up to all cells in the grid in the worst case.

class Solution {
    public:
        void islandsAndTreasure(vector<vector<int>>& grid) {
            int m = grid.size();                            // Number of rows in the grid
            int n = grid[0].size();                         // Number of columns in the grid
            queue<pair<int, int>> q;                        // Queue for BFS traversal
            for(int i=0; i<m; i++) {                        // Iterate over all rows
                for(int j=0; j<n; j++) {                    // Iterate over all columns
                    if(grid[i][j] == 0) q.push({i, j});     // Add all cells with value 0 to the queue
                }
            }
            int dist = 1;                                   // Start distance from 1
            vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Directions for 4 neighbors
            while(!q.empty()) {                             // While there are cells to process
                int qSize = q.size();                       // Number of cells in the current BFS level
                for(int i=0; i<qSize; i++) {                // Process all cells in the current level
                    int ui = q.front().first, uj = q.front().second; // Get the current cell
                    q.pop();                                // Remove the cell from the queue
                    for(auto dir: dirs) {                   // Iterate over all 4 neighbors
                        int vi = ui + dir.first, vj = uj + dir.second; // Calculate neighbor coordinates
                        if(vi >= 0 && vi < m && vj >= 0 && vj < n      // Check if neighbor is within bounds
                        && grid[vi][vj] != -1 && grid[vi][vj] != 0     // Check if neighbor is not a wall or gate
                        && grid[vi][vj] > dist) {                     // Check if neighbor can be updated
                            grid[vi][vj] = dist;                      // Update the neighbor's distance
                            q.push({vi, vj});                         // Add the neighbor to the queue
                        }
                    }
                }
                dist++;                                   // Increment distance for the next BFS level
            }
        }
    };


/*
### Approach 2: Multi-Source BFS + Update distance of child as distance of parent + 1
1. Define a helper function `isValid` to check if a cell is within bounds, not a wall
(-1), and not a gate (0). This ensures that only valid and traversable cells are
processed.
2. Implement a BFS function that starts from a given gate and propagates distances to
all reachable cells. Use a queue to perform the BFS traversal.
3. For each cell processed in the BFS:
   a. Check its four neighbors (up, down, left, right). If a neighbor is valid and its
current value is greater than the distance from the current cell plus one, update its
value to the new distance.
   b. Add the updated neighbor to the queue for further processing.
4. In the main function `islandsAndTreasure`, iterate over all cells in the grid. For
each gate (cell with value 0), call the BFS function to propagate distances from that
gate.
5. The algorithm ensures that each cell is processed at most once, resulting in a time
complexity of O(n * m), where n is the number of rows and m is the number of columns.
*/

// Method 2. Multisource BFS + Update distance of child as distance of parent + 1
// Running time: O(number of zeroes * BFS) = O(k*n*m)[Incorrect] but O(n*m) as k doesn't matter here 
// Auxiliary space: O(n) due to the BFS queue
// where n = number of rows
// m = number of columns
// k = number of zeroes
// Note: Thus, the actual time complexity is still O(n * m), not O(k * n * m). 
// The number of 0s affects only the starting conditions but does not multiply the complexity.


// Time Complexity: O(n * m)
// - Each cell is processed at most once during the BFS traversal.
// - n = number of rows, m = number of columns.

// Space Complexity: O(n * m)
// - The BFS queue can hold up to all cells in the grid in the worst case.

class Solution {
public:
    bool isValid(pair<int, int> v, int n, int m, vector<vector<int>> &rooms) {
        int i = v.first;
        int j = v.second;
        if(i<0 || i==n || j<0 || j==m) return false;    // Check if the cell is out of bounds
        else if(rooms[i][j] == 0 || rooms[i][j] == -1) return false;    // Check if the cell is a gate or a wall
        else return true;   // The cell is valid and traversable
    }

    void bfs(int i, int j, int n, int m, vector<vector<int>> &rooms) {
        queue<pair<int, int>> q;                        // Queue for BFS traversal
        q.push({i, j});                                 // Start BFS from the given gate
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Directions for 4 neighbors
        while(!q.empty()) {                             // While there are cells to process
            pair<int, int> u = q.front();               // Get the current cell
            q.pop();                                    // Remove the cell from the queue
            for(auto dir: dirs) {                       // Iterate over all 4 neighbors
                pair<int, int> v = { u.first + dir[0], u.second + dir[1] }; // Calculate neighbor coordinates
                if(isValid(v, n, m, rooms) && rooms[v.first][v.second] > rooms[u.first][u.second] + 1) {
                    q.push(v);                          // Add the neighbor to the queue
                    rooms[v.first][v.second] = rooms[u.first][u.second] + 1; // Update the neighbor's distance
                }
            }
        }
    }

    void islandsAndTreasure(vector<vector<int>> &rooms) {
        int n = rooms.size();                           // Number of rows in the grid
        int m = rooms[0].size();                        // Number of columns in the grid
        for(int i=0; i<n; i++) {                        // Iterate over all rows
            for(int j=0; j<m; j++) {                    // Iterate over all columns
                if(rooms[i][j] == 0) {                  // If the cell is a gate
                    bfs(i, j, n, m, rooms);             // Perform BFS from the gate
                }
            }
        }
    }
};