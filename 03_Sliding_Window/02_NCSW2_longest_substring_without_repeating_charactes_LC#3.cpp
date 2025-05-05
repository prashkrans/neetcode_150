// LC#3. Longest Substring Without Repeating Characters

/*
Approach: Sliding Window with Hash Map

1. We use a sliding window approach with two pointers to find the longest substring without repeating characters.
2. The left pointer (l) and right pointer (r) define the current window of characters we are considering.
3. We use a hash map to store the most recent position of each character we've seen so far.
4. We initialize our answer variable to handle empty strings, and both pointers start at the beginning of the string.
5. For each character at the right pointer, we check if it exists in our current window by using the hash map.
6. If the character exists AND its last position is within our current window (>= l), we must shrink our window.
7. We shrink by moving the left pointer to one position after the last occurrence of the duplicate character.
8. We always update the position of the current character in the hash map to its current index.
9. After each iteration, we calculate the current window size (r-l+1) and update the maximum length found so far.
10. This approach ensures we only need to scan the string once while dynamically adjusting our window whenever we encounter repeating characters.
11. The sliding window technique efficiently maintains the property that at any point, the characters between l and r form a substring without repeating characters.
*/

// Sliding Window with Hash Map
// Time Complexity: O(n) - where n is the length of the string s
// Space Complexity: O(min(m, n)) - where m is the size of the character set, at most O(n) due to the map mp

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int ans = s.empty() ? 0 : 1;                        // Initialize answer based on whether string is empty
        int l = 0, r = 0;                                   // Initialize left and right pointers for the sliding window
        unordered_map<char, int> mp;                        // Map to store the most recent index of each character
        while(r < s.size()) {                               // Iterate through the string
            if(mp.count(s[r]) && mp[s[r]] >= l)             // [#IMP >=] If character exists in current window
                l = mp[s[r]] + 1;                           // Move left pointer to position after the duplicate
            mp[s[r]] = r;                                   // Update the position of the current character
            ans = max(ans, r - l + 1);                      // Update answer with max length found so far
            r++;                                            // Move right pointer to next character
        }
        return ans;                                         // Return the length of longest substring without repeats
    }
};