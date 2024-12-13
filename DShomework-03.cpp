//Add a function size() to our C++ implementation of a singly link list.  
//In the main function,use a case to show the size value of an example of a singly link list.
#include <iostream>
using namespace std;

template <typename T>
class SinglyLinkedList;

template <typename T>
class Node {
private:
    T elem;
    Node<T> *next;
    friend class SinglyLinkedList<T>;
};

template <typename T>
class SinglyLinkedList {
private:
    Node<T> *head;
public:
    SinglyLinkedList(): head(nullptr) {}
    ~SinglyLinkedList() {
        while (!empty()) {
            removeFront();
        }
    }

    bool empty() const {
        return head == nullptr;
    }
    const T& front() const {
        return head->elem;
    }
    void addFront(const T& e) {
        Node<T> *v = new Node<T>;
        v->elem = e;
        v->next = head;
        head = v;
    }
    void removeFront() {
        Node<T> *old = head;
        head = old->next;
        delete old;
    }

    int size() {
        int count = 0;
        Node<T> *cur = head;
        while (cur) {
            count++;
            cur = cur->next;
        }
        return count;
    }
};

int main() {
    int a_test = 20;
    int b_test = 30;
    SinglyLinkedList<int> sl;

    sl.addFront(a_test);
    sl.addFront(b_test);
    int size = sl.size();

    cout << "The size of linked list: " << size << endl;

    return 0;
}