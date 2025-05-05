// LC#207. NCG7 Course Schedule I


// This is basically a problem to check whether the graph is DAG (Directed Acyclic Graph)

// Method 1. Create adjacency list from the given m edges and then use Kahns' Algo:
// a. Create Indegree array
// b. Push all the nodes in a queue with indegree == 0
// c. For all v in out edges of u, reduce indgree of v by 1 and if indegree[v] becomes 0 push it to queue
// d. If the count of all the nodes pushed into queue == no. of nodes in the graph, then return true else false

// Running time: O(n+m) or O(nodes + edges) 
// Auxiliary space: O(n) due to the bfs queue


class Solution {
    public:
        bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {        
            // vector<vector<int>> adjList(numCourses, {}); // Incorrect Initialization
            vector<vector<int>> adjList(numCourses, vector<int>()); // Initialization
            vector<int> indegree(numCourses, 0);
    
            // numCourses is n: number of nodes
            // prequisites.size() is m: number of edges
            for(int i=0; i<prerequisites.size(); i++) { 
                int u = prerequisites[i][1];            // Note prerequisites are given in the form of [{v, u}] not [{u, v}]
                int v = prerequisites[i][0];
                adjList[u].push_back(v);                // A directed edge here goes from u to v only
                // adjList[v].push_back({});            // Incorrect
                indegree[v]++;
            }
    
            queue<int> q;
            int countNodes = 0;
            for(int u=0; u<numCourses; u++) {
                if(indegree[u]==0) {
                    q.push(u);
                    countNodes++;
                }
            }    
            
            while(!q.empty()) {
                int u = q.front();
                q.pop();
                for(vector<int>::iterator it=adjList[u].begin(); it!=adjList[u].end(); ++it) {
                    int v = *it;
                    indegree[v]--;
                    if(indegree[v]==0) {
                        q.push(v);
                        countNodes++;
                    }
                }
            }
            return (countNodes == numCourses);
        }
    };
    

// Method 2: DFS (Learn this but prefer Kahn's algo over this) | Same as using DFS for cycle detection in a directed graph
// Running time: O(n+m) or O(nodes + edges) 
// Auxiliary space: O(n) due to the dfs stack

    class Solution {
        public:
            bool dfsCycleDetected(int u, vector<vector<int>> &adjL, vector<int> &visited, vector<int> &stack) {
                visited[u] = 1;
                stack[u] = 1;
                for(auto v: adjL[u]) {
                    if(!visited[v]) {
                        if(dfsCycleDetected(v, adjL, visited, stack)) return true; // Note return true as soon as cycle detected
                    }
                    else if(stack[v]) return true;
                }
                stack[u] = 0;
                return false;
            }
        
            bool canFinish(int n, vector<vector<int>>& e) {
                // n: no. of nodes or courses and m: no. of edges
                int m = e.size();
                vector<vector<int>> adjL(n, vector<int>());
                vector<int> visited(n, 0);
                vector<int> stack(n, 0);    // Using a vector for a stack here to search an element in the stack in O(1) instead of O(n)
                for(int i=0; i<m; i++) {
                    int u = e[i][1];
                    int v = e[i][0];
                    adjL[u].push_back(v);
                }
                for(int src = 0; src<n; src++) {
                    if(dfsCycleDetected(src, adjL, visited, stack))
                        return false;
                }
                return true;
            }
        };