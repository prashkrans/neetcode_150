#include<iostream>
#include<vector>
using namespace std;

// Yet to verify and simplify this solution

class Solution {
    void rec(int start, vector<int>& arr, vector<vector<int>> partition, vector<vector<vector<int>>>& ans) {
        int n = arr.size();
        if(start == n) {                                  // Base case: processed the entire array
            ans.push_back(partition);                     // Add current partition to results
            return;
        }
        
        vector<int> currentSubArray;
        for(int i = start; i < n; i++) {                  // Try all possible first parts
            currentSubArray.push_back(arr[i]);            // Build current subarray
            partition.push_back(currentSubArray);         // Add subarray to current partition
            rec(i+1, arr, partition, ans);              // Recurse with remaining array elements
            partition.pop_back();                         // Backtrack: remove last subarray
        }
    }
    
public:
    vector<vector<vector<int>>> partition(vector<int>& arr) {
        vector<vector<vector<int>>> ans;                  // Store all valid partitions
        rec(0, arr, vector<vector<int>>(), ans);          // Start recursion with empty partition
        return ans;                                       // Return all partitions
    }
};

int main() {
    cout << "Enter array size: ";
    int n;
    cin >> n;
    
    vector<int> arr(n);
    cout << "Enter array elements: ";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    Solution sol;
    vector<vector<vector<int>>> ans = sol.partition(arr);
    
    cout << endl << "The partitions of the given array are:" << endl;
    for(int i = 0; i < ans.size(); i++) {
        cout << "Partition " << i+1 << ": ";
        for(int j = 0; j < ans[i].size(); j++) {
            cout << "[";
            for(int k = 0; k < ans[i][j].size(); k++) {
                cout << ans[i][j][k];
                if(k != ans[i][j].size() - 1) cout << ", ";
            }
            cout << "]";
            if(j != ans[i][j].size() - 1) cout << " | ";
        }
        cout << endl;
    }
    
    return 0;
}