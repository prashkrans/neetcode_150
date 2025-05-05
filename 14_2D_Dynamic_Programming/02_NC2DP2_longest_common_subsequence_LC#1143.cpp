// LC#1143. NC2DP2. Longest Common Subsequence

// Approach: 
// a. Recursion without memo => Recursion with memo => Bottom up
// b. Directly Bottom up using the fact that two strings that are empty have LCS = "" with length of the LCS as 0
// So, the recurrence relation becomes:
// Given f("", "") = 0 i.e. f(m, n) = 0 and f("a", "") and f("", "a") = 0 i.e. f(m-1, n) = f(n, m-1) = 0
// f(i, j) = if (s1[i] == s2[j]) 1 + f(i+1, j+1) 
//           else max(f(i, j+1), f(i+1, j))

// Method 3a: Bottom Up DP (from i = 0 to m and j = 0 to n | returns dp[n][m])
// O(m*n)
// O(m*n) due to the DP 2D array

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size();
        int m = text2.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0)); // This already makes the first row and col all 0s
        for(int i=1; i<n+1; i++) {
            for(int j=1; j<m+1; j++) {
                if(text1[i-1]==text2[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
                else dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            }
        }
        return dp[n][m];
    }
};

// Method 3b: Bottom Up DP (from i = m-1 to 0 and j = n-1 to 0 | returns dp[0][0])
// O(m*n)
// O(m*n) due to the DP 2D array

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size();
        int n = text2.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for(int i=m-1; i>=0; i--) {
            for(int j=n-1; j>=0; j--) {
                if(text1[i] == text2[j]) dp[i][j] = 1 + dp[i+1][j+1];
                else dp[i][j] = max(dp[i+1][j], dp[i][j+1]);
            }
        }
        return dp[0][0];
    }
};

// O(m*n)
// O(m*n) due to the DP 2D array