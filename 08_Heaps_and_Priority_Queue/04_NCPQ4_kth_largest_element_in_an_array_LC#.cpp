// LC#215. Kth Largest Element in an Array

// 1. Min heap of size k
// O(nlogk)
// O(k), not O(n)

class Solution {
    public:
        int findKthLargest(vector<int>& nums, int k) {
            priority_queue<int, vector<int>, greater<int>> pq;
            for(int i=0; i<nums.size(); i++) {
                pq.push(nums[i]);
                if(pq.size() > k) pq.pop();
            }
            return pq.top();
        }
    };
    