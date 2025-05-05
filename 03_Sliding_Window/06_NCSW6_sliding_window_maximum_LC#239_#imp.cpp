/* LC#239. Sliding Window Maximum

### Approach 1a: Sliding Window Maximum Using Priority Queue (Max Heap)
1. Use a priority queue (max heap) to efficiently find the maximum element in each sliding window.
2. The priority queue stores pairs of (value, index), where `value` is the element value and `index` is its position in the array.
3. For the first window:
   - Push the first `k` elements into the priority queue.
4. For each subsequent window:
   - Add the new element at the right end of the window to the priority queue.
   - Remove elements from the top of the heap if their indices are outside the current window.
5. The maximum element of the current window is always at the top of the priority queue.
6. Add the maximum element to the result vector for each window.
7. The algorithm ensures efficient computation of the maximum for each window in O(log k) time per window, resulting in O(n log k) overall complexity.
*/

// 1. Using Priority Queue (Max Heap) with Index Tracking (Prefer this method) (My custom code)
// Time Complexity: O(n log k)
// - Each element is pushed into and popped from the priority queue at most once.
// - Priority queue operations (push and pop) take O(log k), where k is the size of the sliding window.
// - Overall complexity is O(n log k), where n is the size of the input array.

// Space Complexity: O(k)
// - The priority queue stores at most k elements at any time.

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> ans;                                                // Result vector to store maximum values
        int n = nums.size();                                            // Size of the input array
        priority_queue<pair<int, int>> pq;                              // Max heap to store value-index pairs
        for(int i = 0; i <= n - k; i++) {                               // Iterate through all possible windows
            if(i == 0) {                                                // Initialize the heap for the first window
                for(int j = 0; j < k; j++) pq.push({nums[j], j});       // Push the first k elements into the heap
            } else {                                                    // For subsequent windows
                pq.push({nums[i + k - 1], i + k - 1});                  // Add the new element to the heap
                while(pq.top().second < i) pq.pop(); // [#IMP .second]  // Remove elements outside the current window
            }
            ans.push_back(pq.top().first);           // [#IMP .first]   // Add the maximum element of the current window to the result
        }
        return ans;                                                     // Return the result vector
    }
};

    /*
Approach 1b: Using Priority Queue (Max Heap)

1. We use a priority queue (max heap) to efficiently find the maximum element in each sliding window.
2. The priority queue stores pairs of (value, index) where value is the element value and index is its position in the array.
3. We first initialize the priority queue with the first k-1 elements of the array.
4. Then for each position i from k-1 to the end of the array, we add the current element to the priority queue.
5. Before extracting the maximum, we remove any elements that are no longer in the current window (elements with index <= i-k).
6. We extract the maximum value from the priority queue (the top element) and add it to our result array.
7. The key insight is that we only need to remove elements from the queue when they're actually at the top and outside our window.
8. This approach works because the priority queue automatically keeps the maximum element at the top.
9. For each window position, we get the maximum in O(log n) time, making the overall algorithm O(n log n).
10. While a deque-based approach would be more efficient (O(n)), this priority queue solution is still reasonably fast and intuitive.
11. One advantage of this approach is that it can be easily modified to find other window statistics like minimum or median.
*/

// 1. Using Priority Queue (Max Heap)
// Time Complexity: O(n log n) - where n is the size of the array and log n comes from priority queue operations
// Space Complexity: O(n) - in worst case all elements might be in the priority queue

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if(nums.size()==0 || nums.size() == 1) return nums;             // Return nums if empty or has only one element
        priority_queue<pair<int,int>> pq;                               // Max heap to store value-index pairs
        vector<int> ans;                                                // Result vector to store maximum values
        for(int i=0; i<k-1; i++) pq.push({nums[i], i});                 // Initialize the priority queue with first k-1 elements
        for(int i=k-1; i<nums.size(); i++) {                            // Process each window starting from the kth element
            pq.push({nums[i], i});                                      // Add current element to the priority queue
            while(!pq.empty() && pq.top().second <= i - k) pq.pop();    // Remove elements that are outside the current window
            ans.push_back(pq.top().first);                              // Add current window's maximum to result
        }
        return ans;                                                     // Return the result vector
    }
};