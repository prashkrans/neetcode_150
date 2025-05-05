// LC#78. NCB1. Subsets
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
