/* LC#853. NCST6. Car Fleet

### Mathematical Approach:

1. Pair each car's position with its speed using a vector of pairs.
2. Sort the cars in descending order of position because cars closer to the target are considered first.
3. Use a stack to keep track of car fleets:
   - Compute the time each car takes to reach the target: `time = (target - position) / speed`.
   - If the current car's time is greater than the top of the stack (fleet ahead), it forms a new fleet.
   - If it is less than or equal, it will merge with the fleet ahead and does not form a new one.
4. Stack stores the time to reach target for each fleet (top being the slowest leading fleet).
5. Key Insight: A faster car can’t overtake the slower one ahead; it will merge with it if it catches up.
6. Final fleet count is the number of times a car couldn't catch up and had to form a new fleet — stored as the stack size.

*/
// Using a stack
// Time Complexity: O(n log n) due to sorting
// Space Complexity: O(n) for the timeToReachTarget vector and the stack

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size(); // number of cars
        vector<pair<int, int>> cars; // stores (position, speed) pairs

        for(int i=0; i<n; i++) 
            cars.push_back({position[i], speed[i]}); // populate the cars vector with position and speed

        sort(cars.begin(), cars.end(), greater<pair<int, int>>()); // sort cars by position in descending order

        vector<float> timeToReachTarget; // stores time each car takes to reach the target
        for(int i=0; i<n; i++) 
            timeToReachTarget.push_back((float)(target - cars[i].first) / cars[i].second); // compute time to target

        stack<float> st; // stack to track distinct fleets
        for(int i=0; i<n; i++) {
            if(st.empty()) st.push(timeToReachTarget[i]); // first car forms a new fleet
            else {
                if(timeToReachTarget[i] > st.top()) st.push(timeToReachTarget[i]); // slower car forms new fleet
                // else, current car joins the fleet ahead (no push)
            }
        }
        return st.size(); // number of fleets formed
    }
};

// Without creating a timeToReachTarget vector
// Time Complexity: O(n log n) due to sorting the cars based on position
// Space Complexity: O(n) for the stack and the cars vector

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();                              // number of cars
        vector<pair<int, int>> cars;

        for(int i=0; i<n; i++) 
            cars.push_back({position[i], speed[i]});          // combine position and speed as a pair
        sort(cars.begin(), cars.end(), greater<pair<int, int>>()); // sort cars in descending order of position

        stack<double> st;                                     // to store time to reach the target
        for(int i=0; i<n; i++) {
            double timeToReachTarget = ((double)(target - cars[i].first) / cars[i].second); // time = distance / speed
            if(st.empty()) st.push(timeToReachTarget);        // first car always forms a fleet
            else {
                if(timeToReachTarget > st.top()) st.push(timeToReachTarget); // forms a new fleet if slower
                // if timeToReachTarget <= st.top(), it merges with the car in front (no push)
            }
        }

        return st.size();                                     // number of fleets is the stack size
    }
};
    
    