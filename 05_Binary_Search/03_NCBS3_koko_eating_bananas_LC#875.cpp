/* LC# 875. Koko Eating Bananas

Main logic:
k varies from 1 to maxVal where maxVal is max value of banana piles 
=> l = 1 and r = maxVal
while (l <= r) 
    Calc h for each k = (l + r) / 2
    if calcH <= h: r = k - 1
    else if calcH > h: l = k + 1
return l

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

// 2a. Binary Search (Iterative) (Prefer this approach over recursive and naive)
// O(n*log k) where n = piles.size() and k = max value in piles
// O(1) due to a few variables

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

    int binarySearch(int l, int r, vector<int> &piles, int h) {
        while(l <= r) { // Note: l <= r 
            int mid = l + (r - l) / 2;
            if(totalTime(piles, mid) <= h) r = mid - 1; // Note: calcH <= h => r = mid - 1 (not mid) 
            else l = mid + 1;
        }
        return l;
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int maxVal = INT_MIN;         
        for(int i=0; i<piles.size(); i++) maxVal = max(maxVal, piles[i]); 
        return binarySearch(1, maxVal, piles, h); 
    }
};

// or, same as above but l < r

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

    int binarySearch(int l, int r, vector<int> &piles, int h) {
        while(l < r) { // Note: l <= r 
            int mid = l + (r - l) / 2;
            if(totalTime(piles, mid) <= h) r = mid; // Note: calcH <= h => r = mid - 1 (not mid) 
            else l = mid + 1;
        }
        return l;
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int maxVal = INT_MIN;         
        for(int i=0; i<piles.size(); i++) maxVal = max(maxVal, piles[i]); 
        return binarySearch(1, maxVal, piles, h); 
    }
};


// 2b. Binary Search (Recursive)
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

    int binarySearch(int l, int r, vector<int> &piles, int h) {
        while(l < r) { // Note: l <= r 
            int mid = l + (r - l) / 2;
            if(totalTime(piles, mid) <= h) r = mid; // Note: calcH <= h => r = mid - 1 (not mid) 
            else l = mid + 1;
        }
        return l;
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int maxVal = INT_MIN;         
        for(int i=0; i<piles.size(); i++) maxVal = max(maxVal, piles[i]); 
        return binarySearch(1, maxVal, piles, h); 
    }
};

// or, same as above but l < r

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

    int binarySearch(int l, int r, vector<int> &piles, int h) {
        while(l < r) { // Note: l <= r 
            int mid = l + (r - l) / 2;
            if(totalTime(piles, mid) <= h) r = mid; // Note: calcH <= h => r = mid - 1 (not mid) 
            else l = mid + 1;
        }
        return l;
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int maxVal = INT_MIN;         
        for(int i=0; i<piles.size(); i++) maxVal = max(maxVal, piles[i]); 
        return binarySearch(1, maxVal, piles, h); 
    }
};

// 1. Naive Solution gets TLE
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