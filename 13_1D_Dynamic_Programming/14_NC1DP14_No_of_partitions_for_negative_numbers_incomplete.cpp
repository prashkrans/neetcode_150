/**
Find the number of partitions of an array such that each contiguous partition consists of atleast one negative number.
eg. [-1,-2,-3,-4] has 8 possible partitions :

[-1], [-2], [-3], [-4]

[-1, -2], [-3], [-4]

[-1, -2, -3], [-4]

[-1, -2, -3, -4]

[-1], [-2, -3], [-4]

[-1], [-2, -3, -4]

[-1], [-2], [-3, -4]

[-1, -2], [-3, -4]

*/



#include<iostream>
#include<vector>

using namespace std;

class Solution {
    int recFunc(int start, int end, vector<int> &nums) {
        int n = end - start + 1;
        if(n==0 || n==1 || n==2) return n;
        int left = 0, right = 0;
        int ans = 1;
        for(int i = start+1; i<=end; i++) {
            int mid = start;
            mid = i;
            left = recFunc(start, mid-1, nums);
            right = recFunc(mid, end, nums);
            ans += left * right;
        }
        return ans;
    }
public:
    int noOfPartitions(vector<int> &nums) {
        return recFunc(0, nums.size()-1, nums);
    }
};

int main() {
    int n;
    cout<<"Input the value of n: ";
    cin>>n;
    cout<<"Input the values of nums: ";
    vector<int> nums(n);
    for(int i=0; i<n; i++) {
        cin>>nums[i];
    }
    for(auto num: nums) cout<<num<<" "; cout<<endl;
    Solution sol;
    cout<<"Number of partitions: "<<sol.noOfPartitions(nums)<<endl;
    return 0;
}