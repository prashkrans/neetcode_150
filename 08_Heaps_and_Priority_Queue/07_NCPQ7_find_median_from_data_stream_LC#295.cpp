/* LC#295. NCPQ7. Find Median from Data Stream
TODO - make the code for approach 2 more compact

We can use a Heap (Max-Heap for the left half and Min-Heap for the right half). Instead of dividing the array, 
we store the elements in these heaps as they arrive in the data stream. 
But how can you maintain equal halves of elements in these two heaps? How do you implement this?

We initialize a Max-Heap and a Min-Heap. When adding an element, if the element is greater than the minimum 
element of the Min-Heap, we push it into the Min-Heap; otherwise, we push it into the Max-Heap. If the size 
difference between the two heaps becomes greater than one, we rebalance them by popping an element from the 
larger heap and pushing it into the smaller heap. This process ensures that the elements are evenly distributed 
between the two heaps, allowing us to retrieve the middle element or elements in O(1) time.
*/

//  1. Naive solution:
//  O(addNum) = O(1) but O(findMedian) = O(nlogn) due to sorting after each insert
//  O(n) due to storing the stream of nums in an array nums

//  2. Using two priority queues, one maxHeap and one minHeap
//  O(addNum) = O(logn) where n = current size of stream and O(findMedian) = O(1)
//  O(n) due to the two priority queues

// 2b. Makes insertion code slightly more compact

class MedianFinder {
    priority_queue<int> maxHeap;                                  // stores smaller half of numbers
    priority_queue<int, vector<int>, greater<int>> minHeap;       // stores larger half of numbers
public:
    MedianFinder() { // [#IMP] acually not required to initialize 
        maxHeap = priority_queue<int>();                          // initialize empty max heap
        minHeap = priority_queue<int, vector<int>, greater<int>>(); // initialize empty min heap
    }
    
    void addNum(int num) {
        // add num to either minHeap or maxHeap
        int n = maxHeap.size();
        int m = minHeap.size();
        
        if(n==0 && m==0) minHeap.push(num);                       // first element goes to minHeap
        else if(n > m) {                                          // if maxHeap has more elements
            if(num >= maxHeap.top()) minHeap.push(num);           // if num >= max of smaller half, add to larger half
            else maxHeap.push(num);                               // else add to smaller half
        }
        else if(n <= m) {                                         // if minHeap has more or equal elements
            if(num >= minHeap.top()) minHeap.push(num);           // if num >= min of larger half, add to larger half
            else maxHeap.push(num);                               // else add to smaller half
        }
        
        // rebalance heaps to maintain size property
        n = maxHeap.size();
        m = minHeap.size();
        int rebalanceVal;
        
        if(n > m+1) {                                             // if maxHeap has 2+ more elements
            rebalanceVal = maxHeap.top();                         // move largest from maxHeap
            maxHeap.pop();
            minHeap.push(rebalanceVal);                           // to minHeap
        }
        else if(m > n+1) {                                        // if minHeap has 2+ more elements
            rebalanceVal = minHeap.top();                         // move smallest from minHeap
            minHeap.pop();
            maxHeap.push(rebalanceVal);                           // to maxHeap
        }
    }
    
    double findMedian() {
        int n = maxHeap.size();
        int m = minHeap.size();
        
        if(n == m) return (maxHeap.top() + minHeap.top())/2.0;    // even elements: average of middle two
        else if(n > m) return maxHeap.top();                      // maxHeap has middle element
        else return minHeap.top();                                // minHeap has middle element
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */