/* LC#252 Premium NCIN4. Meeting Rooms I

Given an array of meeting time intervals where intervals[i] = [starti, endi], 
determine if a person could attend all meetings.

Example 1:
Input: intervals = [[0,30],[5,10],[15,20]]
Output: false

Example 2:
Input: intervals = [[7,10],[2,4]]
Output: true

Constraints:
0 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti < endi <= 106
*/

/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

// 1. Sort the intervals based on their start times and check for overlaps
// Time Complexity: O(n log n), where n is the number of intervals (due to sorting)
// Space Complexity: O(1), as no additional space is used apart from variables

class cmp {
public:
    bool operator() (const Interval a, const Interval b) const {
        return a.start < b.start;                            // Sort intervals by their start times
    }
};

class Solution {
public:
    bool canAttendMeetings(vector<Interval>& intervals) {
        if(intervals.empty()) return true;                   // If no intervals, return true
        sort(intervals.begin(), intervals.end(), cmp());     // Sort intervals by start times
        for(int i = 0; i < intervals.size() - 1; i++) {      // Iterate through sorted intervals
            if(intervals[i+1].start < intervals[i].end)      // Check for overlapping intervals
                return false;                                // If overlap found, return false
        }
        return true;                                         // If no overlaps, return true
    }
};
    