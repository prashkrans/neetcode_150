// LC#49. NCAH4. Group Anagrams
// O(n*mlogm) where n = size of strs and m = size of the longest string in strs
// O(n*m) due to the map

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ans;
        unordered_map<string, vector<string>> mp;
        for(int i=0; i<strs.size(); i++) {
            string key = strs[i];
            sort(key.begin(), key.end());
            mp[key].push_back(strs[i]);
        }
        for(auto i: mp)
            ans.push_back(i.second);
        return ans;
    }
};
