// LC#4. Median of Two Sorted Arrays


// 1. Create a new array from the given two arrays and return its median
// O(n+m) where n = array1.size() and m = array2.size()
// O(n+m) due to the new array

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        vector<int> merged(n+m);
        int i=0, j=0, k=0;
        while(i<n && j<m) {
            if(nums1[i] > nums2[j]) merged[k++] = nums2[j++];
            else merged[k++] = nums1[i++];
        }
        while(i<n) merged[k++] = nums1[i++];
        while(j<m) merged[k++] = nums2[j++];
        int size = n+m;
        //for(int i=0; i<size; i++) cout<<merged[i]<<" "; cout<<"\n";
        if(size%2==0) return (merged[size/2-1] + merged[size/2] + 0.0)/2;       //  Note the use of 0.0
        else return merged[size/2];
    }
};

// 2. Use binary search to find the median
/*
Problem 4: Median of Two Sorted Arrays

Approach: Binary Search
Time Complexity: O(log(min(m,n)))
Space Complexity: O(1)

Key Insights:
1. We want to partition both arrays such that:
   - Left parts of both arrays combined have exactly (m+n+1)/2 elements
   - Every element in left parts <= every element in right parts

2. If we determine the partition of the shorter array, the partition of the
   longer array is automatically determined.

3. Binary search is performed on the shorter array to find the correct partition
   that satisfies our conditions.

4. When we have the correct partitions, the median is either:
   - Max of left parts (if total length is odd)
   - Average of max of left parts and min of right parts (if total length is even)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // Always perform binary search on the smaller array for efficiency
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        
        int x = nums1.size();
        int y = nums2.size();
        int low = 0;
        int high = x;
        
        while (low <= high) {
            // partitionX: number of elements from nums1 in the left part
            int partitionX = (low + high) / 2;
            
            // partitionY: number of elements from nums2 in the left part
            // Ensures left side has (x+y+1)/2 elements in total
            int partitionY = (x + y + 1) / 2 - partitionX;
            
            // Find max/min elements around the partitions
            // If partition is at edge, use INT_MIN/INT_MAX to simplify comparison
            int maxX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
            int maxY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
            
            int minX = (partitionX == x) ? INT_MAX : nums1[partitionX];
            int minY = (partitionY == y) ? INT_MAX : nums2[partitionY];
            
            // Check if we found the correct partition
            if (maxX <= minY && maxY <= minX) {
                // Found the correct partition
                // If total length is odd, median is max of left part
                if ((x + y) % 2 != 0) {
                    return max(maxX, maxY);
                }
                // If total length is even, median is average of max of left part
                // and min of right part
                else {
                    return (max(maxX, maxY) + min(minX, minY)) / 2.0;
                }
            }
            // If maxX > minY, move partition to the left
            else if (maxX > minY) {
                high = partitionX - 1;
            }
            // If maxY > minX, move partition to the right
            else {
                low = partitionX + 1;
            }
        }
        
        // This should never be reached if the input arrays are sorted
        return 0.0;
    }
};

// Utility function to print the median
void printMedian(vector<int>& nums1, vector<int>& nums2) {
    Solution sol;
    cout << "Array 1: ";
    for (int num : nums1) cout << num << " ";
    cout << "\nArray 2: ";
    for (int num : nums2) cout << num << " ";
    cout << "\nMedian: " << sol.findMedianSortedArrays(nums1, nums2) << "\n\n";
}

int main() {
    // Dry Run 1: Even total length
    vector<int> nums1_1 = {1, 3, 8, 9};
    vector<int> nums2_1 = {7, 11, 18, 19, 21, 25};
    cout << "Dry Run 1 (Even length):\n";
    printMedian(nums1_1, nums2_1);
    
    // Walkthrough of Dry Run 1:
    cout << "Walkthrough of Dry Run 1:\n";
    cout << "x = 4, y = 6, total = 10 (even)\n";
    cout << "Start: low = 0, high = 4\n";
    cout << "Iteration 1: partitionX = 2, partitionY = 3\n";
    cout << "maxX = 3, minX = 8, maxY = 11, minY = 18\n";
    cout << "Since 3 <= 18 and 11 <= 8 (false), move right\n";
    cout << "Iteration 2: low = 3, high = 4, partitionX = 3, partitionY = 2\n";
    cout << "maxX = 8, minX = 9, maxY = 7, minY = 11\n";
    cout << "Since 8 <= 11 and 7 <= 9, we found the correct partition\n";
    cout << "Median = (max(8,7) + min(9,11))/2.0 = (8 + 9)/2.0 = 8.5\n\n";
    
    // Dry Run 2: Odd total length
    vector<int> nums1_2 = {23, 26, 31, 35};
    vector<int> nums2_2 = {3, 5, 7, 9, 11, 16};
    cout << "Dry Run 2 (Odd length):\n";
    printMedian(nums1_2, nums2_2);
    
    // Walkthrough of Dry Run 2:
    cout << "Walkthrough of Dry Run 2:\n";
    cout << "x = 4, y = 6, total = 10 (odd)\n";
    cout << "Start: low = 0, high = 4\n";
    cout << "Iteration 1: partitionX = 2, partitionY = 3\n";
    cout << "maxX = 26, minX = 31, maxY = 7, minY = 9\n";
    cout << "Since 26 > 9, move left\n";
    cout << "Iteration 2: low = 0, high = 1, partitionX = 0, partitionY = 5\n";
    cout << "maxX = INT_MIN, minX = 23, maxY = 11, minY = 16\n";
    cout << "Since INT_MIN <= 16 and 11 <= 23, we found the correct partition\n";
    cout << "Median = max(INT_MIN, 11) = 11\n\n";
    
    // Dry Run 3: Edge case with empty array
    vector<int> nums1_3 = {};
    vector<int> nums2_3 = {1, 2, 3, 4, 5};
    cout << "Dry Run 3 (Empty array):\n";
    printMedian(nums1_3, nums2_3);
    
    return 0;
}