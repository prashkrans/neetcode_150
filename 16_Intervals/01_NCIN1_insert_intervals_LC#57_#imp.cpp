/* LC#57 NCIN1 Insert Interval

The given intervals are non-overlapping and sorted in ascending order based on the start value. 
Try to visualize them as line segments and consider how a new interval can be inserted. 
We have three cases: we have appended all intervals, we reach an interval whose start value is 
greater than the new interval’s end, or we find an overlapping interval.

### Approach 1: Merge Intervals During Insertion
1. Initialize an empty result vector `ans` to store the merged intervals.
2. Extract the start (`newStart`) and end (`newEnd`) of the `newInterval`.
3. Iterate through the given intervals:
   - If the current interval ends before `newInterval` starts, add it to the result
     as it does not overlap with `newInterval`.
   - If the current interval starts after `newInterval` ends:
     - If `newInterval` has not been inserted yet, add it to the result and mark
       it as inserted.
     - Add the current interval to the result.
   - If the current interval overlaps with `newInterval`, merge them by updating
     `newStart` to the minimum of the two start times and `newEnd` to the maximum
     of the two end times.
4. After the loop, if `newInterval` has not been inserted, add it to the result.
5. Return the result vector containing the merged intervals.
6. This approach ensures that the intervals are processed in a single pass, maintaining
the time complexity of O(n).
*/

// Merge Intervals During Insertion
// Time Complexity: O(n), where n is the number of intervals (single pass through the intervals)
// Space Complexity: O(n), for the output vector

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> ans;                              // Resultant vector to store merged intervals
        bool isInserted = false;                              // Flag to check if newInterval is inserted
        int newStart = newInterval[0];                        // Start of the new interval
        int newEnd = newInterval[1];                          // End of the new interval

        for(int i = 0; i < intervals.size(); i++) {           // Iterate through all intervals
            if(intervals[i][1] < newStart) {                  // If current interval ends before newInterval starts
                ans.push_back(intervals[i]);                  // Add current interval to the result
            } 
            else if(intervals[i][0] > newEnd) {               // If current interval starts after newInterval ends
                if(!isInserted) {                             // If newInterval is not yet inserted
                    ans.push_back({newStart, newEnd});        // Insert newInterval
                    isInserted = true;                        // Mark newInterval as inserted
                }
                ans.push_back(intervals[i]);                  // Add current interval to the result
            } 
            else {                                            // If intervals overlap
                newStart = min(newStart, intervals[i][0]);    // Merge intervals by updating newStart
                newEnd = max(newEnd, intervals[i][1]);        // Merge intervals by updating newEnd
            }
        }

        if(!isInserted) ans.push_back({newStart, newEnd});    // If newInterval is not inserted, add it at the end
        return ans;                                           // Return the merged intervals
    }
};
    

// or (My custom code)

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> ans;
        bool isInserted = false;
        int newStart = newInterval[0];
        int newEnd = newInterval[1];
        for(int i=0; i<intervals.size(); i++) {
            if(intervals[i][1] < newStart) ans.push_back(intervals[i]);
            else if(intervals[i][0] > newEnd) {
                if(!isInserted) {
                    ans.push_back({newStart, newEnd});
                    isInserted = true;
                }
                ans.push_back(intervals[i]);
            }
            else { // Overlapping intervals: The conditions here are redundant
                if(intervals[i][1] >= newStart) newStart = min(newStart, intervals[i][0]);
                if(intervals[i][0] <= newEnd) newEnd = max(newEnd, intervals[i][1]);
            }
        }
        if(!isInserted) ans.push_back({newStart, newEnd});
        return ans;     
    }
};
    