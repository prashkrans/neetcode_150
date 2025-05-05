// LC#217. NCAH1. Contains Duplicate


// 1. Using an unordered set
// O(n)
// O(n) 

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> st;
        for(int i=0; i<nums.size(); i++) {
            if(st.find(nums[i]) != st.end()) return true;
            st.insert(nums[i]);
        }
        return false;
    }
};