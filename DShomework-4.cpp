//Give a fully generic implementation of the doubly linked list data structure of Section 3.3.3(or of our lecture slide) by using a templated class.
#include <iostream>

using namespace std;

template <typename T>
class DoublyLinkedList;

template <typename T>
class Node {
private:
    T elem;
    Node<T> *prev;
    Node<T> *next;
    friend class DoublyLinkedList<T>;
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T> *head;
    Node<T> *trail;
public:
    DoublyLinkedList() {
        head = new Node<T>; 
        trail = new Node<T>; 
        head->next = trail;
        trail->prev = head;
    }
    ~DoublyLinkedList() {
        while (!empty()) {
            removeFront();
        }
        delete head;
        delete trail;
    }

    bool empty() const {
        return head->next == trail;
    }
    const T& front() const {
        return head->next->elem;
    }

    const T& back() const {
        return trail->prev->elem;
    }
    void add(Node<T> *v, const T& e) {
        Node<T> *u = new Node<T>;
        u->elem = e;
        u->next = v;
        u->prev = v->prev;
        v->prev->next = u;
        v->prev = u;
    }

    void addFront(const T& e) {
        add(head->next, e); 
    }

    void addBack(const T& e) {
        add(trail, e); 
    }

    void remove(Node<T> *v) {
        Node<T> *u = v->prev;
        Node<T> *w = v->next;
        u->next = w;
        w->prev = u;
        delete v;
    }

    void removeFront() {
        remove(head->next);
    }
    
    void removeBack() {
        remove(trail->prev);
    }
};

int main() {
    
    int a_test = 10;
    int b_test = 20;
    int c_test = 30;
    int d_test = 40;
    int e_test = 50;
    
    DoublyLinkedList<int> dl;

    dl.addFront(a_test);
    dl.addBack(b_test);
    dl.addFront(c_test);
    dl.addBack(d_test);
    dl.addFront(e_test);

    cout << "The linked list is empty: " << (dl.empty() ? "Yes" : "No") << endl;
    cout << "The first element: " << dl.front() << endl;
    cout << "The last element: " << dl.back() << endl;

    dl.removeFront();
    dl.removeBack();

    cout << "The rest element in linked list after removal: " << dl.front() << endl;
    
    return 0;
}
