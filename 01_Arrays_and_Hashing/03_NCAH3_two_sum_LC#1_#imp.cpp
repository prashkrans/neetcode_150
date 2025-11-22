// LC#1. NCAH3. Two Sum

// 1. Using an unordered_map to store nums[i] and i
// O(n)
// O(n)

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> uMap;
        vector<int> ans;
        for(int i=0; i<nums.size(); i++) {
            if(uMap.count(target - nums[i])) {
                ans.push_back(uMap[target-nums[i]]);
                ans.push_back(i);
                break;
            }
            else uMap[nums[i]] = i;
        }
        return ans;
    }
};

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans(2, -1);
        unordered_map<int, int> mp;
        for(int i=0; i<nums.size(); i++) {
            if(mp.find(target-nums[i]) != mp.end()) {
                ans[0] = mp[target-nums[i]];
                ans[1] = i;
                break;
            }
            mp[nums[i]] = i;
        }
        return ans;
    }
};
