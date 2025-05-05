
/* LC# 47. NCB4b. Permutations II

Creating a new vector is expensive, so we should avoid it, but it becomes easier to understand.

A. without creating a new vector (prefer this approach)
B. with creating a new vector


*/
// A1. Void type recursion without creating a new vector
// Time Complexity: O(n! * n)
// - Generating all unique permutations takes O(n!) time.
// - For each permutation, operations like swapping and backtracking take O(n) time.
// - Overall complexity is O(n! * n).

// Space Complexity: O(n)
// - The recursion stack can go as deep as n, where n is the size of the input array.
// - Additional space is used for the `path` vector, which can also grow up to size n.

class Solution {
    void rec(int i, vector<int> &nums, vector<int> path, vector<vector<int>> &ans) {
        if(i == nums.size()) {                            // Base case: index reached the end of the array
            ans.push_back(path);                          // Add the completed permutation to the result
            return;
        }
        unordered_set<int> st;                            // Set to track used numbers at the current level
        for(int j = i; j < nums.size(); j++) {            // Iterate through all elements starting from index i
            if(st.find(nums[j]) == st.end()) {            // Skip duplicates at the current level
                st.insert(nums[j]);                       // Mark the number as used
                swap(nums[i], nums[j]);                   // Swap the current element with the element at index i
                path.push_back(nums[i]);                  // [#IMP] nums[j] is now nums[i]. Add the current element to the path
                rec(i + 1, nums, path, ans);              // Recurse for the next index
                swap(nums[i], nums[j]);                   // Backtrack Step 1. Undo the swap
                path.pop_back();                          // Backtrack Step 2. Remove the last element from the path
            }
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ans;                          // Result vector to store all unique permutations
        rec(0, nums, vector<int>(), ans);                 // Start the recursion
        return ans;                                       // Return the result
    }
};

// B1. Void type recursion with creating a new vector
// O(n! * n^2) ~ O(n!) where n = nums.size();
// O(n! * n) ~ O(n!) wastes space

class Solution {
    vector<vector<int>> ans;
    void rec(vector<int> &nums, vector<int> path) {
        if(nums.empty()) {
            ans.push_back(path);
            return;
        }
        unordered_set<int> st;
        for(int i=0; i<nums.size(); i++) {     
            if(st.find(nums[i]) != st.end()) continue;
            st.insert(nums[i]);
            vector<int> newNums(nums);          // or,  vector<int> newNums;                
            newNums.erase(newNums.begin() + i); // for(int j=0; j<nums.size(); j++) if(j!=i) newNums.push_back(nums[j]);
            path.push_back(nums[i]);
            rec(newNums, path);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        rec(nums, vector<int>());
        return ans;
    }
};