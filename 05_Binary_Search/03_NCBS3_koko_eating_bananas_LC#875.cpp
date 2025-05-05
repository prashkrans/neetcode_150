/* LC# 875. Koko Eating Bananas

Approach:
Consider m to be the largest pile and n to be the number of piles. A brute force solution would be to 
linearly check all values from 1 to m and find the minimum possible value at which Koko can complete the task. 
This approach would take O(n * m) time. Can you think of a more efficient method? Perhaps an efficient searching 
algorithm could help.

Rather than linearly scanning, we can use binary search. The upper bound of k is max(piles) and since we are 
only dealing with positive values, the lower bound is 1. The search space of our binary search is 1 through 
max(piles). This allows us to find the smallest possible k using binary search.


Time Complexity: O(n * log(k))
- n = number of piles
- k = maximum pile size
- Binary search takes O(log k) iterations
- Each iteration calls totalTime() which is O(n)

Space Complexity: O(log k)
- O(1) auxiliary space for variables
- O(log k) space for the recursion stack in binary search
- The recursive binary search can go log k levels deep

*/

// 1. Binary Search (Recursive)
// O(n*log k) where n = piles.size() and k = max value in piles
// O(log k) due to the recursion stack

typedef long long ll;

class Solution {
    ll totalTime(vector<int> &piles, int k) { // Calculates total time needed to eat all piles at speed k
        ll sum = 0;
        for(int i=0; i<piles.size(); i++) {
            int rem = piles[i] % k;
            ll currHours = piles[i] / k; 
            if(rem>0) currHours++;          // ceil(piles[i]/k) - take ceiling since we can't eat partial bananas
            sum += currHours;
        }
        // cout<<"k: "<<k<<" totalSum: "<<sum<<endl;
        return sum;
    }

    // Binary search to find minimum k where total time <= h
    int binarySearch(int l, int r, vector<int> &piles, int h, int &ans) {
        if(l>r) return -1;                   // Base case: search space is empty
        int k = (l + r)/2;                   // Calculate midpoint for current search space
        ll time = totalTime(piles, k);       // Calculate time for current k value
        if(time <= h) {                      // If current k works (time is within h hours)
            ans = min(ans, k);               // Update answer with smallest valid k found so far
            return binarySearch(l, k-1, piles, h, ans); // Continue searching left half for even smaller k
        }
        return binarySearch(k+1, r, piles, h, ans); // If current k is too slow, search right half for larger k
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) { // Main function to find minimum eating speed k
        int upperBoundOfK = INT_MIN;         // Will hold the maximum pile size
        for(int i=0; i<piles.size(); i++) upperBoundOfK = max(upperBoundOfK, piles[i]); // Find max pile size
        int ans = INT_MAX;                   // Initialize answer to maximum possible value
        binarySearch(1, upperBoundOfK, piles, h, ans); // Search for minimum valid k between 1 and max pile size
        return ans;                          // Return the minimum valid eating speed
    }
};

// 2. Naive Solution gets TLE
// O(n*k)
// O(1)

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int k = 1;
        while (true) {
            long long totalTime = 0;
            for (int pile : piles) {
                totalTime += (pile + k - 1) / k;  
            }

            if (totalTime <= h) {
                return k;
            }
            k++;
        }
    }
};