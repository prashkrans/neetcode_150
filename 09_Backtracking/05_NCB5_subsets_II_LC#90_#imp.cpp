/* LC#90. NCB5. Subsets II (Similar to LC#40. Combination Sum II)

Approach for "Subsets with Duplicates" Problem:
1. Sort the input array to group duplicates together, making handling duplicates easier.

2. Use recursive backtracking with two choices at each element: [#IMP]
  - Take: Include the current element in the subset and increment i by 1
  - Skip: Skip the current element (and all its duplicates) and increment i to the next different element

3. When including the element:
  - Add it to the current path
  - Recurse to the next position
  - Backtrack by removing the element after recursion

4. When excluding the element:
  - Skip all duplicates of the current element
  - Recurse starting from the next different element

5. Use a path vector to track the current subset being built

6. When reaching the end of the array, add the current path to the results

7. This approach ensures no duplicate subsets by handling all identical elements together
*/

// 1. Recursion without a set
// O(2^n)
// O(2^n): O(n) for the recursion stack and O(2^n) for the ans => O(2^n)

class Solution {
    vector<vector<int>> ans;                       // Store all unique subsets

    void rec(int i, vector<int> &nums, vector<int> path) {
        if(i==nums.size()) {                       // Base case: reached end of array
            ans.push_back(path);                   // Add current path to answer
            return;
        }
        path.push_back(nums[i]);                   // Include current element
        rec(i+1, nums, path);                      // Recurse with current element
        path.pop_back();                           // Backtrack (remove current element)
        int j = i;                                 // Find next different element
        while(j<nums.size() && nums[i] == nums[j]) j++;  // Skip duplicates
        rec(j, nums, path);                        // Recurse without current element
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());            // Sort to group duplicates together
        rec(0, nums, vector<int>());               // Start recursion with empty path
        return ans;                                // Return all unique subsets
    }
};

// or, same as 1. but passing ans by reference

class Solution {
    void rec(int i, vector<int> &nums, vector<int> path, vector<vector<int>> &ans) {
        if(i==nums.size()) {
            ans.push_back(path);
            return;
        }
        path.push_back(nums[i]);
        rec(i+1, nums, path, ans);
        path.pop_back();
        int j = i;
        while(j<nums.size() && nums[i] == nums[j]) j++;
        rec(j, nums, path, ans);
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        rec(0, nums, {}, ans);
        return ans;
    }
};

// 2. Recursion using a set
// O(2^n)
// O(2^n) due to the recursion stack

class Solution {
    set<vector<int>> rec(int i, vector<int> &nums) {
        if(i==nums.size()) { 
            set<vector<int>> st;
            st.insert(vector<int>());
            return st;
            // or return {{}} which is the same as a set of one empty vector
        }
        auto left = rec(i+1, nums);
        auto right = rec(i+1, nums);
        set<vector<int>> res(left);
        for(auto j: right) {
            j.push_back(nums[i]);
            res.insert(j);
        }
        return res;
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        set<vector<int>> ans = rec(0, nums);
        return {ans.begin(), ans.end()};
    }
};