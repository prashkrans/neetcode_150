// LC#25. NCLL11. Reverse Nodes in k-Group

// 1. Using standard reverseList and recursion (my custom code)
// O(n) time — since (traverse + reverse + recurse) = O(3n) ~ O(n) | 0ms beats 100%
// O(max(k, n/k)) space — due to recursion depth (reverseList: O(k), reverseKGroup: O(n/k))

class Solution {
    ListNode* reverseList(ListNode* head) {
        if(!head || !head->next) return head;                  // Base case: empty list or single node
        ListNode* res = reverseList(head->next);               // Recurse on the next node
        head->next->next = head;                               // Reverse the link
        head->next = nullptr;                                  // Set current node's next to nullptr
        return res;                                            // Return new head of reversed list
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(!head || !head->next) return head;                  // Base case: list too short to reverse
        ListNode* curr = head;
        int i = 1;
        while(curr && i < k) {                                 // Traverse k nodes ahead
            curr = curr->next;
            i++;
        }
        if(curr && i == k) {                                   // Found k nodes to reverse
            ListNode* currNext = curr->next;                   // Store (k+1)th node
            curr->next = nullptr;                              // Break the list after k nodes [#IMP]
            ListNode* reversedHead = reverseList(head);        // Reverse current k nodes
            head->next = reverseKGroup(currNext, k);           // Recurse for the remaining list
            return reversedHead;                               // Return new head after reversal
        } else {
            return head;                                       // Less than k nodes, return as is
        }
    }
};

// 2. Iteration (TODO - For now copied the solution below):
// O(n)
// O(1) space optimized

class Solution {
        ListNode* getKth(ListNode* curr, int k) {
            while (curr && k > 0) {
                curr = curr->next;
                k--;
            }
            return curr;
        }
    public:
        ListNode* reverseKGroup(ListNode* head, int k) {
            ListNode* dummy = new ListNode(0, head);
            ListNode* groupPrev = dummy;
    
            while (true) {
                ListNode* kth = getKth(groupPrev, k);
                if (!kth) {
                    break;
                }
                ListNode* groupNext = kth->next;
    
                ListNode* prev = kth->next;
                ListNode* curr = groupPrev->next;
                while (curr != groupNext) {
                    ListNode* tmp = curr->next;
                    curr->next = prev;
                    prev = curr;
                    curr = tmp;
                }
    
                ListNode* tmp = groupPrev->next;
                groupPrev->next = kth;
                groupPrev = tmp;
            }
            return dummy->next;
        }
    };