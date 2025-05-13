/* LC#567. Permutation in String

Found another method yet to test it tho
freqMap1
while r < m
if(s2[r] is not found in freqMap1) increment l to r and clear freqMap2
if(s2[r] is found in freqMap1) freqMap2[s[r]]++ then match freqMap1 with freqMap2
TODO 

/* Approach 1: Brute Force with Sorting
1. We are given two strings, s1 and s2. We need to determine whether s2 contains a
   permutation of s1.
2. Since the order of characters in a permutation does not matter, we sort s1
   so it can be easily compared with sorted substrings of s2.
3. We first check if s1 is longer than s2; if it is, we return false because
   a longer string cannot be a substring of a shorter one.
4. Then, we loop through s2, considering all substrings of the same length as s1
   by moving a window of size n from left to right.
5. For each such substring, we sort it and compare it to the sorted version of s1.
6. If any sorted substring matches the sorted s1, it means s2 contains a permutation
   of s1, so we return true.
7. If no such substring exists after completing the loop, we return false indicating
   no permutation of s1 is a substring of s2.
*/ 

// 1: Brute Force with Sorting (Easier to understand but less efficient)
// Time Complexity: O(m * n log n + n log n) ~ O(mnlogn), where m = s2.length(), n = s1.length()
// Space Complexity: O(n), for the substring storage in each iteration

class Solution {
public:
   bool checkInclusion(string s1, string s2) {
      int n = s1.size();                          // length of s1
      int m = s2.size();                          // length of s2
      sort(s1.begin(), s1.end());                 // sort s1 to compare later
      if(n > m) return false;                     // if s1 is longer than s2, no permutation possible
      for(int i=0; i<=m-n; i++) {                 // iterate over all substrings of s2 of length n
            string subStr = s2.substr(i, n);        // take substring of length n starting at i
            sort(subStr.begin(), subStr.end());     // sort the substring for comparison
            if(s1 == subStr) return true;           // if sorted substring matches sorted s1, return true
      }
      return false;                               // no permutation match found in s2
   }
};

/*
### Approach 2: Sliding Window with Frequency Maps (Prefer this method)
1. Use two frequency maps:
   - `freqMap1` to store the character frequencies of `s1`.
   - `freqMap2` to store the character frequencies of the current window in `s2`.
2. Initialize the window size to the length of `s1` (`n`).
3. Populate `freqMap1` with the frequencies of characters in `s1`.
4. Populate `freqMap2` with the frequencies of the first `n` characters in `s2`.
5. Check if the first window matches `freqMap1` using the `isMatching` function.
6. Slide the window through `s2`:
   - Add the new character at the right end of the window to `freqMap2`.
   - Remove the character at the left end of the window from `freqMap2`.
   - Check if the current window matches `freqMap1`.
7. If a matching window is found, return `true`.
8. If no matching window is found after sliding through `s2`, return `false`.
9. The solution has O(m) time complexity and O(1) space complexity.
*/

// 2. Approach: Sliding Window with Frequency Count (My custom code)
// Time Complexity: O((n+m) * 26) ~ O(n+m) ~ O(m) since m > n | 0ms beats 100%
// - The `isMatching` function iterates over at most 26 characters (constant time).
// - The sliding window iterates through the string `s2` of length `m`.
// - Overall complexity is O(m), where m is the length of `s2`.

// Space Complexity: O(1)
// - The unordered maps store at most 26 characters (constant space).

class Solution {
   bool isMatching(unordered_map<char, int> &mp1, unordered_map<char, int> &mp2) {
       for(auto i: mp1) {                              // Iterate over all character-frequency pairs in mp1
           if(mp1[i.first] != mp2[i.first]) return false; // Check if frequencies match in both maps
       }
       return true;                                    // Return true if all frequencies match
   }
public:
   bool checkInclusion(string s1, string s2) {
       int n = s1.size(), m = s2.size();               // Lengths of s1 and s2
       if(n > m) return false;                         // If s1 is longer than s2, return false
       unordered_map<char, int> freqMap1;              // Frequency map for s1
       unordered_map<char, int> freqMap2;              // Frequency map for the current window in s2
       for(int i=0; i<n; i++) freqMap1[s1[i]]++;       // Populate freqMap1 with frequencies of s1
       int l = 0, r = n;                               // Initialize window boundaries
       for(int i=0; i<r; i++) freqMap2[s2[i]]++;       // Populate freqMap2 with the first window in s2
       if(isMatching(freqMap1, freqMap2)) return true; // Check if the first window matches
       while(r < m) {                                  // Slide the window through s2
           freqMap2[s2[r]]++;                          // Add the new character to the window
           freqMap2[s2[l]]--;                          // Remove the leftmost character from the window
           if(isMatching(freqMap1, freqMap2)) return true; // Check if the current window matches
           r++;                                        // Move the right pointer
           l++;                                        // Move the left pointer
       }
       return false;                                   // Return false if no matching window is found
   }
};
   