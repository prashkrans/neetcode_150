// LC#Premium. NCAG5. Alien Dictionary

// Approach: 
// if(word1.size() > word2.size() && word1.substr(0, minLength) == word2) // Important edge case
// The relative ordering of the characters can be treated as edges. For example, consider the words ordered 
// as ["ape", "apple"]. "ape" comes before "apple", which indicates that 'e' is a predecessor of 'p'. Therefore, 
// there is a directed edge e -> p, and this dependency should be valid across all the words. In this way, we can 
// build an adjacency list by comparing adjacent words. Can you think of an algorithm that is suitable to find a valid ordering?
// We can use Topological Sort to ensure every node appears after its predecessor. Using DFS, we traverse the graph built 
// from the adjacency list. A visited map tracks nodes in the current DFS path: False means not in the path, and True means in the path. 
// If any DFS call returns True, it indicates a cycle and we return immediately. How do we extract the ordering from this DFS?



// Method 1. Create adjL then use Kahn's BFS algo to check for a cycle, iff DAG return topoSort
// Running time: O(N + V + E)
// Auxiliary space: O(V + E) 
// where N is the sum of the lengths of all the strings, V is the number of unique characters 
// (vertices), and E is the number of edges.


class Solution {
    // Helper function to print the adjacency list (for debugging)
    void printAdjList(unordered_map<char, vector<char>> &adjL) {
        for(auto i: adjL) {
            char u = i.first;
            cout<< u << " -> ";
            for(auto v: adjL[u]) cout<< v <<" ";
            cout<<endl;
        }
    }
    
    // Implements Kahn's algorithm for topological sorting using BFS
    string bfsKahns(unordered_map<char, vector<char>> &adjL, unordered_map<char, int> &indegree) {
        string topoSort;
        
        // Calculate indegree for each vertex
        for(auto i: adjL) {
            char u = i.first; // indegree[u] already initialized to 0
            for(auto v: adjL[u])
                indegree[v]++;
        }

        // Add vertices with 0 indegree to queue (starting points)
        queue<char> q;
        for(auto i: indegree) {
            int u = i.first; 
            if(indegree[u]==0)  {
                q.push(u);
                topoSort += u; // Else comment this line
            }
        }   

        // Process vertices in topological order
        while(!q.empty()) {
            char u = q.front();
            q.pop();
            // topoSort += u // Add u to topoSort here
            for(auto v: adjL[u]) {
                indegree[v]--; // Decrease indegree after removing incoming edge
                if(indegree[v]==0) { // If all dependencies processed, add to queue
                    q.push(v);
                    topoSort += v; // Else comment this line too 
                }
            }
        }
        
        // If topological sort doesn't include all vertices, there must be a cycle
        return (topoSort.size() == adjL.size()) ? topoSort : "";       
    }
public:
    string foreignDictionary(vector<string>& words) {
        // Initialize adjacency list and indegree map for each character
        unordered_map<char, vector<char>> adjL;
        unordered_map<char, int> indegree;
        for(auto word: words) {
            for(auto ch: word) {
                adjL[ch] = vector<char>(); // Initialize empty adjacency list
                indegree[ch] = 0; // Initialize indegree to 0
            }
        }
        
        // Build graph based on adjacent word comparisons
        for(int i=0; i<words.size()-1; i++) {
            string word1 = words[i];    
            string word2 = words[i+1];
            int minLength = min(word1.size(), word2.size());
            
            // [#IMP] edge case: Handle invalid dictionary case: if word1 is a prefix of word2 but appears before it
            if(word1.size() > word2.size() && word1.substr(0, minLength) == word2)
                return "";
                
            // Find first differing character to establish order relationship
            for(int i=0; i<minLength; i++) {
                char u = word1[i];
                char v = word2[i];
                if(u != v) {
                    adjL[u].push_back(v); // Add directed edge u->v
                    break; // Only use first difference to establish order
                }
            }
        }
        
        // Perform topological sort to get character order
        return bfsKahns(adjL, indegree);
    }
};

// Method 2: Create adjL then use DFS + recStack to check for a cycle, iff DAG return topoSort
// Running time: O(N + V + E)
// Auxiliary space: O(V + E) 
// where N is the sum of the lengths of all the strings, V is the number of unique characters 
// (vertices), and E is the number of edges.

class Solution {
    bool isCyclicDfs(char u, unordered_map<char, vector<char>> &adjL, unordered_map<char, int> &visited, unordered_map<char, int> &recStack, string &topoSort) {
        visited[u] = 1;
        recStack[u] = 1;
        for(auto v: adjL[u]) {
            if(!visited[v]) {
                if(isCyclicDfs(v, adjL, visited, recStack, topoSort)) return true;
            }
            else if(recStack[v]==1) return true;
        }
        topoSort += u;
        recStack[u] = 0;
        return false;
    }
    
public:
    string foreignDictionary(vector<string>& words) {
        unordered_map<char, vector<char>> adjL;
        unordered_map<char, int> visited;
        unordered_map<char, int> recStack;
        for(auto word: words) {
            for(auto ch: word) {
                adjL[ch] = vector<char>();
                visited[ch] = 0;
                recStack[ch] = 0;
            }
        }
        
        for(int i=0; i<words.size()-1; i++) {
            string word1 = words[i];    
            string word2 = words[i+1];
            int minLength = min(word1.size(), word2.size());   
            if(word1.size() > word2.size() && word1.substr(0, minLength) == word2) // Missed this edge case
                return "";
            for(int i=0; i<minLength; i++) {    // Condition for an edge, creates adjacency list here
                char u = word1[i];
                char v = word2[i];
                if(u != v) {
                    adjL[u].push_back(v);   // directed edge
                    break;                  // important to use break here
                }
            }
        }
        string topoSort;
        for(auto i: adjL) {
            char u = i.first;
            if(!visited[u]) {
                if(isCyclicDfs(u, adjL, visited, recStack, topoSort)) return "";
            }
        }
        reverse(topoSort.begin(), topoSort.end());
        return topoSort;       
    }
};
