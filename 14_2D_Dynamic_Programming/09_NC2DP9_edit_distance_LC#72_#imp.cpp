
// LC#72. NC2DP9. Edit Distance
// Approach:
// We recursively iterate through the strings using indices i and j for word1 and word2, respectively. 
// If the characters at the current indices match, we increment both indices without counting an operation. 
// Otherwise, we have three choices: 
// 1. insert the character at the current index of word1 (increment j), 
// 2. delete the current character of word1 (increment i), 
// 3. or replace the character at index i in word1 (increment both i and j).

// If index i goes out of bounds, we return the number of remaining characters in word2 (using insert operations). 
// If index j goes out of bounds, we return the number of remaining characters in word1 (using delete operations). 
// At each step, we return the minimum operation path. This approach is exponential. 
// Can you think of a way to optimize it?

// Method 1: Rec without memo
// O(3^k) or O(3^(m+n))
// O(k) or O(3^(m+n))
// where k = max(m, n), m = word1.size(), n = word2.size()

class Solution {
    int rec(int i, int j, int m, int n, string &s1, string &s2) { // not changing the words hence passed by reference
        if(i==m) return n - j;
        if(j==n) return m - i;
        if(s1[i] == s2[j]) return rec(i+1, j+1, m, n, s1, s2);
        int ins = rec(i, j+1, m, n, s1, s2);
        int del = rec(i+1, j, m, n, s1, s2);
        int rep = rec(i+1, j+1, m, n, s1, s2);
        return 1 + min(ins, min(del, rep));
    }
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        return rec(0, 0, m, n, word1, word2);
    }
};

// Method 2: Rec with memo 2D dp array
// O(m*n)
// O(m*n)

class Solution {
    int rec(int i, int j, int m, int n, string &s1, string &s2, vector<vector<int>> &dp) {
        if(i==m) return dp[i][j] = n - j;
        if(j==n) return dp[i][j] = m - i;
        if(dp[i][j] != -1) return dp[i][j];
        if(s1[i] == s2[j]) return dp[i][j] = rec(i+1, j+1, m, n, s1, s2, dp); // Don't miss the return here
        int ins = rec(i, j+1, m, n, s1, s2, dp);
        int del = rec(i+1, j, m, n, s1, s2, dp);
        int rep = rec(i+1, j+1, m, n, s1, s2, dp);
        return dp[i][j] = 1 + min(ins, min(del, rep));
    }
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, -1));
        return rec(0, 0, m, n, word1, word2, dp);
    }
};


//  Method 3: Bottom up DP 2D array (Prefer this method)
//  O(m*n) 
//  O(m*n) due to the DP 2D array
//  where m = word1.size() and n = word2.size()

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();                           // Length of word1
        int n = word2.size();                           // Length of word2
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0)); // DP table for edit distances
        
        for(int i=0; i<=m; i++) dp[i][n] = m-i;         // Base case: edit distance from word1 to empty string word2
        for(int j=0; j<=n; j++) dp[m][j] = n-j;         // Base case: edit distance from empty string word1 to word2
        // dp[m][n] = 0;                                   // Redundant Base case: empty to empty requires 0 operations
        
        for(int i=m-1; i>=0; i--) {                     // Iterate backwards through word1
            for(int j=n-1; j>=0; j--) {                 // Iterate backwards through word2
                if(word1[i] == word2[j])                // If characters match
                    dp[i][j] = dp[i+1][j+1];            // No operation needed, use diagonal value
                else                                    // If characters don't match
                    dp[i][j] = 1 + min(dp[i][j+1], min(dp[i+1][j+1], dp[i+1][j])); 
                    // Take 1 plus the minimum of three operations: Insert, Replace, Delete
            }
        }
        return dp[0][0];                                // Return edit distance for the full strings
    }
};