// LC#973. K Closest Points to Origin


// 1. Min heap of pair<int, int> == {distance^2, index}
// O(n log n) not O(k log n) due to the fact that we are storing all n points in the heap.
// O(n) due to the fact that we are storing all n points in the heap.

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        vector<vector<int>> ans;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for(int i=0; i<points.size(); i++) {
            int distSquared = pow(points[i][0], 2) + pow(points[i][1], 2);
            pq.push({distSquared, i});
        }
        while(k--) {
            int index = pq.top().second;
            pq.pop();
            ans.push_back(points[index]);
        }
        return ans;
    }
};

/*
### Approach: Max-Heap of Size k
1. Use a max-heap (priority queue) to maintain the k closest points to the origin.
2. For each point:
   - Calculate the squared distance from the origin: `dist = x^2 + y^2`.
   - Push the distance and the index of the point into the heap.
   - If the heap size exceeds k, remove the farthest point (top of the heap).
3. After processing all points, the heap contains the k closest points.
4. Extract the points from the heap and add them to the result vector.

*/

// 2. Maxheap of size k (Use either of the two but this is better)
// Time Complexity: O(n log k)
// - Each point is pushed into the priority queue, which takes O(log k) time per operation.
// - For n points, this results in O(n log k) time complexity.

// Space Complexity: O(k)
// - The priority queue stores at most k elements.

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        vector<vector<int>> ans;                                      // Result vector to store the k closest points
        priority_queue<pair<int, int>> pq;                            // Max-heap to store distances and indices
        for(int i = 0; i < points.size(); i++) {                      // Iterate through all points
            int x1 = points[i][0], y1 = points[i][1];                 // Extract x and y coordinates
            int dist = x1 * x1 + y1 * y1;                             // Calculate squared distance from origin
            pq.push({dist, i});                                       // Push distance and index into the heap
            if(pq.size() > k) pq.pop();                               // Maintain the heap size to k
        }
        while(!pq.empty()) {                                          // Extract the k closest points
            ans.push_back(points[pq.top().second]);                   // Add the point corresponding to the top of the heap
            pq.pop();                                                 // Remove the top element
        }
        return ans;                                                   // Return the result
    }
};