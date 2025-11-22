/* Given a string s, which may contain duplicate characters, your task is to generate 
and return an array of all unique permutations of the string. 
You can return your answer in any order.

https://www.geeksforgeeks.org/problems/permutations-of-a-given-string2041/0

### Approach 1: Backtracking with In-place Swapping and Duplicate Handling
1. Use a recursive function `rec` to generate all unique permutations of the input string.
2. Base case:
   - If the current index `i` reaches the end of the string, add the current permutation to the result.
3. For each index `j` starting from `i`:
   - Use a set to skip duplicate characters at the current recursion level.
   - Swap the character at index `i` with the character at index `j`.
   - Recurse for the next index (`i + 1`) with the updated path.
   - Backtrack by undoing the swap.
4. The recursion explores all unique permutations by swapping characters at each level and skipping duplicates.

### Notes:
- This approach avoids creating new strings at each step, making it more efficient than approaches that copy the string.
- The use of a set ensures that duplicate permutations are skipped at each recursion level.
*/

// 1. Recursion with backtracking with in-place swapping
// Time Complexity: O(n! * n)
// - Generating all unique permutations takes O(n!) time.
// - For each permutation, operations like swapping and backtracking take O(n) time.
// - Overall complexity is O(n! * n).

// Space Complexity: O(n)
// - The recursion stack can go as deep as n, where n is the size of the string.
// - Additional space is used for the `path` string, which can also grow up to size n.

class Solution {
    void rec(int i, string &s, string path, vector<string> &ans) {
        if(i == s.size()) {                              // Base case: reached the end of the string
            ans.push_back(path);                         // Add the completed permutation to the result
            return;
        }
        unordered_set<char> st;                          // Set to track used characters at the current level
        for(int j = i; j < s.size(); j++) {              // Iterate through all characters starting from index i
            if(st.find(s[j]) != st.end()) continue;      // Skip duplicates at the current level
            st.insert(s[j]);                             // Mark the character as used
            swap(s[i], s[j]);                            // Swap the current character with the character at index i
            rec(i + 1, s, path + s[i], ans);             // Recurse for the next index with the updated path
            swap(s[i], s[j]);                            // Backtrack by undoing the swap
        }
    }
public:
    vector<string> findPermutation(string &s) {
        vector<string> ans;                              // Result vector to store all unique permutations
        rec(0, s, "", ans);                              // Start the recursion
        return ans;                                      // Return the result
    }
};

/*
### Approach: Backtracking with Substring Creation
1. Use a recursive function `rec` to generate all unique permutations of the input string.
2. Base case:
   - If the input string `s` is empty, add the current path to the result.
3. For each character in the string:
   - Use a set to skip duplicate characters at the current recursion level.
   - Create a new string by excluding the current character.
   - Recurse with the reduced string and the updated path.
4. The recursion explores all unique permutations by creating substrings at each level and skipping duplicates.

### Notes:
- This approach is less efficient than in-place swapping because it creates new strings at each step.
- The use of a set ensures that duplicate permutations are skipped at each recursion level.
*/

// 2. Recursion with backtracking with creating a new string
// Time Complexity: O(n! * n)
// - Generating all unique permutations takes O(n!) time.
// - For each permutation, operations like creating substrings and concatenating strings take O(n) time.
// - Overall complexity is O(n! * n).

// Space Complexity: O(n! * n)
// - The result vector `ans` stores all unique permutations, which can be up to O(n!) permutations, each of size n.
// - The recursion stack can go as deep as n, where n is the size of the string.
// - Additional space is used for creating substrings and concatenating strings.

class Solution {
    void rec(string s, string path, vector<string> &ans) {
        if(s.empty()) {                                  // Base case: no characters left to permute
            ans.push_back(path);                         // Add the completed permutation to the result
            return;
        }
        unordered_set<char> st;                          // Set to track used characters at the current level
        for(int i = 0; i < s.size(); i++) {              // Iterate through all characters in the string
            if(st.find(s[i]) != st.end()) continue;      // Skip duplicates at the current level
            st.insert(s[i]);                             // Mark the character as used
            string subStr = s.substr(0, i) + s.substr(i + 1); // Create a new string excluding the current character
            rec(subStr, path + s[i], ans);               // Recurse with the reduced string and updated path
        }
    }
public:
    vector<string> findPermutation(string &s) {
        vector<string> ans;                              // Result vector to store all unique permutations
        rec(s, "", ans);                                 // Start the recursion
        return ans;                                      // Return the result
    }
};