// LC#981. Time Based Key-Value Store


/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */


// 1. Using unordered_map<string, vector<pair<int, string>>> mp and binary search
// Time complexity: O(1) for set() and O(log n) for get()
// Space complexity: O(m * n)
// Where n is the total number of values associated with a key and m is the total number of keys.

class TimeMap {
    unordered_map<string, vector<pair<int, string>>> store;

    string binarySearch(int timestamp, vector<pair<int, string>> &values) {
        int l = 0;
        int r = values.size()-1;
        string ans;
        while(l<=r) {
            int mid = (l + r)/2;
            if(values[mid].first <= timestamp) {
                ans = values[mid].second;
                l = mid+1; // Don't use break here
            }
            else r = mid-1;
        }
        return ans;
    }
public:
    TimeMap() {
        store = unordered_map<string, vector<pair<int, string>>>();
    }
    
    void set(string key, string value, int timestamp) {
        store[key].push_back({timestamp, value});
    }
    
    string get(string key, int timestamp) {
        return binarySearch(timestamp, store[key]);
    }
};
