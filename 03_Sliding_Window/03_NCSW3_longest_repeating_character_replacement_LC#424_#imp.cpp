/* LC#424. Longest Repeating Character Replacement

Main logic: (current window size - max frequency) <= replacements allowed

Approach: Sliding Window with Frequency Count

1. We use two pointers, left and right, to define a sliding window over the string.
2. As we move the right pointer, we add the current character to a frequency map that tracks letter counts.
3. We calculate the most frequent character in the window to check how many changes are needed.
4. If the number of characters to replace (window size minus max frequency) exceeds k, the window is invalid.
5. To fix this, we move the left pointer forward and reduce the count of the character at the left pointer.
6. We continue updating the answer with the size of the largest valid window seen so far.
7. The maxFrequency function simply finds the highest frequency in the current window using a loop.
8. The idea is that we can replace at most k characters in the window to make all letters the same.
9. This approach ensures we always track a valid window and adjust only when the replacement limit is crossed.
10. It runs in linear time relative to string length and uses constant space for the frequency array.
*/

/* 1a. Sliding window using vector of 26 chars and while loop
Time Complexity: O(26 * n) = O(n), where n is the length of the string.
Space Complexity: O(1), since frequency map size is constant (26 letters).
*/

class Solution {
    int maxFrequency(vector<int> &map) {
        int maxF = 0;                                 // maxF stores the highest frequency in the current window
        for(int i=0; i<26; i++) maxF = max(maxF, map[i]); // iterate over all letters to find max frequency
        return maxF;                                  // return max frequency found
    }
public:
    int characterReplacement(string s, int k) {
        if(s.empty()) return 0;                       // handle edge case for empty string
        int ans = 0;                                  // ans stores the result: max valid window length
        int l = 0, r = 0;                             // l and r are left and right window boundaries
        vector<int> map(26, 0);                       // frequency map for 26 uppercase letters
        while(r < s.size()) {                         // iterate while right pointer is within bounds
            map[s[r] - 'A']++;                        // include current char in window frequency
            if(r - l + 1 - maxFrequency(map) > k) {   // if replacements exceed k, window is invalid
                map[s[l] -  'A']--;                   // shrink window from left and update frequency
                l++;                                  // move left pointer forward
            }
            ans = max(ans, r - l + 1);                // update maximum valid window size
            r++;                                      // move right pointer forward
        }
        return ans;                                   // return result
    }
};


/* 1b. Sliding window using an unordered_map for 26 chars and a for loop
Time Complexity: O(26 * n) = O(n), since each character is processed at most twice and maxFrequency checks 26 elements.
Space Complexity: O(1), because unordered_map has at most 26 keys for uppercase English letters.
*/

class Solution {
    int maxFrequency(unordered_map<char, int> &mp) {
        int maxFreq = 0;                                // Tracks the highest frequency of any character in the current window
        for(auto i: mp)                                 // Iterate over all character-frequency pairs
            maxFreq = max(maxFreq, i.second);           // Update maxFreq if current frequency is higher
        return maxFreq;                                 // Return the highest frequency found
    }
public:
    int characterReplacement(string s, int k) {
        if(s.empty()) return 0;                         // Handle edge case for empty string
        int ans = 0;                                    // Stores the maximum valid window length found
        int n = s.size();                               // Length of the input string
        int l = 0, r = 0;                               // Window boundaries
        unordered_map<char, int> freqMap;               // Frequency map to count characters in the window
        for(int r = 0; r < n; r++) {                    // Expand window by moving right pointer
            freqMap[s[r]]++;                            // Increment frequency of the current character
            if(r - l + 1 - maxFrequency(freqMap) > k) { // Check if more than k replacements are needed
                freqMap[s[l]]--;                        // Shrink window by reducing left character count
                l++;                                    // Move left pointer right
            }
            ans = max(ans, r - l + 1);                  // Update max answer if current window is larger
        }
        return ans;                                     // Return the longest valid substring length
    }
};


// 1c. Same as 1a but using double while loops
// Passes all test cases, including edge cases but yet to understand the solution
// Time Complexity: O(n)
// - Each character is processed at most twice: once when expanding the window and once when shrinking it.
// - The `maxFrequency` function iterates over the frequency map, but since the map size is constant (at most 26 keys for uppercase letters), this is O(1).
// - Overall complexity is O(n), where n is the length of the string.

// Space Complexity: O(1)
// - The unordered_map stores at most 26 keys for uppercase English letters, which is constant space.

class Solution {
    int maxFrequency(unordered_map<char, int> &mp) {
        int maxFreq = 0;                                // Tracks the highest frequency of any character in the current window
        for(auto i: mp)                                 // Iterate over all character-frequency pairs
            maxFreq = max(maxFreq, i.second);           // Update maxFreq if current frequency is higher
        return maxFreq;                                 // Return the highest frequency found
    }
public:
    int characterReplacement(string s, int k) {
        if(s.empty()) return 0;                         // Handle edge case for empty string
        int ans = 0;                                    // Stores the maximum valid window length found
        int l = 0, r = 0;                               // Window boundaries
        unordered_map<char, int> freqMap;               // Frequency map to count characters in the window
        while(r < s.size()) {                           // Expand the window by moving the right pointer
            freqMap[s[r]]++;                            // Increment frequency of the current character
            while(r - l + 1 - maxFrequency(freqMap) > k) { // Check if more than k replacements are needed
                freqMap[s[l]]--;                        // Shrink the window by reducing the count of the left character
                l++;                                    // Move the left pointer right
            }
            ans = max(ans, r - l + 1);                  // Update the maximum valid window length
            r++;                                        // Move the right pointer right
        }
        return ans;                                     // Return the longest valid substring length
    }
};