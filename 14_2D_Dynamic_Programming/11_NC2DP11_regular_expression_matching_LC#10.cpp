// LC#10. NC2DP11. Regular Expression Matching

// Approach:
// This solution performs recursive pattern matching with support for:
// - '.' which matches any single character
// - '*' which matches zero or more of the preceding element

// The function `rec(i, j, s, p)` checks whether s[i:] matches p[j:]:
// 1. Base case: If j >= p.size(), we return true only if i == s.size() (i.e., both string and pattern are fully matched).
// 2. Character match: We check if the current character matches (either directly or via '.').
// 3. Handling asterisk or star '*' (when p[j+1] == '*'):
//    - We can skip two characters in the pattern (i.e., `j+2`) to represent "zero occurrences" of `p[j]`.
//    - If current characters match, we can also stay at pattern index j and move to `i+1` in the string — this allows 
// for "one or more occurrences".
// 4. If there is no '*', but characters match, move both i and j forward (i.e., `i+1`, `j+1`).
// 5. If nothing matches, return false.

// Skipping by two positions in the pattern (i.e., `j+2`) is crucial when processing '*' — it skips both the character 
// and the '*' itself.

// 1. Rec without memo
// O(2^(n+m)
// O(m+n)

class Solution {
    bool rec(int i, int j, string &s, string &p) {
        if(j>=p.size()) return (i==s.size());
        bool match = false;
        if(i<s.size() && (s[i] == p[j] || p[j] == '.')) match = true;
        if(j+1 < p.size() && p[j+1] == '*') {
            if(rec(i, j+2, s, p)) return true;
            if(match && rec(i+1, j, s, p)) return true;
        }
        if(match) return rec(i+1, j+1, s, p);
        return false;
    }
public:
    bool isMatch(string s, string p) {
        return rec(0, 0, s, p);
    }
};


// 2. Rec with memo (Prefer this method)
// O(n*m) 0 ms beats 100 %
// O(n*m)

class Solution {
    bool rec(int i, int j, int n, int m, string &s, string &p, vector<vector<int>> &dp) {
        if(j>=m) return dp[i][j] = (i==n);
        if(i<=n && dp[i][j] != -1) return dp[i][j];
        bool match = false;
        if(i<n && (s[i] == p[j] || p[j] == '.')) match = true;
        if(j+1 < m && p[j+1] == '*') {
            if(rec(i, j+2, n, m, s, p, dp)) return dp[i][j] = true;
            if(match && rec(i+1, j, n, m, s, p, dp)) return dp[i][j] = true;
        }
        if(match) return dp[i][j] = rec(i+1, j+1, n, m, s, p, dp);
        return dp[i][j] = false;
    }
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        return rec(0, 0, n, m, s, p, dp);
    }
};

// 3. Bottom up DP
// 2. Rec with memo
// O(n*m) 0 ms beats 100 %
// O(n*m)

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.length(), n = p.length();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[m][n] = true; // Both s and p as empty strings

        for (int i = m; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                bool match = i < m && (s[i] == p[j] || p[j] == '.');

                if ((j + 1) < n && p[j + 1] == '*') {
                    dp[i][j] = dp[i][j + 2];
                    if (match) {
                        dp[i][j] = dp[i + 1][j] || dp[i][j];
                    }
                } else if (match) {
                    dp[i][j] = dp[i + 1][j + 1];
                }
            }
        }

        return dp[0][0];
    }
};