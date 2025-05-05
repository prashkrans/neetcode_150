/* LC#134. NCGA4. Gas Station
Seems trick but is really easy.
Two variables: 
1. totalGas = summation of (gas[i] - cost[i]) for all is
2. total = 2 options: if total < 0, curr station is not a starting station so make start = i + 1
                      else curr station could be a starting station so continue 

### Approach: Greedy with Single Pass
1. We use a greedy approach to find the starting station that allows completing the circular tour.
2. The solution hinges on two key insights: 
    a. if total gas is less than total cost, no solution exists.
    b. If we start at station i and can't reach station j, then any station between i and j can't be a valid starting point.
3. We track three main variables: 
    totalGas (cumulative sum of all gas-cost differences), 
    tank (current gas in tank), and 
    start (potential starting station).
4. For each station, we calculate the net gain/loss by subtracting the cost from the available gas.
5. We update both the totalGas (global tracker) and tank (current journey tracker) with this gain value.
6. If at any point our tank becomes negative, we can't reach the next station from our current starting point.
7. When tank becomes negative, we update our starting point to the next station and reset the tank.
8. After checking all stations, we verify if a complete circuit is possible by checking if totalGas is negative.
9. This solution is optimal with O(n) time complexity and O(1) space complexity.
*/

// 1. Greedy with Single Pass
// Time Complexity: O(n) where n is the size of gas/cost arrays
// Space Complexity: O(1) as we use only constant extra space

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int totalGas = 0, tank = 0, start = 0;                   // Initialize tracking variables
        for(int i=0; i<gas.size(); i++) {                        // Iterate through all stations
            int gain = gas[i] - cost[i];                         // Calculate net gain/loss at current station
            totalGas += gain;                                    // Track total gain/loss across all stations
            tank += gain;                                        // Update current gas in tank
            if(tank < 0) {                                       // If we can't reach next station
                tank = 0;                                        // Reset tank as we're starting fresh
                start = i + 1;                                   // Update potential starting point to next station
            }
        }
        return (totalGas < 0) ? -1 : start;                      // Return -1 if impossible, otherwise return starting index
    }
};

/*
Dry run for example: gas = [1,2,3,4,5], cost = [3,4,5,1,2] | Ans = starting index: 3  
Initialization:
- totalGas = 0, tank = 0, start = 0

Iteration 0: i = 0
- gain = gas[0] - cost[0] = 1 - 3 = -2
- totalGas = 0 + (-2) = -2
- tank = 0 + (-2) = -2
- tank < 0, so:
  - start = 0 + 1 = 1
  - tank = 0

Iteration 1: i = 1
- gain = gas[1] - cost[1] = 2 - 4 = -2
- totalGas = -2 + (-2) = -4
- tank = 0 + (-2) = -2
- tank < 0, so:
  - start = 1 + 1 = 2
  - tank = 0

Iteration 2: i = 2
- gain = gas[2] - cost[2] = 3 - 5 = -2
- totalGas = -4 + (-2) = -6
- tank = 0 + (-2) = -2
- tank < 0, so:
  - start = 2 + 1 = 3
  - tank = 0

Iteration 3: i = 3
- gain = gas[3] - cost[3] = 4 - 1 = 3
- totalGas = -6 + 3 = -3
- tank = 0 + 3 = 3
- tank ≥ 0, no change to start

Iteration 4: i = 4
- gain = gas[4] - cost[4] = 5 - 2 = 3
- totalGas = -3 + 3 = 0
- tank = 3 + 3 = 6
- tank ≥ 0, no change to start

Final check:
- totalGas = 0, which is not < 0
- Return start = 3

Therefore, the answer is station 3 (0-indexed).

*/