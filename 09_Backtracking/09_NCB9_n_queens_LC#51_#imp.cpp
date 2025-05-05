/* LC#51. NCB9. N-Queens

Approach
We use backtracking. Starting from column 0, we attempt to place a queen in each row of the column. 

Before placing, we check whether the position is safe using a helper function isSafe() which checks for conflicts along:
    1. left row
    2. upper-left diagonal
    3. lower-left diagonal

If a valid position is found, we place the queen and move to the next column. If we reach the last column (col == n), 
it means we've placed all n queens and found a valid configuration, which we add to our result.

We backtrack by removing the queen and trying the next possible row in the current column.
*/


// Method 1. Backtrack without visited array but using isSafe() to check queen positions
// It is a perfect solution and an example of backtracking
// Running time: O(n!) | E.g. n = 4. At j = 0 we have 4 rows as option * at j = 1 we have 3 rows as an option * 2 * 1 = 4!
// Auxiliary space: O(n^2) due to the board which is vector of strings

class Solution {
    bool isSafe(int i, int j, int n, vector<string> &board) {
        // check left cells in the same row, top left diag and bottom left diag
        int r = i, c = j;
        while(j>=0) {                                   // Check left (row)
            if(board[i][j] == 'Q') return false;
            j--;
        }
        j = c;
        while(i>=0 && j>=0) {                           // Check upper-left diagonal
            if(board[i][j] == 'Q') return false;
            i--;    
            j--;
        }
        i = r;  j = c;
        while(i<n && j>=0) {                            // Check lower-left diagonal
            if(board[i][j] == 'Q') return false;
            i++;    
            j--;
        }
        return true;                                     // Position is safe
    }

    void backtrack(int j, int n, vector<string> &board, vector<vector<string>> &ans) {
        if(j==n) {                                       // All queens placed successfully
            ans.push_back(board);
            return;
        }
        for(int i=0; i<n; i++) {                         // Try each row in current column
            if(isSafe(i, j, n, board)) {                 // Check if position is safe
                board[i][j] = 'Q';                       // Place queen
                backtrack(j+1, n, board, ans);           // Recur for next column
                board[i][j] = '.';                       // Remove queen (backtrack)
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;                      // Store all solutions
        vector<string> board(n, string(n, '.'));         // Initialize empty board
        backtrack(0, n, board, ans);                     // Start backtracking from column 0
        return ans;                                      // Return all valid arrangements
    }
};





// Method 2. Using DFS and visited array: TODO
// Same as above
// Same as above

class Solution {
    void dfs(int i, int j, int n, vector<string> &board, vector<vector<int>> &visited) {
        if(i<0 || i==n || j<0 || j==n || visited[i][j]) return;
        visited[i][j] = 1;
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
        for(auto dir: dirs) {
            int vi = i + dir[0];    
            int vj = j + dir[1];
            dfs(vi, vj, n, board, visited);
        }
…        for(auto i: res) cout<<i.first<<" "<<i.second<<endl;
        return ans;
    }
};