/* LC#131. NCB7. Palindrome Partitioning
Note: No. of total partitions of an array or string of size n = 2^(n-1)
*/

// 1. Recursion with vector<string> partition

// Time Complexity: O(n * 2^n) where n = s.size();
// - Not O(n * n!)
// - 2^(n-1) possible partitions of string
// - Each palindrome check is O(n)

// Space Complexity: O(n)
// - Recursion stack depth is O(n)
// - Each recursive call stores a partition vector
// - Not counting output space which is O(n * 2^n)

class Solution {
    bool isPalin(string s) {                        // Helper function to check if string is palindrome
        int l = 0, r = s.size()-1;                  // Initialize pointers at start and end
        while(l<r) {                                // Compare characters from both ends
            if(s[l] != s[r]) return false;          // Not a palindrome if characters don't match
            l++; r--;                               // Move pointers inward
        }
        return true;                                // If we reach here, it's a palindrome
    }

    void rec(string s, vector<string> partition, vector<vector<string>> &ans) {
        int n = s.size();                           // Get string length
        if(n==0) {                                  // Base case: if string is empty
            ans.push_back(partition);               // Add current partition to answers
            return;
        }
        for(int i=0; i<n; i++) {                    // Try all possible first partitions
            string subStr = s.substr(0, i+1);       // Get substring from start to i
            if(isPalin(subStr)) {                   // Iff the substring is palindrome we move forward else stop and seek other branches
                partition.push_back(subStr);         // Add to current partition
                rec(s.substr(i+1), partition, ans);  // Recurse with remaining string
                partition.pop_back();                // Backtrack to try other partitions
            }
        }
    }
public:
    vector<vector<string>> partition(string s) {    // Main function
        vector<vector<string>> ans;                 // To store all valid partitions
        rec(s, vector<string>(), ans);              // Start recursion with empty partition
        return ans;                                 // Return all valid partitions
    }
};

// 2. This is a different type of recursion but R.T. is the same as above O(n*2^n)
// this code is correct but ans is storing double values, fix that
// passes in leetcode too

class Solution {
    vector<vector<string>> ans;

    bool isPalin(string s) {
        int l = 0, r = s.size()-1;
        while(l<r) {
            if(s[l] != s[r]) return false;
            l++; r--;
        }
        return true;
    }

    void rec(int i, int prev, int n, string s, vector<string> path) {
        if(i==n) {
            string sub = s.substr(prev, i-prev);
            path.push_back(sub);
            ans.push_back(path);
            return;
        }
        rec(i+1, prev, n, s, path);
        string subStr = s.substr(prev, i-prev);
        path.push_back(subStr);
        rec(i+1, i, n, s, path);
        path.pop_back();
    }
    
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        int n = s.size();
        rec(0, 0, n, s, vector<string>());
        for(int i=0; i<ans.size()/2; i++) {
            bool isPalinPartition = true;
            for(auto s: ans[i]){
                isPalinPartition = isPalinPartition && isPalin(s);
            }
            if(isPalinPartition) res.push_back(ans[i]);
        }
        return res;
    }
};

