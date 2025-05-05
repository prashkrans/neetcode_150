// Method 1. Odd and even palindrome formation (Two pointers method)
// Running time: O(2*n^2) ~ O(n^2) due to while loop inside the for loop
// Auxiliary space: O(1) due to variables like startingIndex, maxLength, etc. 
// Note: Use while loop inside the for loops. Don't use for loops inside

class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        int count = 0;
        for(int i=0; i<n; i++) {
            int left = i;
            int right = i;
            while(left>=0 && right<n && s[left] == s[right]) {
                count++; 
                left--; right++;
            }

            left = i; 
            right = i+1;
            while(left>=0 && right<n && s[left] == s[right]) {
                count++; 
                left--; right++;
            }
        }
        return count;
    }
};

    // Both the base cases are covered in the for loop:
    // if(s.size()==1) return 1;
    // if(s.size()==2) return (s[0] == s[1]) ? 3 : 2; 
    // e.g. aa = 3 => a, a & aa | bc = 2 => b, c
    