/* LC#139. NC1DP10. Word Break

Approaches: 
1. Recursion using prefix and suffix and passing the string as a value as substrings
2. Recursion using sliding window or two pointers (similar to above but more efficient, hence prefer this)
3. BFS (TODO)

// Need to verify all the running times and space complexities


*/

// Method 1: Recursive without memoization
// Time Complexity: O(2^n)
// - For each prefix, we recursively explore all possible suffixes.
// - This results in an exponential time complexity due to redundant calculations.

// Space Complexity: O(n)
// - The recursion stack can go as deep as the length of the string `s`.

class Solution {
    bool rec(string s, unordered_set<string> &wordSet) {
        if(s.empty()) return true;                       // Base case: if the string is empty, return true
        bool res = false;
        for(int len = 1; len <= s.size(); len++) {       // Iterate through all possible prefixes
            string prefix = s.substr(0, len);           // Extract the prefix
            string suffix = s.substr(len);              // Extract the suffix
            if(wordSet.find(prefix) != wordSet.end()) { // Check if the prefix exists in the dictionary
                // cout<<prefix<<" -> "<<suffix<<endl;
                res = res || rec(suffix, wordSet);      // Recurse for the suffix
                if(res) return true;                    // If a valid segmentation is found, return true
            }
        }
        return res;                                     // If no valid segmentation is found, return false
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end()); // Convert wordDict to a set for O(1) lookups
        return rec(s, wordSet);                        // Start the recursion
    }
};

// Method 2: Recursive with memoization
// Running time: O(n^2) 
// Auxiliary space: O(n^2) since dp stores all the substrings i.e. O(n^2)

class Solution { // better to understand 
    bool rec(string s, unordered_set<string> &st,  unordered_map<string, bool> &dp) {
        if(s.empty()) return dp[""];
        else if(dp.count(s)) return dp[s];
        else {
            bool res = false;
            for(int len=1; len<=s.size(); len++) {      // Each substring is a branch here
                    string prefix = s.substr(0, len);
                    string suffix = s.substr(len);
                    if(st.find(prefix)!=st.end()) {     // Only if prefix is found proceed further else continue
                        res = res || rec(suffix, st, dp);
                        if(res) break; // the first time we find true, we break and return it
                    }
                }            
            dp[s] = res;
            return dp[s];
        }
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> st = {wordDict.begin(), wordDict.end()};
        unordered_map<string, bool> dp;
        dp[""] = true; // Base case that dp[empty string] is true
        return rec(s, st, dp);
    }
};

// or (Both are same here)

class Solution {
    bool rec(string s, unordered_set<string> &wordSet,  unordered_map<string, bool> &dp) {
        if(s.empty()) return dp[""];
        bool res = false;
        for(int len=1; len<=s.size(); len++) {      // Each substring is a branch here
                string prefix = s.substr(0, len);
                string suffix = s.substr(len);
                if(wordSet.find(prefix)!=wordSet.end()) {     // Only if prefix is found proceed further else continue
                    if(dp.count(suffix)) res = res || dp[suffix];
                    else res = res || rec(suffix, wordSet, dp);
                    if(res) break; // the first time we find true, we break and return it
                }
            }            
        dp[s] = res;
        return dp[s];
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet = {wordDict.begin(), wordDict.end()};
        // or unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        unordered_map<string, bool> dp;
        dp[""] = true; // Base case that dp[empty string] is true
        return rec(s, wordSet, dp);
    }
};



// Prefer this method

/* B. Using two pointers l and r or sliding window along with recursion

### Approach: Recursive with Two Pointers and Memoization
1. Use two pointers `l` and `r` to represent the current substring being checked.
2. Base cases:
   - If `r` reaches the end of the string, return true (the string can be segmented).
   - If the result for `(l, r)` is already computed, return the cached value from `dp[l][r]`.
3. Recursive steps:
   - Iterate through all substrings starting at `l` and ending at `r`.
   - If the substring exists in the dictionary, recurse for the remaining string starting at `r + 1`.
   - Cache the result for `(l, r)` in `dp[l][r]`.
4. Return the result for the initial call `(0, 0)`.

### Complexity:
- **Time Complexity**: O(n^2)
  - Each state `(l, r)` is computed only once due to memoization.
- **Space Complexity**: O(n^2)
  - The 2D `dp` array stores results for all pairs `(l, r)`.
  - The recursion stack can go as deep as `n`.

### Notes:
- This approach uses a sliding window technique with two pointers to check substrings.
- Memoization ensures that redundant calculations are avoided.
*/

// B1. Rec without memo

// Time Complexity: O(2^n) | Gets TLE 
// - For each starting index `l`, we explore all possible substrings starting at `l`.
// - This results in an exponential time complexity due to redundant calculations.

// Space Complexity: O(n)
// - The recursion stack can go as deep as the length of the string `s`.

class Solution {
    bool rec(int l, int r, string &s, unordered_set<string> &dict) {
        if(r == s.size()) return true;                      // Base case: reached the end of the string
        string substr;
        while(r < s.size()) {                               // Iterate through all substrings starting at `l`
            substr += s[r];
            if(dict.find(substr) != dict.end()) {           // Check if the substring exists in the dictionary
                if(rec(r + 1, r + 1, s, dict)) return true; // Recurse for the remaining string
            }
            r++;
        }
        return false;                                       // If no valid split is found, return false
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end()); // Convert wordDict to a set for O(1) lookups
        return rec(0, 0, s, dict);                          // Start the recursion
    }
};

// B2. Rec with memo

// Time Complexity: O(n^2) | 0ms beats 100%
// - For each starting index `l`, we iterate through all possible ending indices `r`.
// - The recursion is memoized, so each state `(l, r)` is computed only once.
// - This results in O(n^2) complexity, where n is the length of the string `s`.

// Space Complexity: O(n^2)
// - The 2D `dp` array stores results for all pairs `(l, r)`.
// - The recursion stack can go as deep as `n` in the worst case.

class Solution {
    bool rec(int l, int r, string &s, unordered_set<string> &dict, vector<vector<int>> &dp) {
        if(r == s.size()) return dp[l][r] = true;           // Base case: reached the end of the string
        if(dp[l][r] != -1) return dp[l][r];                 // Return cached result if already computed
        string substr;
        while(r < s.size()) {                               // Iterate through all substrings starting at `l`
            substr += s[r];
            dp[l][r] = false; // [#IMP - edge case]         // Initialize dp[l][r] to false
            if(dict.find(substr) != dict.end()) {           // Check if the substring exists in the dictionary
                if(rec(r + 1, r + 1, s, dict, dp))  {       // Recurse for the remaining string
                    return dp[l][r] = true;                 // If valid, mark dp[l][r] as true and return
                }
            }
            r++;
        }
        return dp[l][r] = false;                            // If no valid split is found, return false
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end()); // Convert wordDict to a set for O(1) lookups
        // or, unordered_set<string> dict;
        // for(auto word: wordDict) dict.insert(word);
        vector<vector<int>> dp(s.size() + 1, vector<int>(s.size() + 1, -1)); // Initialize 2D dp array with -1
        return rec(0, 0, s, dict, dp);                      // Start the recursion
    }
};