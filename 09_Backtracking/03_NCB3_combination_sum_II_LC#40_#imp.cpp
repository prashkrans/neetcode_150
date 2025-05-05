// LC#40. Combination Sum II (Similar to LC#90. Subsets II)


// Approach:
// 1. Sort the input array to handle duplicates efficiently.
// 2. Use backtracking with two choices at each step: [#IMP]
//    - Include the current element and move to position i+1 (can't reuse same element)
//    - Exclude the current element and move to position j where nums[j] != nums[j] (skip all duplicates)
// 3. Use recursion to explore all valid combinations.
// 4. Implement pruning to stop exploration when:
//    - Target becomes negative (combination sum exceeds target)
//    - We've reached the end of the array
// 5. When target becomes zero, we've found a valid combination.

// 1a. Recursion
// O(2^(t/m)) where t = target and m = min val of nums array | 0 ms beats 100 %
// O(t/m)

class Solution {
    vector<vector<int>> ans;

    void rec(int i, vector<int> &nums, int target, vector<int> &path) {
        if(target==0) {
            ans.push_back(path);
            return;
        }
        if(target<0 || i==nums.size()) return; // 1a and 1b differ only in the ordering of base case known as pruning
        path.push_back(nums[i]);
        rec(i+1, nums, target-nums[i], path);
        path.pop_back(); // backtrack

        int j = i;
        while(j<nums.size() && nums[i] == nums[j]) j++; // if skipping an element, skip all its duplicates too
        rec(j, nums, target, path);
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> path;
        sort(candidates.begin(), candidates.end()); // [#IMP] imp to sort here
        rec(0, candidates, target, path);
        return ans;
    }
};


// 1b. 
// O(2^(t/m))
// O(t/m)
// But still gives TLE

class Solution {
    vector<vector<int>> ans;

    void rec(int i, vector<int> &nums, int target, vector<int> &path) {
        if(i==nums.size()) {
            if(target == 0) ans.push_back(path);
            return;
        }
        path.push_back(nums[i]);
        rec(i+1, nums, target-nums[i], path);
        path.pop_back(); // backtrack

        int j = i;
        while(j<nums.size() && nums[i] == nums[j]) j++; // if skipping an element, skip all its duplicates too
        rec(j, nums, target, path);
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> path;
        sort(candidates.begin(), candidates.end()); // imp to sort here
        rec(0, candidates, target, path);
        return ans;
    }
};



// 2. 
// O()
// O()

class Solution {
    set<vector<int>> ans; // using a set since need unique combinations

    void rec(int i, vector<int> &nums, int target, vector<int> &path) {
        if(i==nums.size()) {
            if(target == 0) ans.insert(path);
            return;
        }
        path.push_back(nums[i]);
        rec(i+1, nums, target-nums[i], path);
        path.pop_back(); // backtrack
        rec(i+1, nums, target, path);
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> path;
        sort(candidates.begin(), candidates.end()); // imp to sort here
        rec(0, candidates, target, path);
        return {ans.begin(), ans.end()};
    }
};



// gets TLE:
class Solution {
    void rec(vector<int> &nums, int target, vector<int> path, set<vector<int>> &ans) {
        if(target == 0) {
            sort(path.begin(), path.end());
            ans.insert(path);
            return;
        }
        if(target < 0) return;
        for(int i=0; i<nums.size(); i++) {
            path.push_back(nums[i]);
            vector<int> newNums;
            for(int j=i+1; j<nums.size(); j++) newNums.push_back(nums[j]);
            rec(newNums, target-nums[i], path, ans);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& nums, int target) {
        set<vector<int>> ans;
        sort(nums.begin(), nums.end());
        rec(nums, target, {}, ans);
        return vector<vector<int>>(ans.begin(), ans.end());
    }
};


// Slightly diff and worse than above: gets TLE:
class Solution {
    void rec(vector<int> &nums, int target, vector<int> path, set<vector<int>> &ans) {
        if(target == 0) {
            sort(path.begin(), path.end());
            ans.insert(path);
            return;
        }
        if(target < 0) return;
        for(int i=0; i<nums.size(); i++) {
            path.push_back(nums[i]);
            vector<int> newNums;
            for(int j=0; j<nums.size(); j++) if(i!=j) newNums.push_back(nums[j]);
            rec(newNums, target-nums[i], path, ans);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& nums, int target) {
        set<vector<int>> ans;
        rec(nums, target, {}, ans);
        return vector<vector<int>>(ans.begin(), ans.end());
    }
};