// LC#155. NCST2. Min Stack

// 1a. Using two stacks
// O(1) for each push(), pop(), top(), getMin()
// O(n) due to the extra stack

class MinStack {
    stack<int> s1;
    stack<int> s2;
public:
    MinStack() {
        s1 = stack<int> ();
        s2 = stack<int> ();
    }
    
    void push(int val) {
        s1.push(val);
        if(s2.empty()) s2.push(val);
        else s2.push(min(s2.top(), val));   // Pushing to both stacks for each time push() is called
    }
    
    void pop() {                            // Popping both for each time pop() is called        
        s1.pop();
        s2.pop();                   
    }
    
    int top() {
        return s1.top();
    }
    
    int getMin() {
        return s2.top();
    }
};


// 1b. Using two stacks. Pushing in stack2 only when currVal <= s2.top() and popping from s2 only when s2.top() == val
// O(1) for each push(), pop(), top(), getMin()
// O(n) due to the extra stack

class MinStack {
    stack<int> s1;
    stack<int> s2;
public:
    MinStack() {
        s1 = stack<int> ();
        s2 = stack<int> ();
    }
    
    void push(int val) {
        s1.push(val);
        if(s2.empty()) s2.push(val);
        else if(s2.top() >= val) s2.push(val); // Note >= is important
    }
    
    void pop() {
        int val = s1.top();
        s1.pop();
        if(s2.top() == val) s2.pop();
    }
    
    int top() {
        return s1.top();
    }
    
    int getMin() {
        return s2.top();
    }
};
