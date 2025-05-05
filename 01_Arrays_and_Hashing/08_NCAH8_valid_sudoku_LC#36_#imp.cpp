/* LC#36. Valid Sudoku

### Approach: Three-Pass Validation with Hash Sets
1. The solution validates a Sudoku board by checking three separate conditions: rows,
columns, and 3x3 subboxes.
2. We use an unordered_set data structure to efficiently detect duplicates in constant
time for each check.
3. For row validation, we iterate through each row and ensure no digit
appears more than once, ignoring empty cells marked with '.'.
4. For column validation, we iterate through each column and similarly check for
duplicate digits, resetting the set for each new column.
5. For 3x3 subbox validation, we examine each of the nine subboxes using
a helper function that verifies no digit appears twice.
6. The isValidBox helper function takes the top-left coordinates of a subbox and
checks all nine cells within it.
7. If at any point we find a duplicate digit in a row,
column, or subbox, we immediately return false.
8. The time complexity is O(1) because a Sudoku board has fixed dimensions
(9x9), making all our operations constant time.
9. The space complexity is also O(1) because we use a fixed-size hash
set that never grows beyond 9 elements.
*/

// 1. Three-Pass Validation with Hash Sets
// Time Complexity: O(1) (not O(n)) as the size of the sudoku board is fixed at 9x9 | Oms beats 100%
// Space Complexity: O(1) as we use a fixed-size hash set for checking duplicates

class Solution {
    bool isValidBox(int i, int j, vector<vector<char>> &board) {  // Helper function to check 3x3 subbox validity
        unordered_set<char> st;                                   // Set to track digits in current subbox
        for(int x=i; x<i+3; x++) {                               // Iterate through rows of the 3x3 subbox
            for(int y=j; y<j+3; y++) {                           // Iterate through columns of the 3x3 subbox
                if(st.find(board[x][y]) != st.end()) return false; // If digit already exists in set, invalid sudoku
                if(board[x][y] != '.') st.insert(board[x][y]);     // Insert non-empty cells into the set
            }
        }
        return true;                                              // All checks passed, subbox is valid
    }
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        // for(auto i: board) {                                   // Debug code to print the board
        //     for(auto j: i) cout<<j<<" ";
        //     cout<<endl;
        // }
        unordered_set<char> st;                                   // Set to check for duplicates
        int n = 9;                                                // Size of sudoku board
        for(int i=0; i<n; i++) {                                  // Check each row
            st.clear();                                           // Clear set for new row
            for(int j=0; j<n; j++) {                              // Iterate through columns
                if(st.find(board[i][j]) != st.end()) return false; // If digit already in set, invalid row
                if(board[i][j] != '.') st.insert(board[i][j]);     // Add non-empty cells to set
            }
        }
        for(int j=0; j<n; j++) {                                  // Check each column
            st.clear();                                           // Clear set for new column
            for(int i=0; i<n; i++) {                              // Iterate through rows
                if(st.find(board[i][j]) != st.end()) return false; // If digit already in set, invalid column
                if(board[i][j] != '.') st.insert(board[i][j]);     // Add non-empty cells to set
            }
        }
        for(int i=0; i<n; i=i+3) {                                // Check each 3x3 subbox
            for(int j=0; j<n; j=j+3) {                            // Iterate through starting points of subboxes
                if(isValidBox(i, j, board) == false) return false; // Check if current subbox is valid
            }
        }
        return true;                                              // All checks passed, valid sudoku
    }
};

// {0, 3}, {3, 0}, {3, 3}

//     0 1 2       3 4 5
// 0             0  
// 1             1  
// 2             2  

