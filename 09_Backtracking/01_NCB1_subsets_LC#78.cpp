/* LC#78. NCB1. Subsets

This problem can be solved by two methods:
1. 	Bit manipulation (Bit masking type 2)
2. 	Recursion
Both methods are important
*/

// 1a. Recursive function that returns a 2D vector
// O(2^n)
// O(2^n) due to the res vector

class Solution {
    vector<vector<int>> rec(int i, vector<int> &nums) {
        if(i==nums.size()) return vector<vector<int>> (1, vector<int>());
        vector<vector<int>> res = rec(i+1, nums);
        int size = res.size();
        for(int j=0; j<size; j++) {
            vector<int> curr = res[j];
            curr.push_back(nums[i]);
            res.push_back(curr);
        }
        return res;
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        return rec(0, nums);
    }
};

// 1b. Void type recursion
// O(2^n) | 0ms, beats 100%
// O(2^n) due to the ans vector

class Solution {
    void rec(int i, vector<int>& nums, vector<int> currSet, vector<vector<int>> &ans) { // both vector<int> &currSet and vector<int> currSet works
        if(i == nums.size()) {
            ans.push_back(currSet);
            return;
        }
        currSet.push_back(nums[i]);
        rec(i + 1, nums, currSet, ans);
        currSet.pop_back();
        rec(i + 1, nums, currSet, ans);
    } 
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> currSet;
        rec(0, nums, currSet, ans);
        return ans;
    }
};

/*
### Approach 2: Bitmask Enumeration for Power Set Generation
1. Observe that a set with n elements has exactly two raised to n possible subsets.
2. Represent each subset using a binary number where each bit indicates inclusion or exclusion.
3. Iterate from zero to two raised to n minus one to cover all bitmask combinations.
4. For each bitmask, check every bit position corresponding to each element index.
5. If a bit is set, include the corresponding element in the current subset.
6. Store each constructed subset into the final answer list.
7. This approach uses bit manipulation, enumeration, and combinatorial properties.
*/

// Method 2. Bitmask Enumeration for Power Set Generation (My original solution after a hint)
// Time Complexity: o(n * 2^n)
// Space Complexity: o(n * 2^n)

class Solution {                                                                           
public:                                                                                   
    vector<vector<int>> subsets(vector<int>& nums) {                                      // Generates all possible subsets
        vector<vector<int>> ans;                                                          // Stores all subsets
        int n = nums.size();                                                              // Number of elements
        int total = 1 << n;  // = 1 * 2^n = 2^n                                           // Total subsets count using bitmasking
        for(int i = 0; i < total; i++) {                                                  // Iterate over all bitmasks
            vector<int> currSet;                                                          // Stores current subset
            for(int j = 0; j < n; j++) {                                                  // Check each bit position
                if(i & 1 << j) currSet.push_back(nums[j]);                                // Include element if bit is set
            }
            ans.push_back(currSet);                                                       // Add generated subset to answer
        }
        return ans;                                                                       // Return all subsets
    }
};
