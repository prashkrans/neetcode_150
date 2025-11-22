// LC#1046. NCPQ2. Last Stone Weight

// 1. Max heap
// O(nlogn)
// O(n)
class Solution {
    public:
        int lastStoneWeight(vector<int>& stones) {
            priority_queue<int> pq;
            for(auto stone: stones) pq.push(stone);
            while(pq.size()>1) {
                int first = pq.top(); pq.pop();
                int second = pq.top(); pq.pop();
                int rem = first - second;
                if(rem!=0) pq.push(rem);
            }
            if(pq.size()==1) return pq.top();
            else return 0;
        }
    };
    
    
    // 6 4 3 2 2 
    // 3 2 2 2
    // 2 2 1
    // 1