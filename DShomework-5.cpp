// Give a more robust implementation of the circularly linked list data structure of Section 3.4.1(of our lecture slide), 
//which throws an appropriate exception if an illegal operation is attempted.
#include <iostream>
using namespace std;

template <typename T>
class CircularLinkedList;

template <typename T>
class Node {
private:
    T elem;
    Node<T> *next;
    friend class CircularLinkedList<T>;
};

template <typename T>
class CircularLinkedList {
private:
    Node<T> *cursor;
public:
    CircularLinkedList(): cursor(nullptr) {}
    ~CircularLinkedList() {
        while (!empty()) {
            remove();
        }
    }

    bool empty() const {
        return cursor == nullptr;
    }
    const T& front() const {

        if (empty()) throw "The circular linked list is empty, can not run front function";
        return cursor->next->elem;
    }

    const T& back() const {

        if (empty()) throw "The circular linked list is empty, can not run back function";
        return cursor->elem;
    }
    void advance() {

        if (empty()) throw "The circular linked list is empty, can not run advance function";
        cursor = cursor->next;
    }
    void add(const T& e) {
        Node<T> *v = new Node<T>;
        v->elem = e;
        if (cursor == nullptr) {
            v->next = v;
            cursor = v;
        } else {
            v->next = cursor->next;
            cursor->next = v;
        }
    }

    void remove() {
        if (empty()) throw "Can not remove element from the empty list";

        Node<T> *old = cursor->next;
        if (old == cursor) {
            cursor == nullptr;
        } else {
            cursor->next = old->next;
        }
        delete old;
    }
};

int main() {
    int a_test = 20, b_test = 25, c_test = 30;
    CircularLinkedList<int> cl;
    
    try {
        cl.front();
    } catch(const char *msg) {
        cout << "Exception: " << msg << endl;
    }
    try {
        cl.back();
    } catch(const char *msg) {
        cout << "Exception: " << msg << endl;
    }
    try {
        cl.advance();
    } catch(const char *msg) {
        cout << "Exception: " << msg << endl;
    }
    try {
        cl.remove();
    } catch(const char *msg) {
        cout << "Exception: " << msg << endl;
    }
    
    return 0;
}