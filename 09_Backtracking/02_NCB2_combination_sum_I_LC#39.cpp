// LC#39. NCB2. Combination Sum
// Note: all the elements in the input array are distinct hence its easier 
// unlike LC#40 Combination Sum II or LC#90. Subsets II where we need to handle duplicates.


// Note: Recursion 1 and 2 are totally different approaches
// 1. Recursion 1: O(2^t/m) where t = target and m = min val of nums array
// 2. Recursion 2: O(n^t) where t = target where n = size of nums and t is the target

// 1. Recursion better
// O(2^(t/m))
// O(t/m) where t = target and m = minimum value in the array


class Solution {
    vector<vector<int>> ans;
    void rec(int i, vector<int> &nums, int target, vector<int> &path) { // [#IMP] path is passed by reference
        if(target==0) {                             // base case 1
            ans.push_back(path);
            return;
        }
        if(target < 0 || i == nums.size()) return;  // base case 2
        rec(i+1, nums, target, path);               // skip and increment i
        path.push_back(nums[i]);                    // part of take
        rec(i, nums, target-nums[i], path);         // take but not increment i
        path.pop_back();                            // backtrack
    }
public:
    vector<vector<int>> combinationSum(vector<int>& nums, int target) {
        vector<int> path;
        rec(0, nums, target, path);
        return ans;
    }
};


// 2. Recursion but worse (Better to understand this way of recursion but not the best way)
// Time Complexity: O(n^t)
// - For each number in the array, we explore all combinations that sum up to the target.
// - Here, `n` is the size of the array, and `t` is the target value.

// Space Complexity: O(t)
// - The recursion stack can go as deep as the target value `t` in the worst case.

class Solution {
    void rec(vector<int> &nums, int target, vector<int> path, set<vector<int>> &ans) {
        if(target == 0) {                               // Base case: target is achieved
            sort(path.begin(), path.end());             // Sort the path to ensure uniqueness
            ans.insert(path);                           // Insert the sorted path into the set
            return;
        }
        if(target < 0) return;                          // Base case: target is negative
        for(int i = 0; i < nums.size(); i++) {          // Iterate through all numbers
            path.push_back(nums[i]);                    // Add the current number to the path
            rec(nums, target - nums[i], path, ans);     // Recurse with the reduced target
            path.pop_back();                            // Backtrack by removing the last number
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& nums, int target) {
        set<vector<int>> ans;                           // Use a set to store unique combinations
        rec(nums, target, {}, ans);                     // Start the recursion
        return vector<vector<int>>(ans.begin(), ans.end()); // Convert the set to a vector and return
    }
};