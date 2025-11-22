/* LC#1306. NAG3b. Jump Game III


### Approach 1: Breadth-First Search with Visited Tracking
1. Use a queue to perform breadth-first search (BFS) starting from the given
index, ensuring we explore all reachable indices.
2. If the start index itself contains 0, return true immediately since
we’ve already reached our goal.
3. Use a visited array to avoid cycles and re-processing of indices, which
helps keep the time complexity linear.
4. From each index, calculate two possible next indices: one by jumping right
(u + arr[u]) and one by jumping left (u - arr[u]).
5. For each of these indices, if they are within bounds and not visited yet,
add them to the queue and mark them as visited.
6. If any of these reachable indices has a value of 0, we return true as we
found a valid path to zero.
7. If the BFS completes without encountering a zero, return false since no
valid path exists.
*/

// 1. Using BFS
// Time Complexity: O(n), where n is the length of arr, as each index is visited at most once. | 0ms beats 100%
// Space Complexity: O(n) for the visited array and queue.

class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();
        if(arr[start] == 0) return true;                             // If starting index has 0, we're already done

        queue<int> q;                                                // BFS queue
        vector<int> visited(n, 0);                                   // Track visited indices to avoid cycles
        q.push(start);                                               // Start BFS from the given index
        visited[start] = 1;                                          // Mark start index as visited

        while(!q.empty()) {                                          // Continue until all reachable indices are explored
            int u = q.front();                                       // Get current index
            q.pop();

            int v = u + arr[u];                                      // Next index by jumping right
            int w = u - arr[u];                                      // Next index by jumping left

            if(v >= 0 && v < n && !visited[v]) {                     // If right jump is valid and not visited
                q.push(v);                                           // Add to queue
                visited[v] = true;                                   // Mark as visited
                if(arr[v] == 0) return true;                         // Found zero, return true
            }

            if(w >= 0 && w < n && !visited[w]) {                     // If left jump is valid and not visited
                q.push(w);                                           // Add to queue
                visited[w] = true;                                   // Mark as visited
                if(arr[w] == 0) return true;                         // Found zero, return true
            }
        }

        return false;                                                // No path leads to zero, return false
    }
};

// or, same as above but compact

class Solution {
    public:
        bool canReach(vector<int>& arr, int start) {
            int n = arr.size();
            if(arr[start] == 0) return true;
            vector<int> visited(n, 0);
            queue<int> q;
            q.push(start);
            visited[start] = 1;
            while(!q.empty()) {
                int u = q.front();
                q.pop();
                vector<int> dirs = {arr[u], -1*arr[u]};
                for(int i=0; i<2; i++) {
                    int v = u + dirs[i];
                    if(v>=0 && v<n && !visited[v]) {
                        q.push(v);
                        visited[v] = true;
                        if(arr[v] == 0) return true;
                    }
                }
            }
            return false;
        }
    };