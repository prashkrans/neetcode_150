// LC#19. NCLL5. Remove Nth Node From End of List

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */


 // 1. Iterative
 // O(n)
 // O(1) due to curr, size, iter

 class Solution {
    int length(ListNode* head) {
        int i=0;
        while(head) {
            head = head->next;
            i++;
        }
        return i;
    }
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* curr = head;
        int size = length(head);
        int iter = size - n - 1;
        curr = head;
        if(iter==-1) {
            curr = head;
            head = head->next;
            delete curr;
        }
        else {
            while(iter>0) {
            curr = curr->next;
            iter--;
        }
            ListNode* del = curr->next;
            if(del) {
                curr->next = curr->next->next;
                del->next = nullptr;
            }
        delete del;
        }
        return head;
    }
};



// 2a. Recursive (left to right)
// O(n) 
// O(n) due to the recursive stack

class Solution {
    int length(ListNode* head) {
        int i=0;
        while(head) {
            head = head->next;
            i++;
        }
        return i;
    }
    ListNode* traverse(ListNode* head, int k) {
        if(k==0) {
            ListNode* headTemp = head;
            head = head->next;
            headTemp->next = nullptr;
            delete headTemp;
            return head;

        }
        if(k==1) {
            ListNode* headNext = head->next;
            head->next = head->next->next;
            headNext = nullptr;
            delete headNext;
            return head;
        }
        head->next = traverse(head->next, k-1);
        return head;
    }
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int k = length(head) - n;
        cout<<n<<" "<<k<<endl;
        return traverse(head, k);
    }
};


// 2b. Recursive (right to left) - better recursive solution
// O(n) 
// O(n) due to the recursive stack

class Solution {
public:
    ListNode* rec(ListNode* head, int& n) { // n is passed as a reference i.e. n is a global variable
        if (!head) {
            return NULL;
        }

        head -> next = rec(head -> next, n);
        n--;                        // Using n as a global variable and decrementing n when coming out of recursion i.e. right to left
        if (n == 0) {
            return head -> next;    // Simply skip the node where n==0
        } 
        return head;
    }

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        return rec(head, n);
    }
};

// or, same as 2b but deletes the node (Prefer this method)
// Time Complexity: O(n)
// - The recursion traverses the entire linked list once, where n is the number of nodes in the list.

// Space Complexity: O(n)
// - The recursive stack can go as deep as the number of nodes in the linked list.

class Solution { 
    ListNode* rec(ListNode* head, int &n) {              // Similar to a postorder traversal
        if(!head) return nullptr;                        // Base case: reached the end of the list
        head->next = rec(head->next, n);                 // Recurse to the next node
        n--;                                             // Decrement n when returning from recursion
        if(n == 0) {                                     // If n reaches 0, this is the nth node from the end
            ListNode* headNext = head->next;             // Save the next node
            delete head;                                 // Delete the current node
            return headNext;                             // Return the next node to skip the current one
        }
        return head;                                     // Return the current node
    }
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        return rec(head, n);                             // Start the recursive process
    }
};