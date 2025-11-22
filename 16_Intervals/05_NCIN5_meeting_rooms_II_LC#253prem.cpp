/* LC#253 Premium NCIN5. Meeting Rooms II

Approches:
1. Min-Heap to Track Meeting End Times
2. Two Pointers with Sorted Start and End Times
TODO:
3. Sweep Line Algorithm with Event Points
4. Greedy Algorithm with Sorting
5. Binary Search with Sorted End Times
6. Segment Tree for Range Queries
7. Dynamic Programming with Interval Scheduling

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

/*
### Approach 1: Min-Heap to Track Meeting End Times
1. Sort the intervals based on their start times using a custom comparator.
   - Sorting ensures that meetings are processed in chronological order.
2. Use a min-heap (priority queue) to keep track of the end times of ongoing meetings.
   - The heap allows us to efficiently find the earliest ending meeting.
3. Add the end time of the first meeting to the heap.
4. Iterate through the remaining intervals:
   - If the start time of the current meeting is greater than or equal to the earliest
     ending meeting (top of the heap), remove the earliest ending meeting from the heap.
   - Add the end time of the current meeting to the heap.
5. The size of the heap at any point represents the number of rooms currently in use.
6. At the end of the iteration, the size of the heap is the minimum number of meeting
   rooms required.
7. This approach ensures that overlapping meetings are handled efficiently by always
   keeping track of the earliest ending meeting.
*/

// 1. Min-Heap to Track Meeting End Times and using a custom comparator
// Time Complexity: O(n log n), where n is the number of intervals (due to sorting and heap operations)
// Space Complexity: O(n), for the min-heap used to track meeting end times

class cmp { // cmp is required here as a custom data structure `Interval` is being used here
public:
    bool operator() (Interval a, Interval b) const {
        return a.start < b.start;                            // Sort intervals by their start times
    }
};

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        if (intervals.empty()) return 0;                     // If no intervals, return 0
        sort(intervals.begin(), intervals.end(), cmp());     // Sort intervals by start times
        priority_queue<int, vector<int>, greater<int>> minHeap; // Min-heap to track meeting end times
        minHeap.push(intervals[0].end);                      // Add the end time of the first meeting
        for (int i = 1; i < intervals.size(); i++) {         // Iterate through the remaining intervals
            int currStart = intervals[i].start;              // Start time of the current meeting
            int currEnd = intervals[i].end;                  // End time of the current meeting
            if (minHeap.top() <= currStart) {                // If the earliest ending meeting ends before the current meeting starts
                minHeap.pop();                               // Remove the earliest ending meeting
            }
            minHeap.push(currEnd);                           // Add the current meeting's end time to the heap
        }
        return minHeap.size();                               // The size of the heap is the minimum number of rooms required
    }
};

// or using a lambda function instead of a custom comparator

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        if (intervals.empty()) return 0;                     // If no intervals, return 0
        sort(intervals.begin(), intervals.end(), [](auto &a, auto &b) { // Sort intervals by start times
            return a.start < b.start;
        });
        priority_queue<int, vector<int>, greater<int>> minHeap; // Min-heap to track meeting end times
        for (auto interval : intervals) {                    // Iterate through all intervals
            if (!minHeap.empty() && minHeap.top() <= interval.start) { // If the earliest ending meeting ends before the current meeting starts
                minHeap.pop();                               // Remove the earliest ending meeting
            }
            minHeap.push(interval.end);                      // Add the current meeting's end time to the heap
        }
        return minHeap.size();                               // The size of the heap is the minimum number of rooms required
    }
};

/*
### Approach 2: Two Pointers with Sorted Start and End Times
1. Extract the start and end times of all intervals into separate arrays (`start` and `end`).
2. Sort both arrays:
   - Sorting ensures that we can process meetings in chronological order.
3. Use two pointers (`s` for start times and `e` for end times) to simulate the scheduling of meetings:
   - If the current meeting starts before the earliest ending meeting ends (`start[s] < end[e]`):
     - Increment the `count` of ongoing meetings.
     - Move the `s` pointer to the next start time.
   - Otherwise, if the current meeting starts after or at the same time as the earliest ending meeting ends:
     - Decrement the `count` of ongoing meetings.
     - Move the `e` pointer to the next end time.
4. Track the maximum value of `count` during the iteration, which represents the minimum number of meeting rooms required.
5. Return the maximum value of `count` as the result.
6. This approach efficiently calculates the minimum number of meeting rooms needed by processing start and end times in a single pass after sorting.
*/

// 2. Two Pointers with Sorted Start and End Times
// Time Complexity: O(n log n), where n is the number of intervals (due to sorting)
// Space Complexity: O(n), for the start and end arrays

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        vector<int> start;                                   // Stores start times of intervals
        vector<int> end;                                     // Stores end times of intervals

        for(int i = 0; i < intervals.size(); i++) {          // Populate start and end arrays
            start.push_back(intervals[i].start);             // Add start time of the interval
            end.push_back(intervals[i].end);                 // Add end time of the interval
        }

        sort(start.begin(), start.end());                    // Sort start times
        sort(end.begin(), end.end());                        // Sort end times

        int s = 0, e = 0, count = 0, ans = 0;                // Initialize pointers and counters

        while(s < intervals.size()) {                        // Iterate through all start times
            if(start[s] < end[e]) {                          // If a meeting starts before the earliest ending meeting
                s++;                                         // Move to the next start time
                count++;                                     // Increment the count of ongoing meetings
            } else {                                         // If a meeting ends before or at the same time as the next meeting starts
                e++;                                         // Move to the next end time
                count--;                                     // Decrement the count of ongoing meetings
            }
            ans = max(ans, count);                          // Update the maximum number of rooms needed
        }

        return ans;                                          // Return the maximum number of rooms needed
    }
};


