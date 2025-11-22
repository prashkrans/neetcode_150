/* LC#73. NCMG3. Set Matrix Zeroes
   Given an m x n integer matrix, if an element is 0, set its entire row and column to 0's.
   You must do it in place.
   Example 1:
   Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
   Output: [[1,0,1],[0,0,0],[1,0,1]]
   Example 2:
   Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
   Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]


### Approach: In-Place Marking with First Row and Column as Markers
1. Use two boolean variables to track whether the first row or column originally
contains any zeroes. This ensures their state is preserved.
2. Iterate through the matrix starting from the second row and column. If a zero
is found, mark the corresponding row and column in the first row and column.
3. Iterate through the rows starting from the second row. If a row is marked in
the first column, set all elements in that row to zero.
4. Iterate through the columns starting from the second column. If a column is
marked in the first row, set all elements in that column to zero.
5. If the first row originally had zeroes, set all elements in the first row to
zero.
6. If the first column originally had zeroes, set all elements in the first column
to zero.
*/ 


// 1. In-Place Marking with First Row and Column as Markers
// Time Complexity: O(m*n) due to the nested loops
// Space Complexity: O(1) as we are modifying the matrix in place

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        bool firstRowHasZeroes = false;
        bool firstColHasZeroes = false;
        for(int j=0; j<n; j++) { // Check if the first row has zeroes
            if(matrix[0][j] == 0) {
                firstRowHasZeroes = true; 
                break; 
            } 
        }
        for(int i=0; i<m; i++) { // Check if the first column has zeroes
            if(matrix[i][0] == 0) {
                firstColHasZeroes = true; 
                break; 
            }
        } 
        for(int i=1; i<m; i++) { // Start marking rows and columns from the second row and column
            for(int j=1; j<n; j++) {
                if(matrix[i][j] == 0) { // If an element is zero
                    matrix[0][j] = 0; // Mark the column in the first row
                    matrix[i][0] = 0; // Mark the row in the first column
                }
            }
        }
        for(int i=1; i<m; i++) { // Zero out rows based on markers in the first column
            if(matrix[i][0] == 0) {
                for(int j=1; j<n; j++) matrix[i][j] = 0; // Set the entire row to zero
            }
        }
        for(int j=1; j<n; j++) { // Zero out columns based on markers in the first row
            if(matrix[0][j] == 0) {
                for(int i=1; i<m; i++) matrix[i][j] = 0; // Set the entire column to zero
            }
        }
        if(firstRowHasZeroes) { // If the first row originally had zeroes
            for(int j=0; j<n; j++) matrix[0][j] = 0; // Set the entire first row to zero
        }
        if(firstColHasZeroes) { // If the first column originally had zeroes
            for(int i=0; i<m; i++) matrix[i][0] = 0; // Set the entire first column to zero
        }
    }
};