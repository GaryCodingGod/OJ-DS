// Modify the stack ADT implementation from Section 5.1.5 of the textbook (or as shown in thelecture slides on implementing a stack with a generic linked list) 
// to make it a fully generic class using templates.
#include <iostream>

using namespace std;

template <class T>
class Stack;

template <class T>
class Node {
private:
    int data;
    Node<T> *next;
    friend class Stack<T>;
public:
    Node(): data(0), next(nullptr) {}
    Node(T d): data(d), next(nullptr) {}
    Node(T d, Node<T> *nxt): data(d), next(nxt) {}
};


template <class T>
class Stack {
private:
    int size;
    Node<T> *top;
public:
    Stack(): size(0), top(nullptr) {}

    bool isEmpty() const {
        return top == nullptr;
    }

    int getSize() const {
        return size;
    }

    T& getTop() const {
        if (isEmpty()) {
            throw "Stack is empty";
        }
        return top->data;
    }

    void push(const T& info) {
        Node<T> *newNode = new Node<T>(info);
        size++;
        if (isEmpty()) {
            top = newNode;
        } else {
            newNode->next = top;
            top = newNode;
        }
    }

    void pop() {
        if (isEmpty()) {
            throw "Stack is empty";
        } else {
            Node<T> *delNode = top;
            top = delNode->next;
            delete delNode;
        }
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

int main() {
    
    Stack<int> st;
    cout << "The stack is empty or not: " << (st.isEmpty() ? "True" : "False") << endl;
    try {
        st.pop();
    } catch(const char *msg) {
        cout << msg << endl;
    }

    try {
        st.getTop();
    } catch(const char *msg) {
        cout << msg << endl;
    }
    st.push(1);
    st.push(2);
    cout << "The size: " << st.getSize() << endl;
    cout << "The top element: " << st.getTop() << endl;
    cout << "The stack is empty or not: " << (st.isEmpty() ? "True" : "False") << endl;
    st.pop();
    cout << "The top element: " << st.getTop() << endl;
    
    

    return 0;
}
