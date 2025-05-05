/* LC#703. NCPQ1. Kth Largest Element in a Stream
The k-th largest element is the smallest element among the top k largest elements. This means we only need to 
maintain k elements in our Min-Heap to efficiently determine the k-th largest element. Whenever the size of the 
Min-Heap exceeds k, we remove the smallest element by popping from the heap. How do you implement this?

We initialize a Min-Heap with the elements of the input array. When the add() function is called, we insert the 
new element into the heap. If the heap size exceeds k, we remove the smallest element (the root of the heap). 
Finally, the top element of the heap represents the k-th largest element and is returned.

Insert in min heap is O(logn) and look up/search is O(1)
*/

// 1a. Using a minheap of size k (Prefer this approach)
// Time Complexity:
// - Constructor: O(n log k), where n is the size of the input array and k is the size of the heap.
//   - Each insertion into the heap takes O(log k), and we insert up to n elements.
// - add(): O(log k) for each call, as we insert into the heap and maintain its size.

// Space Complexity: O(k)
// - The priority queue (min-heap) stores at most k elements.

// Note: We dont nedd to save nums array in the class
class KthLargest {
    int k;                                              // The rank of the largest element to track
    priority_queue<int, vector<int>, greater<int>> pq;  // Min-heap to store the top k largest elements
public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;                                    // Initialize k
        for(int i = 0; i < nums.size(); i++) {          // Iterate through the input array
            pq.push(nums[i]);                           // Add each element to the heap
            if(pq.size() > k) pq.pop();                 // Maintain the heap size to k
        }
    }
    
    int add(int val) {
        pq.push(val);                                   // Add the new value to the heap
        if(pq.size() > k) pq.pop();                     // Remove the smallest element if the heap exceeds size k
        return pq.top();                                // Return the k-th largest element (top of the heap)
    }
};

// 1b. Using a minheap of size k (Same as above but ignore this)
// O(mlogk) time and O(k) space, where m is the number of times add() is called, 
// and k represents the rank of the largest number to be tracked (i.e., the k-th largest element).

class KthLargest {
    int k;
    priority_queue<int, vector<int>, greater<int>> pq;
public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        int minSize = k;
        if(minSize > nums.size()) minSize = nums.size();
        sort(nums.begin(), nums.end(), greater<int>());
        for(int i=0; i<minSize; i++) pq.push(nums[i]);
    }
    
    int add(int val) {
        pq.push(val);
        if(pq.size() > k) pq.pop();
        return pq.top();
    }
};

// Ignore this approach
// Gives TLE
class KthLargest {
    int k;
    vector<int> nums;
public:
    KthLargest(int k, vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater<int>());    
        this->k = k;
        this->nums = nums;
    }
    
    int add(int val) {
        nums.push_back(val);
        sort(nums.begin(), nums.end(), greater<int>());    
        int ans = nums[k-1];
        // Once an element is added it is not popped out, so no need to pop out.
        // for(int i=k-1; i<nums.size()-1; i++) nums[i] = nums[i+1];
        // nums.pop_back();
        return ans;
    }
};

