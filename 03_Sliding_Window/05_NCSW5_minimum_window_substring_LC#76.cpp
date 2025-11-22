/*LC#76. Minimum Window Substring

Example 1: [#IMP] - Use this example to come up with the solution
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

### Approach: Sliding Window with Two Frequency Maps

1. We use a sliding window approach with two pointers (l and r) to find the minimum substring of s that contains all characters of t.
2. We maintain two frequency maps: freqMap1 for string t and freqMap2 for the current window in string s.
3. First, we populate freqMap1 with the frequency of each character in string t.
4. We expand the window by moving the right pointer and updating freqMap2 with the characters we encounter.
5. The isMatched function checks if the current window contains all characters from t with sufficient frequency.
6. Once we find a valid window that contains all characters from t, we try to minimize it by moving the left pointer.
7. While maintaining a valid window, we increment the left pointer and remove the corresponding character from freqMap2.
8. We keep track of the minimum window length and its starting position throughout this process.
9. After the entire string is processed, we return the minimum window substring or an empty string if no valid window is found.
10. This approach ensures we only need to scan the string s once, making it an efficient O(n + m) solution.
11. The key insight is that we don't need to restart the search after finding a valid window; we can just contract from the left and expand from the right.
*/

// Sliding Window with Two Frequency Maps (Prefer this and learn it)
// Time Complexity: O(n) - where n is the length of string s
// Space Complexity: O(k) - where k is the number of distinct characters (at most 52 for uppercase and lowercase letters)

class Solution {
    bool isMatched(unordered_map<char, int> &mp1, unordered_map<char, int> &mp2) {   // Function to check if window contains all required characters
        for(auto i: mp1) {                                                           // Iterate through each character in target string
            char ch = i.first;                                                       // Get current character
            if(mp1[ch] > mp2[ch]) return false;  // [#IMP] not mp1[ch] != mp2[ch]    // If frequency in window is less than required, return false
        }
        return true;                                                                 // All characters are covered with sufficient frequency
    }
public:
    string minWindow(string s, string t) {
        int n = s.size();                                                            // Length of string s
        int m = t.size();                                                            // Length of string t
        if(n < m) return "";                                                         // If s is shorter than t, no solution possible
        int startMin = -1;                                                           // Start index of minimum window substring
        int minLen = INT_MAX;                                                        // Length of minimum window substring
        int l = 0, r = 0;                                                            // Initialize left and right pointers for sliding window
        unordered_map<char, int> freqMap1;                                           // Frequency map for characters in t
        for(int i=0; i<m; i++) freqMap1[t[i]]++;                                     // Fill frequency map for string t
        unordered_map<char, int> freqMap2;                                           // Frequency map for current window in s
        while(r < n) {                                                               // Iterate through string s with right pointer
            freqMap2[s[r]]++;                                                        // Include current character in window's frequency map
            while(isMatched(freqMap1, freqMap2)) {                                   // While current window contains all required characters
                if(r - l + 1 < minLen) {                                             // If current window is smaller than minimum window found
                    minLen = r - l + 1;                                              // Update minimum length
                    startMin = l;                                                    // Update start index of minimum window
                }
                freqMap2[s[l]]--;                                                    // Remove leftmost character from window's frequency map
                l++;                                                                 // Contract window from left
            }
            r++;                                                                     // Expand window from right
        }
        return (minLen == INT_MAX) ? "" : s.substr(startMin, minLen);                // Return minimum window substring or empty string if not found
    }
};

// Sliding Window with Two Frequency Maps (same as above)
// Time Complexity: O(n + m) - where n is the length of string s and m is the length of string t
// Space Complexity: O(k) - where k is the number of distinct characters in string t (at most 52 for uppercase and lowercase letters)

class Solution {
    bool isMatched(unordered_map<char, int> &mp1, unordered_map<char, int> &mp2) {  // Function to check if all characters in t are covered in current window
        for(auto i: mp1) {                                                           // Iterate through each character in t's frequency map
            char ch = i.first;                                                       // Get current character
            if(mp1[ch] > mp2[ch]) return false;                                      // If character frequency in window is less than required, return false
        }
        return true;                                                                 // All characters are covered with sufficient frequency
    }
public:
    string minWindow(string s, string t) {
        int n = s.size();                                                            // Length of string s
        int m = t.size();                                                            // Length of string t
        if(n < m) return "";                                                         // If s is shorter than t, no solution possible
        int startMin = -1;                                                           // Start index of minimum window substring
        int minLen = INT_MAX;                                                        // Length of minimum window substring
        int l = 0, r = 0;                                                            // Initialize left and right pointers for sliding window
        unordered_map<char, int> freqMap1;                                           // Frequency map for characters in t
        for(int i=0; i<m; i++) freqMap1[t[i]]++;                                     // Fill frequency map for string t
        unordered_map<char, int> freqMap2;                                           // Frequency map for current window in s
        while(r < n && !isMatched(freqMap1, freqMap2)) {                             // Expand window until all characters are matched or end of string
            freqMap2[s[r]]++;                                                        // Include current character in window's frequency map
            while(isMatched(freqMap1, freqMap2)) {                                   // While current window contains all required characters
                if(r - l + 1 < minLen) {                                             // If current window is smaller than minimum window found
                    minLen = r - l + 1;                                              // Update minimum length
                    startMin = l;                                                    // Update start index of minimum window
                }
                freqMap2[s[l]]--;                                                    // Remove leftmost character from window's frequency map
                l++;                                                                 // Contract window from left
            }
            r++;                                                                     // Expand window from right
        }
        return (minLen == INT_MAX) ? "" : s.substr(startMin, minLen);                // Return minimum window substring or empty string if not found
    }
};