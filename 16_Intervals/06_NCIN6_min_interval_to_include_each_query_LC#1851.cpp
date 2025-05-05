/* LC#1851. NCIN7. Minimum Interval to Include Each Query

### Note:
Each interval is added to the priority queue at most once, not multiple times. 
The code processes each interval exactly once as it moves through the sorted intervals array 
with the pointer j.

### Approach: Min-Heap and Sorted Queries
1. Sort the intervals by their start times. This allows efficient processing of intervals
that include a given query.
2. Use a map to store the queries and their results. Sorting the queries ensures that
we process them in ascending order.
3. Use a min-heap (priority queue) to store intervals that include the current query.
The min-heap is sorted by interval size, allowing efficient retrieval of the smallest
interval. Its stored as pairs of (size, end) to facilitate easy access to the size and end time. 
4. For each query:
   a. Add all intervals that start before or at the query value to the heap.
   b. Remove intervals from the heap that end before the query value.
   c. If the heap is not empty, the top of the heap contains the smallest interval that
includes the query. Update the result for the query.
   d. If the heap is empty, no interval includes the query. Set the result to -1.
5. After processing all queries, retrieve the results from the map in the original
query order.
6. The algorithm ensures efficient processing of intervals and queries, resulting in a
time complexity of O((n + m) * log m), where n is the number of queries and m is the
number of intervals.
*/

/*
1. Using a min-heap and sorted intervals (by start time) and sorted queries
Time Complexity: O(m log m + n log n + m + n) ~ O(mlogm + nlogn)
- O(m log m): Sorting the intervals array
- O(n log n): Creating and inserting into the queriesMap (map operations are log n)
- O(m): Processing each interval once in the loop
- O(m log m): Worst case for priority queue operations (each interval pushed/popped)
- O(n): Iterating through each query in the map
- O(n): Final result construction

Space Complexity: O(m + n)
- O(n): Result vector 'ans'
- O(n): Map 'queriesMap' storing queries and results
- O(m): Priority queue can store at most m intervals
- O(1): Variables like j, query, start, end

This solution is efficient and avoids TLE by:
- Using a map to sort queries
- Processing intervals only once across all queries (not multiple times)
- Maintaining the priority queue state between queries
*/

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        vector<int> ans;                                // Result vector to store answers for each query
        int m = intervals.size(), n = queries.size();   // Number of intervals and queries
        sort(intervals.begin(), intervals.end());       // Sort intervals by their start times
        map<int, int> queriesMap;                       // Map to store queries and their results
        for(int i=0; i<n; i++) queriesMap[queries[i]] = -1; // Initialize all queries with -1
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min-heap to store intervals
        int j = 0;                                      // Pointer to iterate over intervals
        for(auto i: queriesMap) {                       // Iterate over sorted queries
            int query = i.first;                        // Current query value
            while(j < m) {                              // Process intervals
                int start = intervals[j][0];            // Start of the interval
                int end = intervals[j][1];              // End of the interval
                int size = end - start + 1;             // Size of the interval
                if(start <= query) pq.push({size, end}); // Add interval to the heap if it includes the query
                else break;                             // Stop if the interval starts after the query
                j++;                                    // Move to the next interval
            }
            while(!pq.empty() && pq.top().second < query) pq.pop(); // Remove intervals that do not include the query
            if(!pq.empty()) queriesMap[query] = pq.top().first;    // Update the result for the query with the smallest interval
            else queriesMap[query] = -1;                          // No valid interval found for the query
        }
        for(int i=0; i<n; i++) {                       // Populate the result vector
            ans.push_back(queriesMap[queries[i]]);     // Retrieve results in the original query order
        }
        return ans;                                    // Return the result vector
    }
};

/*
2. Using a min-heap but adding and removing all the intervals for each query (may ignore this)
Gets TLE since we are inserting and deleting all the intervals for each query

Time Complexity: O(m*n)
- O(m log m): Sorting the intervals array
- O(n): Iterating through each query
 - For each query:
   - O(m): Clearing and refilling the priority queue for each query
   - O(log m): Priority queue operations for each interval
 - Overall O(n*m + n*log m) ~ O(n*m) since n*m dominates n*log m
- Total: O(m log m + n*m) which simplifies to O(n*m) when n*m dominates m log m

Space Complexity: O(m)
- O(n): Result vector 'ans'
- O(m): Priority queue can store at most m intervals
- O(1): Other variables

### Key differences from the previous solution:

- This solution processes each query independently, clearing the priority queue each time
- No map is used to store queries - processes them in original order
- For each query, it scans through all intervals again
- Much less efficient as it repeats work instead of building on previous computations
- Previous solution had O(m log m + n log n) complexity; this has O(n*m) which is significantly worse

### The previous solution was optimized by:

- Using a map to sort queries
- Processing intervals only once across all queries
- Maintaining the priority queue state between queries

*/

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        vector<int> ans;
        int m = intervals.size(), n = queries.size();
        sort(intervals.begin(), intervals.end());
        // sort(queries.begin(), queries.end());
        for(auto i: intervals) cout<<i[0]<<" "<<i[1]<<endl;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for(int i=0; i<n; i++) {
            int query = queries[i];
            while(!pq.empty()) pq.pop();
            for(int j=0; j<m; j++) {
                int start = intervals[j][0];
                int end = intervals[j][1];
                int size = end - start + 1;
                if(start <= query) pq.push({size, end});
                else break;
            }
            while(!pq.empty() && pq.top().second < query) pq.pop();
            if(!pq.empty()) ans.push_back(pq.top().first);
            else ans.push_back(-1);
        }
        return ans;    
    }
};
    