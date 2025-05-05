/* LC#79. NCB6. Word Search

Approach: DFS Backtrack with pruning to avoid TLE
The methods given below are all same except a few minor things like separate visited matrix, traversing by index or by substr, etc.
*/

// 1a. DFS Backtrack (Prefer this method) | Most efficient

// Time Complexity: O((n * m) * 4^l)
// - n: number of rows in the board
// - m: number of columns in the board
// - l: length of the given word to search
// - For each cell (n*m), we might explore up to 4^l paths in worst case
//   since each position branches into 4 directions

// Space Complexity: O(l)
// - l: maximum depth of the recursion stack (length of the given word)
// - We use the call stack space proportional to the word length
// - No additional visited matrix needed as we mark cells with '#' temporarily

class Solution {
    bool dfsBacktrack(int i, int j, int n, int m, vector<vector<char>> &board, int idx, string &word) {
        if(idx == word.size()) return true;                     // [#IMP] This would be the topmost check condition
        if(i<0 || i==n || j<0 || j==m || board[i][j] == '#' || word[idx] != board[i][j]) return false;
        char temp = board[i][j];
        board[i][j] = '#';
        bool result = (
            dfsBacktrack(i, j+1, n, m, board, idx + 1, word) 
            || dfsBacktrack(i+1, j, n, m, board, idx + 1, word) 
            || dfsBacktrack(i, j-1, n, m, board, idx + 1, word) 
            || dfsBacktrack(i-1, j, n, m, board, idx + 1, word) // Don't put || after the last comparison
        );
        board[i][j] = temp; // Backtracking - [#IMP]
        return result;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        int m = board[0].size(); 
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(dfsBacktrack(i, j, n, m, board, 0, word)) return true;
            }
        }
        return false;
    }
};

// 1b. DFS Backtrack
// O(n*m*4^l) where n is no. of rows and m is no. of cols and l is length of the given word
// O(n*m)

class Solution {
    // This is a different dfs since we are backtracking we need to make visited[{i, j}] = 0 when its processed.
    bool dfsBacktrack(int i, int j, int n, int m, vector<vector<char>> &board, string word, map<pair<int, int>, int> &visited) {
        if(word.empty()) return true;                   // [#IMP] This would be the topmost check condition
        if(i<0 || i==n || j<0 || j==m) return false;
        if(visited[{i, j}]) return false; 
        if(word[0] != board[i][j]) return false;
        visited[{i, j}] = 1;
        bool result = (
            dfsBacktrack(i, j+1, n, m, board, word.substr(1), visited) 
            || dfsBacktrack(i+1, j, n, m, board, word.substr(1), visited) 
            || dfsBacktrack(i, j-1, n, m, board, word.substr(1), visited) 
            || dfsBacktrack(i-1, j, n, m, board, word.substr(1), visited) // Don't put || after the last comparison
        );
        visited[{i, j}] = 0; // Backtracking - [#IMP]
        return result;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        int m = board[0].size();
        map<pair<int, int>, int> visited;
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(dfsBacktrack(i, j, n, m, board, word, visited)) return true;
            }
        }
        return false;
    }
};

// 1c. DFS Backtrack
// O(n*m*4^l) where n is no. of rows and m is no. of cols and l is length of the given word
// O(n*m) due to visited matrix



class Solution {
    bool dfs(int i, int j, int n, int m, vector<vector<char>> &board, string word, vector<vector<int>> &visited) {
        if(word.empty()) return true;   // [#IMP] This would be the topmost check condition
        if(i<0 || i==n || j<0 || j==m || visited[i][j] || word[0] != board[i][j]) return false; // word[0] != board[i][j] is path pruning
        visited[i][j] = 1;
        vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for(auto dir: dirs) {
            int vi = i + dir.first;     
            int vj = j + dir.second;
            if(dfs(vi, vj, n, m, board, word.substr(1), visited)) return true;
        }
        visited[i][j] = 0;
        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size(), m = board[0].size();
        vector<vector<int>> visited(n, vector<int>(m, 0));
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(dfs(i, j, n, m, board, word, visited)) return true;
            }
        }
        return false;
    }
};


// 1d. DFS Backtrack
// O(n*m*4^l) where n is no. of rows and m is no. of cols and l is length of the given word
// O(n*m)

class Solution {
    bool dfs(int i, int j, int n, int m, vector<vector<char>> &board, string &word, string path, vector<vector<int>> &visited) {
        if(path + board[i][j] == word) return true;
        if(word[path.size()] != board[i][j]) return false; // path pruning, avoids TLE
        visited[i][j] = 1;
        vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for(auto dir: dirs) {
            int vi = i + dir.first;     int vj = j + dir.second;
            if(vi>=0 && vi<n && vj>=0 && vj<m && !visited[vi][vj]) {
                if(dfs(vi, vj, n, m, board, word, path+board[i][j], visited)) return true;
            }
        }
        visited[i][j] = 0; // Backtracking - [#IMP]
        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size(), m = board[0].size();
        vector<vector<int>> visited(n, vector<int>(m, 0));
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(dfs(i, j, n, m, board, word, "", visited)) return true;
            }
        }
        return false;
    }
};
