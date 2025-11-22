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