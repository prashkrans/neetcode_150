/** LC#115. NC2DP8. Distinct Subsequences
 * 
The problem is about finding the number of distinct subsequences of string s that equal string t.

Approach: We use recursion with two pointers - one for string s (index i) and one for string t (index j).

At each step we have two possibilities:
1. If current characters match (s[i] == t[j]), we have two choices:
   - Skip the current character in s (increment i only)
   - Use the current character in s to match with t (increment both i and j)
   
2. If characters don't match (s[i] != t[j]), we have only one choice:
   - Skip the current character in s (increment i only)

Base case: When we reach the end of s (i == s.length):
   - If we've also reached the end of t (j == t.length), we found a valid subsequence
   - Otherwise, we haven't found a complete match
**/

// 1. Rec without memo
// O(2^max(n, m)) = O(2^n) where n = s.size() and m = t.size() and n > m
// O(n) due to the recursion stack

class Solution {
    int rec(int i, int j, string &s, string &t) {
        if(i==s.size()) return (j==t.size()) ? 1 : 0;
        if(s[i] == t[j]) return rec(i+1, j, s, t) + rec(i+1, j+1, s, t);
        return rec(i+1, j, s, t);
    }
public:
    int numDistinct(string s, string t) {
        return rec(0, 0, s, t);
    }
};

// 2. Rec with memo
// O(n*m) where n = s.size() and m = t.size() and n > m
// O(n*m) due to the 2D DP array

class Solution {
    int rec(int i, int j, string &s, string &t, vector<vector<int>> &dp) {
        if(i==s.size()) return dp[i][j] = (j==t.size()) ? 1 : 0;
        if(dp[i][j] != -1) return dp[i][j];
        if(s[i] == t[j]) return dp[i][j] = rec(i+1, j, s, t, dp) + rec(i+1, j+1, s, t, dp);
        return dp[i][j] = rec(i+1, j, s, t, dp);
    }
public:
    int numDistinct(string s, string t) {
        vector<vector<int>> dp(s.size()+1, vector<int>(t.size()+1, -1));
        return rec(0, 0, s, t, dp);
    }
};


// 3. Bottom Up DP
// O(n*m) where n = s.size() and m = t.size() and n > m
// O(n*m) due to the 2D DP array

class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.size(), m = t.size();
        vector<vector<uint>> dp(n+1, vector<uint>(m+1, 0));
        for(int i=0; i<n; i++) dp[i][m] = 1;    // Base Case 1: s = s.substr(i) and t = "" => ans = 1 ("" is a subseq of s == t)
        for(int j=0; j<m; j++) dp[n][j] = 0;    // Base Case 2: s = "" and t = t.substr(j) => ans = 0 (no subseq of empty string == t)
        dp[n][m] = 1;                           // Base Case 3: Both s and t are empty => ans = 1 as (s itself is equal to t)

        for(int i=n-1; i>=0; i--) {
            for(int j=m-1; j>=0; j--) {
                if(s[i] == t[j]) dp[i][j] = dp[i+1][j] + dp[i+1][j+1];
                else dp[i][j] = dp[i+1][j];
            }
        }
        return dp[0][0];
    }
};
    

