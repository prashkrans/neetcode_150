// LC#74. NCBS2. Search a 2D Matrix


// 1. Binary Search for cols but linear search for rows
// O(m + log n) where m = no. of rows and n = no. of cols | But this takes 0ms and beats 100%
// O(n) due to the vector nums

class Solution {
    bool binarySearch(vector<int>& nums, int &target) {
        int l = 0, r = nums.size()-1;
        while(l<=r) {
            int mid = (l + r)/2;
            if(nums[mid] == target) return true;
            else if(nums[mid] > target) r = mid - 1;
            else l = mid + 1; 
        }
        return false;
    }

public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        for(int i=0; i<m; i++) {
            if(target >= matrix[i][0] && target <= matrix[i][n-1]) {
                vector<int> nums;
                for(int j=0; j<n; j++) nums.push_back(matrix[i][j]);
                return binarySearch(nums, target);
            }
        }
        return false; // [#IMP] to return false from here
    }
};


// 2. Binary Search for both rows and cols (TODO)
// O(log m + log n) where m = no. of rows and n = no. of cols
// O(n) due to the vector nums
