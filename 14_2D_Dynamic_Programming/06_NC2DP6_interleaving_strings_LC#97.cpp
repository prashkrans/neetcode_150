// LC#97. Interleaving String

// Approach:
// We recursively iterate through the strings using indices i, j, and k for s1, s2, and s3, respectively. 
// At each step, we extend the current path in two directions based on whether the k-th character of s3 matches 
// the current character of s1 or s2. If any path returns true, we immediately return true. If k goes out of bounds, 
// it means we have successfully formed the interleaved string, so we return true.


// 1a. Rec without memo
// O(2^(n+m)) where n = s1.size() and m = s2.size()
// O(n+m) due to the recursion stack

class Solution {
    bool rec(int i, int j, string &s1, string &s2, string &s3) {
        int k = i+j;
        if(k == s3.size()) return true;
        bool left = false, right = false;
        if(i != s1.size() && s1[i] == s3[k]) left = rec(i+1, j, s1, s2, s3);
        if(j != s2.size() && s2[j] == s3[k]) right = rec(i, j+1, s1, s2, s3); // don't use else here
        return left || right;
    }
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.size() + s2.size() != s3.size()) return false;
        return rec(0, 0, s1, s2, s3);
    }
};

// 1b. Rec without memo (sligthly modified base case)
// O(2^(n+m)) where n = s1.size() and m = s2.size()
// O(n+m) due to the recursion stack

class Solution {
    bool rec(int i, int j, string &s1, string &s2, string &s3) {
        int k = i+j;                                                  // k is the current position in s3
        // When k ends both i and j should also end to return true else return false
        if(k == s3.size()) return (i==s1.size() && j==s2.size());     // Base case: if we've processed all of s3, we should have used all of s1 and s2
        if(i != s1.size() && s1[i] == s3[k])                          // If current char in s1 matches current char in s3
            if(rec(i+1, j, s1, s2, s3)) return true;                  // Try using char from s1 and see if it leads to valid interleaving
        if(j != s2.size() && s2[j] == s3[k])                          // If current char in s2 matches current char in s3
            if(rec(i, j+1, s1, s2, s3)) return true;                  // Try using char from s2 and see if it leads to valid interleaving
        return false;                                                 // If neither option works, this path doesn't lead to valid interleaving
    }
public:
    bool isInterleave(string s1, string s2, string s3) {
        return rec(0, 0, s1, s2, s3);                                 // Start recursion from beginning of all strings
    }
};

// 2. Rec with memo (Prefer this method)
// O(n*m)
// O(n*m)
// Note:
// The solution uses an integer array (dp) instead of a boolean array to represent three states:
// a. -1: Not yet processed
// b. 0: Processed, result is false
// c. 1: Processed, result is true
// This allows the algorithm to differentiate between "not calculated yet" and "calculated but false" 
// which is something a boolean array couldn't do since it can only store two values.
// We use the fact that in C++, boolean true is 1 in int, boolean false is 0 in int

class Solution {
    bool rec(int i, int j, string &s1, string &s2, string &s3, vector<vector<int>> &dp) {
        int k = i+j;                                                  // k is the current position in s3
        if(k == s3.size()) {
            if (i==s1.size() && j==s2.size()) return dp[i][j] = true; // Base case: success if we've used all chars of s1, s2, and s3
            else return dp[i][j] = false;                             // Failure if s3 is done but we still have chars left in s1 or s2
        }
        if(dp[i][j] != -1) return dp[i][j];                           // Return cached result if available
        if(i != s1.size() && s1[i] == s3[k])                          // If current char in s1 matches current char in s3
            if(rec(i+1, j, s1, s2, s3, dp)) return dp[i][j] = true;   // Try using char from s1 and cache result
        if(j != s2.size() && s2[j] == s3[k])                          // If current char in s2 matches current char in s3
            if(rec(i, j+1, s1, s2, s3, dp)) return dp[i][j] = true;   // Try using char from s2 and cache result
        return dp[i][j] = false;                                      // Cache and return false if no valid interleaving found
    }
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, -1));            // Initialize memoization table with -1 (unprocessed)
        return rec(0, 0, s1, s2, s3, dp);                             // Start recursion from beginning of all strings
    }
};


// 3. Bottom up DP
// O(n*m)
// O(n*m) due to the DP 2D array

// Note: 
// It fails when dp[n][m] = false so, return false earlier itself if n+m != s3.size()
// It fails when n + m < s3.size()
// i and j vary from n to 0 and m to 0 in the nested for loop since we need the padding of
// bottom most and right most columns

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.size();                               // Length of first string
        int m = s2.size();                               // Length of second string
        if (n+m != s3.size()) return false;              // Quick check: combined lengths must match s3
        
        vector<vector<bool>> dp(n+1, vector<bool>(m+1, false)); // DP table: dp[i][j] = can we interleave s1[i:] and s2[j:] to form s3[i+j:]
        dp[n][m] = true;                                 // Base case: empty strings interleave to form empty string
        
        for(int i=n; i>=0; i--) {                        // Iterate from end of s1
            for(int j=m; j>=0; j--) {                    // Iterate from end of s2
                int k = i+j;                             // Position in s3
                
                if(i != n && s1[i] == s3[k])             // Try taking a character from s1
                    dp[i][j] = dp[i][j] || dp[i+1][j];   // If we can interleave after taking this char
                
                if(j != m && s2[j] == s3[k])             // Try taking a character from s2
                    dp[i][j] = dp[i][j] || dp[i][j+1];   // If we can interleave after taking this char
            }
        }
        
        return dp[0][0];                                 // Answer is whether we can interleave from the beginning
    }
};
    

