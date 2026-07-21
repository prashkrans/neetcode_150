/**
LC#212. NCT3. Word Search II
Exactly same as LC#79 Word Search I in backtracking, but uses a trie to store the words and prune the search space.

Approach:
1. Build a Trie from the given list of words.
2. Iterate through each cell in the board.
3. From each cell, perform DFS traversal:
4. At each step, check if the character exists in the current Trie node's children.
5. If a complete word is found, add it to the result and mark it as found to avoid duplicates.
6. Mark the current cell as visited during the DFS and then mark it unvisited while backtracking.
7. Use direction vectors to explore up, down, left, and right neighbors.

Time Complexity:
a. Trie construction: O(N * L), where N is the number of words and L is the average word length.
b. DFS traversal: O(n * m * 4^L), where n and m are board dimensions and L is the length of the longest word. 
The 4^L comes from exploring each path in 4 directions up to length L.

Space Complexity:
a. Trie storage: O(N * L), for storing the words in the Trie.
b. DFS recursion stack: O(L), maximum depth of the recursion tree.
c. Visited marking: a. if in place: O(1) or b. New 2D Vector: O(n*m) where M = no. of rows and N = no. of cols
d. Answer list: O(K), where K is the number of words found.

**/


class Solution {
    struct TrieNode {
        bool isCompleteWord;
        vector<TrieNode*> children;
        
        TrieNode(): isCompleteWord(false), children(vector<TrieNode*>(26, nullptr)) {}
        
        void insert(string word) {      // If we are writing insert as a method of the struct TrieNode we use this
            // TrieNode* curr = root;
            TrieNode* curr = this;
            for(int i=0; i<word.size(); i++) {
                int index = word[i] - 'a';
                if(curr->children[index] == nullptr) curr->children[index] = new TrieNode;
                curr = curr->children[index];
            }
            curr->isCompleteWord = true;
        }
    };
    TrieNode* root;
public:
    Solution(): root(new TrieNode) {}

    void dfs(int i, int j, int n, int m, vector<vector<char>> &board, vector<vector<int>> &visited, TrieNode* root, string currWord, vector<string> &result) {
        if(i<0 || i>=n || j<0 || j>=m) return;  // Fixed boundary check
        if(visited[i][j]) return;

        int index = board[i][j] - 'a';
        if(root->children[index] == nullptr) return;

        root = root->children[index];
        currWord+=board[i][j];
        if(root->isCompleteWord) {
            result.push_back(currWord);
            root->isCompleteWord = false;  // Avoid duplicates in result
        }

        visited[i][j] = 1;
        
        // Explore all four directions
        dfs(i, j+1, n, m, board, visited, root, currWord, result);
        dfs(i+1, j, n, m, board, visited, root, currWord, result);
        dfs(i, j-1, n, m, board, visited, root, currWord, result);
        dfs(i-1, j, n, m, board, visited, root, currWord, result);
        
        visited[i][j] = 0;  // Backtrack
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> result;
        // Build the Trie with all words
        for(auto &word: words) root->insert(word); // insert(word);
        
        int n = board.size();
        if(n == 0) return result;
        int m = board[0].size();
        if(m == 0) return result;
        
        vector<vector<int>> visited(n, vector<int>(m, 0));
        
        // Try each cell as starting point
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                dfs(i, j, n, m, board, visited, root, "", result);
            }
        }
        
        return result;
    }
};

// ### Approach: Trie Based Backtracking with DFS Pruning
// 1. Insert all given words into a trie to enable fast prefix based pruning during board traversal.
// 2. Traverse each board cell as a potential starting point for depth first search exploration.
// 3. During DFS, move simultaneously in the board and trie to validate prefixes efficiently.
// 4. If a trie child does not exist for a character, prune recursion immediately to save time.
// 5. Mark visited board cells temporarily to avoid revisiting in the same DFS path.
// 6. When a trie node marks a complete word, add current path to result and disable duplicates.
// 7. Use backtracking to restore board state and path after exploring all directions recursively.


// Same as above but slightly different
// Time Complexity: O(m * n * 4^l)
// Space Complexity: O(w * l + l)
// m → number of rows in the board
// n → number of columns in the board
// w → number of words in the input words list
// l → maximum length of a word in words

// m * n comes from starting DFS from every board cell.
// 4^l represents the maximum DFS branching factor up to word length l.
// w * l accounts for building the trie (total characters inserted).
// l space is used by the recursion stack and path during DFS.

class Solution {                                                                           
    struct TrieNode {                                                                       // Trie node structure
        bool isCompleteWord;                                                                // Marks completion of a valid word
        vector<TrieNode*> children;                                                         // Pointers to child nodes
        TrieNode(): isCompleteWord(false), children(26, nullptr) {};                        // Initialize node state
    };

    TrieNode* insert(TrieNode* root, string word) {                                         // Inserts a word into the trie
        TrieNode* curr = root;                                                              // Start traversal from root
        for(int i = 0; i < word.size(); i++) {                                              // Traverse characters of word
            int index = word[i] - 'a';                                                      // Compute child index
            if(!curr->children[index]) curr->children[index] = new TrieNode;                // Create node if missing
            curr = curr->children[index];                                                   // Move to next node
        }
        curr->isCompleteWord = true;                                                        // Mark end of word
        return root;                                                                        // Return root after insertion
    }

    void dfs(int i, int j, int &m, int &n, vector<vector<char>>& board, TrieNode* root, string& path, vector<string>& ans) {
        if(i < 0 || j < 0 || i == m || j == n || board[i][j] == '#') return;                // Boundary and visited check
        
        char ch = board[i][j];                                                              // Current board character
        int index = ch - 'a';                                                               // Convert character to index

        TrieNode* next = root->children[index];                                             // Move trie pointer
        if(!next) return;                                                                   // Prune path if no trie match
        
        path.push_back(ch);                                                                 // Add character to current path
        if(next->isCompleteWord) {                                                          // Check if a word is formed
            ans.push_back(path);                                                            // Store valid word
            next->isCompleteWord = false;                                                   // Avoid duplicate word addition
        }

        board[i][j] = '#';                                                                  // Mark cell as visited
         // vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};                  // This was giving TLE wasted 1 hour
        static int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};                         // Direction vectors
        for(auto dir: dirs) {                                                               // Explore all four directions
            int vi = i + dir[0], vj = j + dir[1];                                           // Compute next cell
            dfs(vi, vj, m, n, board, next, path, ans);                                      // Recurse deeper
        }
        
        path.pop_back();                                                                    // Backtrack current path
        board[i][j] = ch;                                                                   // Restore original board value
        return;                                                                             // Return after exploration
    }

public:                                                                                    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {          // Finds all words on board
        TrieNode* root = new TrieNode;                                                      // Initialize trie root
        for(auto word: words) {                                                             // Insert each word
            root = insert(root, word);                                                      // Build trie structure
        }
        vector<string> ans;                                                                 // Stores found words
        int m = board.size(), n = board[0].size();                                          // Board dimensions
        for(int i = 0; i < m; i++) {                                                        // Iterate rows
            for(int j = 0; j < n; j++) {                                                    // Iterate columns
                string path;                                                                // Current DFS path
                dfs(i, j, m, n, board, root, path, ans);                                    // Start DFS from cell
            }
        }
        return ans;                                                                         // Return all matched words
    }
};


// Same as above but slightly different
// Time Complexity: O(m*n*4^l)
// Space Complexity: O(w*l + l)

class Solution {
    struct TrieNode {
        bool isCompleteWord;
        vector<TrieNode*> children;
        TrieNode(): isCompleteWord(false), children(26, nullptr) {};
    };

    TrieNode* insert(TrieNode* root, string word) {
        TrieNode* curr = root;
        for(int i = 0; i < word.size(); i++) {
            int index = word[i] - 'a';
            if(!curr->children[index]) curr->children[index] = new TrieNode;
            curr = curr->children[index];
        }
        curr->isCompleteWord = true;
        return root;
    }

    void dfs(int i, int j, int &m, int &n, vector<vector<char>>& board, TrieNode* root, string path, vector<string>& ans) {
        if(i < 0 || j < 0 || i == m || j == n || board[i][j] == '#') return;
        
        char ch = board[i][j];
        int index = ch - 'a';
        if(!root->children[index]) return;
        
        if(root->children[index]->isCompleteWord) {
            ans.push_back(path + ch);
            root->children[index]->isCompleteWord = false;
        }

        board[i][j] = '#';
        
        dfs(i + 1, j, m, n, board, root->children[index], path + ch, ans);
        dfs(i, j + 1, m, n, board, root->children[index], path + ch, ans);
        dfs(i - 1, j, m, n, board, root->children[index], path + ch, ans);
        dfs(i, j - 1, m, n, board, root->children[index], path + ch, ans);
                
        board[i][j] = ch;
        return;
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode* root = new TrieNode;
        for(auto word: words) {
            root = insert(root, word);
        }
        vector<string> ans;
        int m = board.size(), n = board[0].size();
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                dfs(i, j, m, n, board, root, "", ans);
            }
        }
        return ans;
    }
};