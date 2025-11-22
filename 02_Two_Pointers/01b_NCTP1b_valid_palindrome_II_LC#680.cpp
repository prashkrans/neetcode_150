// LC#680. NCTP1b. Valid Palindrome II

// 1. Naive solution: 
// O(n^2) where n = s.size() | Gets Memory Limit Exceeded
// O(n)

class Solution {
    bool isPalindrome(string s) {
        int l = 0, r = s.size()-1;
        while(l < r) {
            if(s[l++] != s[r--]) return false;
        }
        return true;
    }
public:
    bool validPalindrome(string s) {
       for(int i=0; i<s.size(); i++) {
        string t = s.substr(0, i) + s.substr(i+1); // Note: s.substr(n) is ""
        if(isPalindrome(t)) return true;
       } 
       return isPalindrome(s);
    }
};

/*
Approach: Two Pointers with One Deletion

1. We use a two-pointer approach to check if the string is a palindrome or can become one by deleting at most one character.
2. We initialize two pointers: l at the beginning and r at the end of the string.
3. We move these pointers toward each other, comparing characters at each step.
4. If all characters match until the pointers meet or cross, the string is already a palindrome.
5. If we find a mismatch at any point, we have two possible characters to delete: either at position l or at position r.
6. We check both possibilities using our helper function isPalindrome():
   a. Skip the character at position l and check if s[l+1...r] is a palindrome
   b. Skip the character at position r and check if s[l...r-1] is a palindrome
7. If either of these substrings is a palindrome, we can make the entire string a palindrome by deleting one character.
8. The helper function isPalindrome() uses the same two-pointer technique to check if a substring is a palindrome.
9. This approach works because we only need to handle one deletion at most.
10. The solution has O(n) time complexity because in the worst case, we might traverse nearly the entire string twice.
11. The space complexity is O(1) because we only use a constant amount of extra space regardless of input size.
*/

//  2. Helper iteration inside iteration to get two choices
//  O(n)
//  O(1) due to n, l, r, etc

// Time Complexity: O(n) - where n is the length of the string
// Space Complexity: O(1) - using only constant extra space

class Solution {
    bool isPalindrome(int l, int r, string &s) {                              // Helper function to check if substring is palindrome
        while(l < r) {                                                         // Iterate until pointers meet
            if(s[l++] != s[r--]) return false;                                 // If characters don't match, not a palindrome
        }
        return true;                                                           // If all characters matched, it's a palindrome
    }
public:
    bool validPalindrome(string s) {
        int n = s.size();                                                      // Get string length
        int l = 0, r = n-1;                                                    // Initialize left and right pointers
        while(l < r) {                                                         // Traverse from both ends
            if(s[l] != s[r]) {                                                 // If characters don't match
                return isPalindrome(l+1, r, s) || isPalindrome(l, r-1, s);     // Try skipping either left or right character
            }   // Note: l -> l+1 and r -> r-1
            l++;                                                               // Move left pointer forward
            r--;                                                               // Move right pointer backward
        }
        return true;                                                           // If we reach here, it's already a palindrome
    }
};