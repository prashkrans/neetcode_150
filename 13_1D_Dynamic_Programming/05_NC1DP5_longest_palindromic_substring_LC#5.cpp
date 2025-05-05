/**
LC#5. NC1DP5. Longest Palindromic Substring

Method 1. Odd and even palindrome formation (Two pointers method) - Easier to understand

TODO:
Method 2. Dynamic Programming - Build a 2D table where DP[i][j] indicates whether substring from index i to j is a palindrome. 
Fill this table bottom-up to find the longest palindrome.

Method 3. Manacher's Algorithm - A specialized algorithm that solves this problem in O(n) time by reusing previously computed 
information about palindromes.

*/

// Method 1. Odd and even palindrome formation (Two pointers method)
// Running time: O(2*n^2) ~ O(n^2) due to while loop inside the for loop
// Auxiliary space: O(1) due to variables like startingIndex, maxLength, etc. 
// Note: Use while loop inside the for loops. Don't use for loops inside


class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if(n == 1) return s;                          // Single character is always a palindrome
        else if(n==2) {
            if(s[0]==s[1]) return s;                  // Two identical chars form a palindrome
            else return s.substr(0, 1);               // Return first char if no palindrome
        }
        else {
            int startingIndex = 0;
            int maxLength = 1;                        // [#IMP] - Initialize with 1 to handle single char case
            
            // Check for odd-length palindromes (centered at each character)
            for(int i=0; i<n; i++) {
                int currLen = 1;                      // Start with center character
                int j = i-1;                          // Left pointer
                int k = i+1;                          // Right pointer
                while(j>=0 && k<n && s[j] == s[k]) {  // Expand outward while palindrome
                    currLen += 2;                     // Add 2 characters to length
                    if(maxLength<currLen) {
                        maxLength = currLen;          // Update if longer palindrome found
                        startingIndex = j;            // Update starting index
                    }
                    j--; k++;                         // Continue expanding
                }
            }
            
            // Check for even-length palindromes (centered between characters)
            for(int i=0; i<n-1; i++) {
                int currLen = 0;                      // Start with 0 as no center character
                int j = i;                            // Left pointer
                int k = i+1;                          // Right pointer
                while(j>=0 && k<n && s[j] == s[k]) {  // Expand outward while palindrome
                    currLen += 2;                     // Add 2 characters to length
                    if(maxLength<currLen) {
                        maxLength = currLen;          // Update if longer palindrome found
                        startingIndex = j;            // Update starting index
                    }
                    j--; k++;                         // Continue expanding
                }
            }
            return s.substr(startingIndex, maxLength); // Extract the longest palindrome
        }
    }
};

// Method 1b. Compact form of the above code

class Solution {
    public:
        string longestPalindrome(string s) {
            int resLen = 0, resIdx = 0;
    
            for (int i = 0; i < s.size(); i++) {
                // odd length
                int l = i, r = i;
                while (l >= 0 && r < s.size() && s[l] == s[r]) {
                    if (r - l + 1 > resLen) {
                        resIdx = l;
                        resLen = r - l + 1;
                    }
                    l--;
                    r++;
                }
    
                // even length
                l = i;
                r = i + 1;
                while (l >= 0 && r < s.size() && s[l] == s[r]) {
                    if (r - l + 1 > resLen) {
                        resIdx = l;
                        resLen = r - l + 1;
                    }
                    l--;
                    r++;
                }
            }
    
            return s.substr(resIdx, resLen);
        }
    };