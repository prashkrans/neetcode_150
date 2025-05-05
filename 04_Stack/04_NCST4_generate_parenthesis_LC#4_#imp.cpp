// LC#22. NCST4. Generate Parentheses

// 1a. Recusion without memoization (With open and close counters)
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

// 1b. Recusion without memoization (With only open and 2*n counters)
// Time Complexity: O(4^n / sqrt(n)) - Catalan number solution
// - The number of valid parentheses combinations is given by the nth Catalan number, which is approximately O(4^n / sqrt(n)).
// - Each recursive call generates a new string, and there are O(4^n / sqrt(n)) valid combinations.

// Space Complexity: O(n)
// - The recursion stack can go as deep as 2n (the total number of parentheses), but at most n open parentheses are tracked at any time.

class Solution {
    void rec(int open, int n, string s, vector<string> &ans) {
        if(open < 0 || n < 0) return;                    // Invalid state: too many closing parentheses or no more characters left
        if(n == 0) {                                     // Base case: no more characters to add
            if(open == 0) ans.push_back(s);              // Valid combination if no unmatched open parentheses
            return;
        }
        rec(open+1, n-1, s + '(', ans);                  // Add an open parenthesis and recurse
        rec(open-1, n-1, s + ')', ans);                  // Add a close parenthesis and recurse
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;                              // Store all valid combinations
        rec(0, 2*n, "", ans);                            // Start recursion with 0 open parentheses and 2n total characters
        return ans;                                      // Return the result
    }
};

// 2. Recusion with memoization (TODO)
// 3. DP bottom up TODO