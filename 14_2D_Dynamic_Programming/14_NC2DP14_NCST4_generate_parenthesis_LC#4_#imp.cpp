// LC#22. NCST4. Generate Parentheses

// 1. Recusion without memoization
// Time Complexity: O(4^n / sqrt(n)) - Catalan number solution
// Space Complexity: O(n) for recursion stack, O(4^n / sqrt(n)) total with results

class Solution {
    void backtrack(int open, int close, int n, string s, vector<string> &ans) {
        if(open > n || close > open) return;  // Invalid state: too many open brackets or more closing than opening
        if(open == n && close == n) {         // Valid solution found: n open and n close parentheses
            ans.push_back(s);                 // Add current combination to result
            return;
        }
        backtrack(open+1, close, n, s+'(', ans);  // Try adding an open parenthesis
        backtrack(open, close+1, n, s+')', ans);  // Try adding a close parenthesis
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;                   // Store all valid combinations
        backtrack(0, 0, n, "", ans);          // Start backtracking with empty string
        return ans;
    }
};


// 2. Recusion with memoization (TODO)
// 3. DP bottom up TODO