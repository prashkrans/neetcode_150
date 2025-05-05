/* LC#48. NCGM1. Rotate Image

### Approach: Reverse Columns and Transpose
1. **Reverse Each Column**:
   - Iterate through each column of the matrix.
   - Use two pointers (`up` and `down`) to reverse the elements in the column.
   - Swap the top and bottom elements until the pointers meet in the middle.
   - This step is similar to reversing a string but applied to each column.

2. **Transpose the Matrix**:
   - Iterate through the upper triangle of the matrix (i.e., where `j >= i`).
   - Swap the elements at positions `(i, j)` and `(j, i)` to transpose the matrix.
   - Note: The diagonal elements (where `i == j`) are not swapped.

3. **Result**:
   - After reversing the columns and transposing the matrix, the matrix is rotated
     90 degrees clockwise.

4. **Time Complexity**:
   - Reversing each column takes O(n^2) time, as each element is visited once.
   - Transposing the matrix also takes O(n^2) time.
   - Overall time complexity: O(n^2).

5. **Space Complexity**:
   - The rotation is performed in-place, so no additional space is used.
   - Overall space complexity: O(1).
*/

// Time Complexity: O(n^2), where n is the size of the matrix (due to reversing columns and transposing) | 0ms beats 100%
// Space Complexity: O(1), as the rotation is done in-place

class Solution {
    void swap(int &a, int &b) {
        a = a + b;      // int temp = a;
        b = a - b;      // a = b;
        a = a - b;      // b = temp;
    }
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();                              // Get the size of the matrix

        // Step 1: Reverse each column
        for(int j = 0; j < n; j++) {                        // Iterate through each column
            int up = 0, down = n - 1;                       // Initialize pointers for the top and bottom of the column
            while(up < down) {                              // Reverse the column by swapping elements
                swap(matrix[up++][j], matrix[down--][j]);   // Swap the top and bottom elements
            }
        }

        // Step 2: Transpose the matrix
        for(int i = 0; i < n; i++) {                        // Iterate through each row
            for(int j = i; j < n; j++) {                    // Iterate through the upper triangle (j = i not 0) of the matrix
                if(i != j) swap(matrix[i][j], matrix[j][i]); // Swap elements to transpose the matrix
            }
        }
    }
};
