/* LC#56. NCIN2. Merge Intervals

### Approach: Sorting and Merging Overlapping Intervals
1. Sort the intervals based on their start times using the default or custom comparator.
   - Sorting ensures that overlapping intervals are adjacent in the list.
2. Initialize a result vector `ans` and add the first interval to it.
3. Iterate through the sorted intervals:
   - If the current interval does not overlap with the last interval in the result
     (i.e., the start time of the current interval is greater than the end time
     of the last interval), add the current interval to the result.
   - If the current interval overlaps with the last interval in the result, merge
     them by updating the end time of the last interval to the maximum of the two
     end times.
4. After processing all intervals, the result vector contains the merged intervals.
5. This approach ensures that all overlapping intervals are merged efficiently
   in a single pass after sorting.
*/


// 1. Sorting and Merging Overlapping Intervals (My custom code)
// O(n log n) time complexity for sorting + O(n) for merging where n is the number of intervals
// O(n) space complexity for the result vector

class cmp {
public:
    bool operator() (vector<int> a, vector<int> b) const {
        return a[0] < b[0];
    }
};
    
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp());
        vector<vector<int>> ans;
        int j = 0;
        for(int i=0; i<intervals.size(); i++) {
            if(i == 0) {
                ans.push_back(intervals[i]);
                j++;
            }
            else {
                if(intervals[i][0] > ans[j-1][1]) {
                    ans.push_back(intervals[i]);
                    j++;
                }
                else {
                    ans[j-1][1] = max(ans[j-1][1], intervals[i][1]);
                }
            }
        }
        return ans;
    }
};

// or

// class cmp is not actually needed here as sorting is done using the default comparator


// Time Complexity: O(n log n), where n is the number of intervals (due to sorting)
// Space Complexity: O(n), for the result vector

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());            // Sort intervals by start times
        vector<vector<int>> ans;                             // Resultant vector to store merged intervals
        ans.push_back(intervals[0]);                         // Add the first interval to the result
        for(int i = 1; i < intervals.size(); i++) {          // Iterate through the intervals
            if(intervals[i][0] > ans.back()[1]) {            // If current interval does not overlap with the last interval in result
                ans.push_back(intervals[i]);                 // Add the current interval to the result
            } else {                                         // If intervals overlap
                ans.back()[1] = max(ans.back()[1], intervals[i][1]); // Merge intervals by updating the end time
            }
        }
        return ans;                                          // Return the merged intervals
    }
};
    