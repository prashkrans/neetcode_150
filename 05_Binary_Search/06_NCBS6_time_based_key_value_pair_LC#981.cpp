// LC#981. Time Based Key-Value Store


/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */


// 1. Using unordered_map<string, vector<pair<int, string>>> mp and binary search (using string ans)
// Time complexity: O(1) for set() and O(log n) for get()
// Space complexity: O(m * n)
// Where n is the total number of values associated with a key and m is the total number of keys.

class TimeMap {
    unordered_map<string, vector<pair<string, int>>> store;

    string binarySearch(vector<pair<string, int>> &values, int timestamp) {
        int l = 0;
        int r = values.size()-1;
        string ans;
        while(l <= r) { // Note l <= r (not l < r)
            int mid = l + (r - l) / 2;
            if(values[mid].second <= timestamp) { // Note <= (not <)
                ans = values[mid].first;
                l = mid + 1; // Don't use break here
            }
            else r = mid - 1;
        }
        return ans;
    }
public:
    TimeMap() {}
    // TimeMap() {
        // store = unordered_map<string, vector<pair<string, int>>>(); redundant
    // }
    
    void set(string key, string value, int timestamp) {
        store[key].push_back({value, timestamp});
    }
    
    string get(string key, int timestamp) {
        return binarySearch(store[key], timestamp);
    }
};


// or, same as above

class TimeMap {
    unordered_map<string, vector<pair<string, int>>> store;
    
    string binarySearch(vector<pair<string, int>> &values, int timestamp) {
        int l = 0;
        int r = values.size()-1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(values[mid].second <= timestamp) {
                l = mid + 1; // Don't use break here
            }
            else r = mid - 1;
        }
        return r >= 0 ? values[r].first : "";
    }

public:
    TimeMap() {}
    // TimeMap() {
        // store = unordered_map<string, vector<pair<string, int>>>(); redundant
    // }
    
    void set(string key, string value, int timestamp) {
        store[key].push_back({value, timestamp});
    }
    
    string get(string key, int timestamp) {
        return binarySearch(store[key], timestamp);
    }
};
