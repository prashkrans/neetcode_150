/* LC#221. NC2DP12. Maximal Square
*/

/*
### Approach: Recursive Solution with Memoization
1. Define a recursive function `rec(i, j, m, n, matrix, dp)` to calculate the size of
the largest square with the top-left corner at `(i, j)`.
2. Base case:
   a. If `(i, j)` is out of bounds or the cell value is '0', return 0.
3. Memoization:
   a. If the result for `(i, j)` is already computed (stored in `dp[i][j]`), return it
to avoid redundant calculations.
4. Recursive calls:
   a. Calculate the size of the square by exploring the right, down, and diagonal
neighbors.
   b. Use the formula `1 + min(right, down, diag)` to determine the size of the square
side at `(i, j)`.
5. Store the result in `dp[i][j]` to avoid recomputation.
6. In the `maximalSquare` function:
   a. Initialize a DP table `dp` with dimensions `m x n` and values set to -1.
   b. Iterate over all cells in the matrix. For each cell with value '1', call the
recursive function to calculate the size of the side of the square.
   c. Track the maximum side length of the square.
7. Calculate the area of the largest square using the formula `side * side` and return
it.
8. The algorithm ensures that each cell is processed once due to memoization, resulting
in a time complexity of O(n * m), where n is the number of rows and m is the number of
columns.
*/

// 1. Rec without memo


class Solution {
    int rec(int i, int j, int m, int n, vector<vector<char>> &matrix) {
        if(i < 0 || i == m || j < 0 || j == n || matrix[i][j] == '0') return 0;
        int right = rec(i, j+1, m, n, matrix);
        int down = rec(i+1, j, m, n, matrix);
        int diag = rec(i+1, j+1, m, n, matrix);
        return 1 + min(right, min(down, diag));

    }   
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int side = 0;
        int m = matrix.size();
        int n = matrix[0].size();
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(matrix[i][j] == '1') 
                    side = max(side, rec(i, j, m, n, matrix));
            }
        }
        int maxArea = side * side;
        return maxArea;
    }
};


// 2. Rec with memo (Prefer this method)
// O(n*m)
// O(n*m) due to the memoization table and O(n*m) for the recursion stack space

class Solution {
    int rec(int i, int j, int m, int n, vector<vector<char>> &matrix, vector<vector<int>> &dp) {
        if(i < 0 || i == m || j < 0 || j == n || matrix[i][j] == '0') return 0; // Base case: out of bounds or '0'
        if(dp[i][j] != -1) return dp[i][j];               // Return cached result if already computed
        int right = rec(i, j+1, m, n, matrix, dp);        // Explore right cell
        int down = rec(i+1, j, m, n, matrix, dp);         // Explore down cell
        int diag = rec(i+1, j+1, m, n, matrix, dp);       // Explore diagonal cell
        return dp[i][j] = 1 + min(right, min(down, diag)); // Store and return the size of the square
    }   
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int side = 0;                                     // Maximum side length of the square
        int m = matrix.size();                            // Number of rows
        int n = matrix[0].size();                         // Number of columns
        vector<vector<int>> dp(m, vector<int>(n, -1));    // DP table initialized to -1
        for(int i=0; i<m; i++) {                          // Iterate over all rows
            for(int j=0; j<n; j++) {                      // Iterate over all columns
                if(matrix[i][j] == '1')                   // If the cell is '1'
                    side = max(side, rec(i, j, m, n, matrix, dp)); // Update the maximum side length
            }
        }
        int maxArea = side * side;                        // Calculate the area of the largest square
        return maxArea;                                   // Return the maximum area
    }
};

// 3. Bottom up DP

class Solution { 
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int side = 0;                                     // Maximum side length of the square
        int m = matrix.size();                            // Number of rows
        int n = matrix[0].size();                         // Number of columns
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0)); // [#IMP] DP table initialized to 0, includes base case of rightmost col and bottomost row as zeroes
        for(int i=m-1; i>=0; i--) {                       // Iterate over rows from bottom to top
            for(int j=n-1; j>=0; j--) {                   // Iterate over columns from right to left
                if(matrix[i][j] == '1') {                 // If the cell is '1'
                    dp[i][j] = 1 + min(dp[i][j+1],        // Calculate the size of the square
                                        min(dp[i+1][j], dp[i+1][j+1]));
                    side = max(side, dp[i][j]);           // Update the maximum side length
                }
                else dp[i][j] = 0;                        // If the cell is '0', no square can be formed. Redundant as dp initialized as all zeroes
            }
        }
        int maxArea = side * side;                        // [#IMP] Calculate the area of the largest square
        return maxArea;                                   // Return the maximum area
    }
};