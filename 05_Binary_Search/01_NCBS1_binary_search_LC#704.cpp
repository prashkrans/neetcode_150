// LC#704. Binary Search


// 1. Iterative Binary Search:
// O(log n) | 0ms beats 100%
// O(1) due to l, r and mid
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size()-1;
        while(l<=r) {   // Note: Make sure is l<=r and not l<r
            int mid = (l + r)/2;
            if(nums[mid] == target) return mid;
            else if(nums[mid] > target) r = mid - 1;
            else if(nums[mid] < target) l = mid + 1;
        }
        return -1;
    }
};


// 2. Recursive Binary Search:
// O(log n) | 0ms beats 100%
// O(log n) due to the recursive stack

class Solution {
    int recursiveBinarySearch(int start, int end, vector<int> &nums, int &k) {
        if(start > end) return -1;
        int mid = (start + end)/2;
        if(nums[mid] == k) return mid;
        if(nums[mid] > k) return recursiveBinarySearch(start, mid-1, nums, k);
        // if(nums[mid] < k) return recursiveBinarySearch(mid+1, end, nums, k); // gives the error: non-void function does not return a val
        return recursiveBinarySearch(mid+1, end, nums, k);
    }

public:
    int search(vector<int> &nums, int target) {
        return recursiveBinarySearch(0, nums.size()-1, nums, target);
    }
};