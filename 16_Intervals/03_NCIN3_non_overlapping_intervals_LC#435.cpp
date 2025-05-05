/* LC#435 NCIN3. Non Overlapping Intervals

Methods: 
1. Greedy Approach 
2. Rec without memo 
3. Rec with memo

### Approach: Greedy Algorithm to Minimize Overlaps
1. Sort the intervals based on their start times using the default comparator.
   - Sorting ensures that intervals are processed in chronological order.
2. Initialize a variable `prevEnd` to track the end time of the last non-overlapping
   interval. Set it to the end time of the first interval.
3. Iterate through the sorted intervals starting from the second interval:
   - If the start time of the current interval is less than `prevEnd`, it means
     the intervals overlap:
     - Increment the count of intervals to remove (`ans`).
     - Update `prevEnd` to the smaller of the two end times (`min(currEnd, prevEnd)`),
       as keeping the interval with the smaller end time minimizes future overlaps.
   - If the intervals do not overlap, update `prevEnd` to the end time of the
     current interval.
4. After processing all intervals, the variable `ans` contains the minimum number
   of intervals to remove to make the rest non-overlapping.
5. This approach ensures that overlaps are minimized greedily by always keeping
   the interval with the smallest end time.
*/

// 1. Greedy Algorithm to Minimize Overlaps
// Time Complexity: O(n log n), where n is the number of intervals (due to sorting)
// Space Complexity: O(1), as no additional space is used apart from variables

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int ans = 0;                                         // Initialize the count of intervals to remove
        sort(intervals.begin(), intervals.end());            // Sort intervals by start times
        int prevEnd = intervals[0][1];                       // Track the end of the previous interval
        for(int i = 1; i < intervals.size(); i++) {          // Iterate through the intervals
            int currStart = intervals[i][0];                 // Start of the current interval
            int currEnd = intervals[i][1];                   // End of the current interval
            if(currStart < prevEnd) {                        // If intervals overlap
                ans++;                                       // Increment the count of intervals to remove
                prevEnd = min(currEnd, prevEnd);             // Keep the interval with the smaller end time
            } else {                                         // If intervals do not overlap
                prevEnd = currEnd;                           // Update prevEnd to the current interval's end
            }
        }
        return ans;                                          // Return the count of intervals to remove
    }
};

// Refer this important example to understand the code better:
// Input: intervals = [[1, 10], [2, 3], [4, 5], [6, 7]]

// 1. Initialize ans = 0
// 2. Sort intervals by start time
//    - intervals is already sorted: [[1, 10], [2, 3], [4, 5], [6, 7]]

// 3. Set prevEnd = intervals[0][1] = 10 (end of first interval)

// 4. Iterate through remaining intervals:
//    i=1: [2, 3]
//      currStart = 2, currEnd = 3
//      Check if currStart < prevEnd: 2 < 10? Yes, there's overlap
//      ans++ → ans = 1
//      prevEnd = min(currEnd, prevEnd) = min(3, 10) = 3 i.e we remove [1, 10] and keep [2, 3]
   
//    i=2: [4, 5]
//      currStart = 4, currEnd = 5
//      Check if currStart < prevEnd: 4 < 3? No, no overlap
//      prevEnd = currEnd = 5
   
//    i=3: [6, 7]
//      currStart = 6, currEnd = 7
//      Check if currStart < prevEnd: 6 < 5? No, no overlap
//      prevEnd = currEnd = 7

// 5. Return ans = 1