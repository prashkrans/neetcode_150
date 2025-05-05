/* LC# NCMG2. 54. Spiral Matrix

Approaches:
1. Recursive
2. Iterative (TODO)

### Approach: Depth-First Search (DFS) for Spiral Order
1. Use a recursive DFS function to traverse the matrix in a spiral order.
2. The function takes the current position `(i, j)`, matrix dimensions `(m, n)`,
   the matrix itself, the result vector `ans`, and the current direction `dir`.
3. Base Case:
   - If the current position is out of bounds or already visited, return false.
4. Add the current element to the result vector and mark it as visited by setting
   its value to `-101`.
5. If all elements are visited (i.e., `ans.size() == m * n`), return true.
6. Determine the next position `(vi, vj)` based on the current direction:
   - `'R'` (right): Move to `(i, j+1)`, next direction is `'D'` (down).
   - `'D'` (down): Move to `(i+1, j)`, next direction is `'L'` (left).
   - `'L'` (left): Move to `(i, j-1)`, next direction is `'U'` (up).
   - `'U'` (up): Move to `(i-1, j)`, next direction is `'R'` (right).
7. If moving in the current direction fails, try moving in the next direction.
8. Start the DFS from the top-left corner `(0, 0)` with the initial direction `'R'`.
9. Return the result vector containing the spiral order of the matrix.
10. This approach ensures that all elements are visited in a spiral order using
    recursion.
*/

// 1. Depth-First Search (DFS) for Spiral Order (My custom code) | 0ms beats 100%
// Time Complexity: O(m * n), where m is the number of rows and n is the number of columns
// Space Complexity: O(m * n), for the recursion stack in the worst case
// Space Complexity: O(m * n), even for the iterative method

class Solution {
public:
    bool dfs(int i, int j, int m, int n, vector<vector<int>> &matrix, vector<int> &ans, char dir) {
        if(i < 0 || i == m || j < 0 || j == n || matrix[i][j] == -101) return false; // Out of bounds or already visited
        ans.push_back(matrix[i][j]);                      // Add the current element to the result
        matrix[i][j] = -101;                              // Mark the current cell as visited
        if(ans.size() == m * n) return true;              // If all elements are visited, return true

        int vi = i, vj = j;                               // Variables for moving in the current direction
        int wi = i, wj = j;                               // Variables for moving in the next direction
        char nextDir;                                     // Variable to store the next direction

        if(dir == 'R') {vj++; nextDir = 'D'; wi++;}       // Move right, next direction is down
        if(dir == 'D') {vi++; nextDir = 'L'; wj--;}       // Move down, next direction is left
        if(dir == 'L') {vj--; nextDir = 'U'; wi--;}       // Move left, next direction is up
        if(dir == 'U') {vi--; nextDir = 'R'; wj++;}       // Move up, next direction is right

        if(dfs(vi, vj, m, n, matrix, ans, dir) == false)  // Try moving in the current direction
            return dfs(wi, wj, m, n, matrix, ans, nextDir); // If blocked, try the next direction

        return false;                                     // Return false if no valid moves are possible
    }

    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;                                  // Result vector to store the spiral order
        int m = matrix.size();                            // Number of rows
        int n = matrix[0].size();                         // Number of columns
        dfs(0, 0, m, n, matrix, ans, 'R');                // Start DFS from the top-left corner, moving right
        return ans;                                       // Return the spiral order
    }
};
