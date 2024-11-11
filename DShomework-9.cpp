//Implement the queue ADT in a fully generic manner using a dynamically allocated C++ array
#include <iostream>

using namespace std;

template <class T>
class Queue {
private:
    T *queue;
    int front;
    int rear;
    int capacity;
    int size;
public:
    Queue(int queueCapacity): capacity(queueCapacity), size(0) {
        queue = new T[capacity];
        front = rear = 0;
    }

    bool isEmpty() const {
        return front == rear;
    }

    int getSize() const {
        return size;
    }

    T& getFront() const {
        if (isEmpty()) {
            throw "Queue is empty";
        }
        return queue[(front + 1) % capacity];
    }

    void enqueue(const T& info) {
        if ((rear + 1) % capacity == front) {
            throw "Queue is full";
        } else {
            size++;
            rear = (rear + 1) % capacity;
            queue[rear] = info;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            throw "Queue is empty";
        } else {
            front = (front + 1) % capacity;
        }
    }

    ~Queue() {
        delete [] queue;
    }
};

int main() {
    
    Queue<int> qu(5);
    cout << "Is queue is empty or not: " << (qu.isEmpty() ? "True" : "False") << endl;
    qu.enqueue(3);
    qu.enqueue(4);
    qu.enqueue(5);


    cout << "Is queue is empty or not: " << (qu.isEmpty() ? "True" : "False") << endl;
    cout << "The queue size: " << qu.getSize() << endl;
    cout << "The front element: " << qu.getFront() << endl;
    
    qu.dequeue();
    cout << "The front element: " << qu.getFront() << endl;


    return 0;
}
