/*
LC#678. NCGA7. Valid Parenthesis String
Problem: Given a string s containing only the characters '(', ')', and '*',
return true if s is valid. A string is valid if:
    1. Any left parenthesis must have a corresponding right parenthesis.
    2. A '*' can represent either an empty string, '(', or ')'.
    3. An empty string is also valid.

Example: Input: s = "(*))"
        Output: true (can be interpreted as "(())" or "()" or "()" with an empty string)

Approaches:
1. Use two stacks to track the indices of left parentheses and '*' characters.
2. Recursion without memoization
3. Recursion with memoization
4. Greedy approach


### Approach 1: Use two stacks to track the indices of left parentheses and '*' characters.
1. Initialize two stacks: one for left parentheses and one for '*' characters.
2. Iterate through the string:
    - If the character is '(', push its index onto the left stack.
    - If the character is '*', push its index onto the star stack.
    - If the character is ')':
    - If there are unmatched left parentheses, pop from the left stack.
    - If not, check if there are any '*' characters to match with.
    - If neither is available, return false.
3. After processing the string, check if there are any unmatched left parentheses.
4. While there are unmatched left parentheses, check if there are any '*' characters
    that can be used to match them.
5. If all left parentheses are matched, return true; otherwise, return false.
*/


// 1. Use two stacks to track the indices of left parentheses and '*' characters.
// Time Complexity: O(n), where n is the length of the string
// Space Complexity: O(n), for the two stacks used to store indices

class Solution {
public:
    bool checkValidString(string s) {
        stack<int> left;                                      // Stack to store indices of '('
        stack<int> star;                                      // Stack to store indices of '*'
        for(int i = 0; i < s.size(); i++) {                   // Iterate through the string
            if(s[i] == '(')                                   // If the character is '(', push its index to left
                left.push(i);
            else if(s[i] == '*')                              // If the character is '*', push its index to star
                star.push(i);
            else {                                            // If the character is ')'
                if(!left.empty())                             // If there is an unmatched '(', pop it
                    left.pop();
                else if(!star.empty())                        // Otherwise, use a '*' as a '(' and pop it
                    star.pop();
                else return false;                            // If neither is available, return false
            }
        }
        while(!left.empty() && !star.empty()) {               // Match remaining '(' with '*'
            int leftIdx = left.top();                         // Get the top index of '('
            left.pop();
            int starIdx = star.top();                         // Get the top index of '*'
            star.pop();
            if(leftIdx > starIdx) return false;               // If '(' appears after '*', return false
        }
        return left.empty();                                  // Return true if no unmatched '(' remains
    }
};

// 2a. Recursion without memoization (Depends on i, open and close so, 2D DP array is not enough)
// Time Complexity: O(3^n), where n is the length of the string (due to three recursive calls for each '*')
// Space Complexity: O(n), for the recursion stack

class Solution {
    bool rec(int i, string &s, int open, int close) {
        if(close > open) return false;                       // If more ')' than '(', return false
        if(i == s.size()) return (open == close);            // Base case: If end of string, check if open == close
        if(s[i] == '(') return rec(i+1, s, open+1, close);   // If '(', increment open and recurse
        else if(s[i] == ')') return rec(i+1, s, open, close+1); // If ')', increment close and recurse
        return rec(i+1, s, open+1, close) ||                 // If '*', we got three options a. try it as '('
               rec(i+1, s, open, close+1) ||                 // b. Try it as ')'
               rec(i+1, s, open, close);                     // c. Try it as an empty string
    }
public:
    bool checkValidString(string s) {
        return rec(0, s, 0, 0);                              // Start recursion with index 0 and open/close = 0
    }
};

// 2b. Recursion without memoization (Depends on i and open only so, 2D DP array is enough)
// Time Complexity: O(3^n), where n is the length of the string (due to three recursive calls for each '*')
// Space Complexity: O(n), for the recursion stack

class Solution {
    bool rec(int i, string &s, int open) {
        if(open < 0) return false;                           // If unmatched ')' exceeds '(', return false
        if(i == s.size()) return (open == 0);                 // Base case: If end of string, check if open == 0
        if(s[i] == '(') return rec(i+1, s, open + 1);        // If '(', increment open and recurse
        else if(s[i] == ')') return rec(i+1, s, open - 1);   // If ')', decrement open and recurse
        return rec(i+1, s, open + 1) ||                      // If '*', try it as '('
               rec(i+1, s, open - 1) ||                      // Try it as ')'
               rec(i+1, s, open);                            // Try it as an empty string
    }
public:
    bool checkValidString(string s) {
        return rec(0, s, 0);                                 // Start recursion with index 0 and open = 0
    }
};

// 3. Recursion with memoization (Depends on i and open only so, 2D DP array is enough)
// Time Complexity: O(n^2), where n is the length of the string (due to memoization reducing redundant calls)
// Space Complexity: O(n^2), for the dp table and recursion stack

class Solution {
    bool rec(int i, string &s, int open, vector<vector<int>> &dp) {
        if(open < 0) return false;                           // If unmatched ')' exceeds '(', return false
        if(i == s.size()) return dp[i][open] = (open == 0);  // Base case: If end of string, check if open == 0
        if(dp[i][open] != -1) return dp[i][open];            // Return cached result if available
        if(s[i] == '(')                                      // If '(', increment open and recurse
            return dp[i][open] = rec(i+1, s, open + 1, dp);
        else if(s[i] == ')')                                 // If ')', decrement open and recurse
            return dp[i][open] = rec(i+1, s, open - 1, dp);
        return dp[i][open] = rec(i+1, s, open + 1, dp) ||    // If '*', try it as '('
                             rec(i+1, s, open - 1, dp) ||    // Try it as ')'
                             rec(i+1, s, open, dp);          // Try it as an empty string
    }
public:
    bool checkValidString(string s) {
        int n = s.size();
        vector<vector<int>> dp(n+1, vector<int>(n+1, -1));   // Initialize dp table with dimensions (n+1) x (n+1)
        return rec(0, s, 0, dp);                             // Start recursion with index 0 and open = 0
    }
};
