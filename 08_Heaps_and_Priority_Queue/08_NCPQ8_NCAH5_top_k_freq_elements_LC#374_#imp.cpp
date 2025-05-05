/* LC#347. NCAH6. NCPQ8. Top K Frequent Elements

### Approach 2: Using a Max Heap (Priority Queue) along with Frequency Counting
1. Create a frequency map (unordered_map) to count how many times each number appears
in the input array. This allows O(1) lookups for each element.
2. Use a max heap (priority queue) to store elements by their frequency. Each entry in
the heap is a pair of (frequency, element).
3. Push all elements from the frequency map into the heap. The heap automatically
orders elements by their frequency in descending order.
4. Extract the top k elements from the heap:
   a. For each of the k iterations, retrieve the element with the highest frequency
from the top of the heap.
   b. Add the element to the result vector and remove it from the heap.
5. Return the result vector containing the k most frequent elements.
6. The algorithm ensures efficient insertion and extraction using the heap, resulting
in a time complexity of O(n + m log m), where n is the size of the input array and m is
the number of unique elements.
*/

// 2. Optimized solution: Using a max heap (priority queue) along with frequency counting
// Time Complexity: O(n + m log m + k log m) ~ O(n + mlogm) where n is the size of nums, m is the number of unique elements, and k is the given k
// - O(n): To count the frequency of elements in the array using the unordered_map.
// - O(m log m): To insert m unique elements into the max heap (priority queue), where m is the number of unique elements.
// - O(k log m): To extract the top k elements from the heap, but since k ≤ m, this is dominated by O(m log m).

// Space Complexity: O(m)
// - O(m): Space used by the unordered_map to store frequencies of m unique elements.
// - O(m): Space used by the priority queue to store m elements.

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> ans;                                  // Vector to store the k most frequent elements
        int n = nums.size();                              // Size of the input array
        unordered_map<int, int> freqMap;                  // Map to store element frequencies
        for(int i=0; i<n; i++) freqMap[nums[i]]++;        // Count frequency of each element in nums
        priority_queue<pair<int, int>> pq;                // Max heap to store elements by frequency
        for(auto i: freqMap) pq.push({i.second, i.first}); // Push frequency and element into the heap
        while(k--) {                                      // Extract the top k elements from the heap
            ans.push_back(pq.top().second);               // Add the element with the highest frequency to the result
            pq.pop();                                     // Remove the top element from the heap
        }
        return ans;                                       // Return the k most frequent elements
    }
};


/*
### Approach 3: Using a Min Heap (Priority Queue) along with Frequency Counting
1. Create a frequency map (unordered_map) to count how many times each number appears
in the input array. This allows O(1) lookups for each element.
2. Use a min heap (priority queue) to store elements by their frequency. Each entry in
the heap is a pair of (frequency, element).
3. Push elements from the frequency map into the heap:
   a. If the heap size exceeds k, remove the element with the smallest frequency from
the heap. This ensures that the heap always contains the k most frequent elements.
4. Extract all elements from the heap:
   a. Add each element in the heap to the result vector. The heap contains the k most
frequent elements in ascending order of frequency.
5. Return the result vector containing the k most frequent elements.
6. The algorithm ensures efficient insertion and extraction using the heap, resulting
in a time complexity of O(n + m log k), where n is the size of the input array and m is
the number of unique elements.
*/

// 3. Optimized solution: Using a min heap (priority queue) along with frequency counting.
// (Prefer this approach as its more efficient in time and space)

// Time Complexity: O(n + m log k)
// - O(n): To count the frequency of elements in the array using the unordered_map.
// - O(m log k): To maintain the min heap of size k, where m is the number of unique elements.
// - O(k): To extract the top k elements from the heap, but this is dominated by O(m log k).

// Space Complexity: O(m + k)
// - O(m): Space used by the unordered_map to store frequencies of m unique elements.
// - O(k): Space used by the min heap to store at most k elements.

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> ans;                                  // Vector to store the k most frequent elements
        int n = nums.size();                              // Size of the input array
        unordered_map<int, int> freqMap;                  // Map to store element frequencies
        for(int i=0; i<n; i++) freqMap[nums[i]]++;        // Count frequency of each element in nums
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min heap to store elements by frequency
        for(auto i: freqMap) {                            // Iterate through the frequency map
            int val = i.first;                            // Element value
            int freq = i.second;                          // Frequency of the element
            pq.push({freq, val});                         // Push frequency and element into the heap
            if(pq.size() > k) pq.pop();                   // Maintain the heap size to k
        }
        while(!pq.empty()) {                              // Extract the top k elements from the heap
            ans.push_back(pq.top().second);               // Add the element with the smallest frequency in the heap to the result
            pq.pop();                                     // Remove the top element from the heap
        }
        return ans;                                       // Return the k most frequent elements
    }
};


/* Could safely ignore this approach as its not efficient
### Approach 1: Frequency Counting with Manual Selection
1. Create a frequency map (unordered_map) to count how many times each number appears
in the input array, which allows O(1) lookups.
2. The algorithm then performs k iterations to find the k most frequent elements,
selecting one in each iteration.
3. In each iteration, we scan through the entire frequency map to find the
element with the highest frequency that hasn't been selected yet.
4. Once we find the element with maximum frequency, we add it to our
result vector and set its frequency to zero in the map.
5. Setting the frequency to zero ensures we don't select the same element
again in subsequent iterations.
6. This approach uses a greedy method by always selecting the most frequent
element available at each step.
7. The time complexity is dominated by the k iterations through the frequency
map, making it O(n + k*m) where m is the unique element count.
8. While not the most efficient solution (a heap would be better), this
approach is straightforward and handles the problem correctly.
*/

// 1. Naive solution: Frequency counting with manual selection
// Time Complexity: O(n + k*m) where n is the size of nums, k is the given k, and m is the number of unique elements
// Space Complexity: O(m) where m is the number of unique elements

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> ans;                                     // Vector to store the k most frequent elements
        unordered_map<int, int> mp;                          // Map to store element frequencies
        for(int i=0; i<nums.size(); i++) mp[nums[i]]++;      // Count frequency of each element in nums
        while(k--) {                                         // Loop k times to find top k frequent elements
            int maxFreq = INT_MIN;                           // Track maximum frequency found in current iteration
            int key = 0;                                     // Store element with maximum frequency
            for(auto i: mp) {                                // Iterate through all elements in the map
                if(maxFreq < i.second) {                     // If current element has higher frequency
                    maxFreq = i.second;                      // Update maximum frequency
                    key = i.first;                           // Update key with current element
                }
            }
            mp[key] = 0;                                     // Reset frequency of found element to avoid reselection
            ans.push_back(key);                              // Add element to result vector
        }
        return ans;                                          // Return the k most frequent elements
    }
};
    