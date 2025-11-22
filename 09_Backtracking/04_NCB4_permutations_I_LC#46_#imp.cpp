/* LC#46. NCB4. Permutations

Creating a new vector is expensive, so we should avoid it, but it becomes easier to understand.

A. without creating a new vector (prefer this approach)
B. with creating a new vector


*/

// A1. Void type recursion without creating a new vector
// Time Complexity: O(n! * n) ~ O(n!) since n! is the dominant term.
// - Generating all permutations takes O(n!) time.
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
        for(int j = i; j < nums.size(); j++) {            // Iterate through all elements starting from index i
            swap(nums[i], nums[j]);                       // Swap the current element with the element at index i
            path.push_back(nums[i]);                      // [#IMP] nums[j] is now nums[i]. Add the current element to the path
            rec(i + 1, nums, path, ans);                  // Recurse for the next index
            
            swap(nums[i], nums[j]);                       // Backtrack Step 1. Undo the swap
            path.pop_back();                              // Backtrack Step 2. Remove the last element from the path
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;                          // Result vector to store all permutations
        rec(0, nums, vector<int>(), ans);                 // Start the recursion
        return ans;                                       // Return the result
    }
};


// B1. Void type recursion
// O(n! * n^2) ~ O(n!) where n = nums.size();
// O(n! * n) ~ O(n!) wastes space

class Solution {
    vector<vector<int>> ans;
    void rec(vector<int> &nums, vector<int> path) {
        if(nums.empty()) {
            ans.push_back(path);
            path.clear();                   // This is not necessary, but it is good practice to clear the path
            return;
        }
        for(int i=0; i<nums.size(); i++) {  // Here, its not optimal to create a new vector but is easier to understand
            vector<int> newNums; // or, vector<int> newNums(nums); newNums.erase(newNums.begin() + i);
            for(int j=0; j<nums.size(); j++) {
                if(j!=i) newNums.push_back(nums[j]);
            }
            path.push_back(nums[i]);
            rec(newNums, path);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        // vector<int>path; rec(nums, path) fails if rec uses vector<int> &path
        rec(nums, vector<int>());
        return ans;
    }
};


// B2a. Recursion that returns vector<vector<int>> 
// O(n! * n^2) ~ O(n!) where n = nums.size();
// O(n! * n) ~ O(n!) wastes space
// Tricky but great

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        if(nums.size()==0) return vector<vector<int>> (1, vector<int>()); // or return {{}}; [verified];
        vector<vector<int>> ans;
        for(int i=0; i<nums.size(); i++) {
            vector<int> newNums(nums);
            newNums.erase(newNums.begin() + i);
            vector<vector<int>> res = permute(newNums);
            for(auto j: res) {
                j.push_back(nums[i]);
                ans.push_back(j);
            }
        }
        return ans;
    }
};

// or,  B2b. same as above but with n == 1 check

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        if(n==1) return vector<vector<int>> (1, vector<int>(1, nums[0])); // or {{nums[0]}};
        vector<vector<int>> ans;
        for(int i=0; i<n; i++) {
            vector<int> newNums(nums);
            newNums.erase(newNums.begin() + i);
            vector<vector<int>> res = permute(newNums);
            for(auto j: res) {
                j.push_back(nums[i]);
                ans.push_back(j);
            }
        }
        return ans;
    }
};
