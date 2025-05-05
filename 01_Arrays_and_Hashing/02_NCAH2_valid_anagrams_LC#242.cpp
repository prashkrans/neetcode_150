// LC#242. NCAH2. Valid Anagram

// 1. Using sort function
// O(nlogn + mlogm) ~ O(2*(nlogn)) ~ O(nlogn) i.e. pseudolinear or nearly linear time
// O(1) or O(m) depends on the sorting method

class Solution {
public:
    bool isAnagram(string s, string t) {
        int n = s.size(), m = t.size();
        if(n != m) return false;
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return (s == t);
    }
};


// 2. Using unordered_map to count the frequency of characters
// O(n + m) due to size() functions iff they match then O(2n) ~ O(n) i.e. linear time
// O(26) ~ O(1) due to the unordered_map for counting the frequency of characters

class Solution {
public:
    bool isAnagram(string s, string t) {
        int n = s.size(), m = t.size();
        if(n != m) return false;
		unordered_map<char, int> freqMap;
		for(int i=0; i<n; i++) freqMap[s[i]]++;
		for(int i=0; i<n; i++) freqMap[t[i]]--;
		for(auto i: freqMap) if(i.second != 0) return false;
		return true;
    }
};