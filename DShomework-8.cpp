//Implement  a  version  of  the  deque  ADT  with  a  fixed  capacity,  using  an  array  in  a  circula
//structure similar to the circular queue implementation discussed in Section 5.2.4 of the textbook
#include <iostream>

using namespace std;

class Dequeue {
private:
    int dequeue[6];
    int front;
    int rear;
public:
    Dequeue() {
        front = rear = -1;
    }
    
    bool isEmpty() const {
        return front == -1;
    }

    bool isFull() const {
        return ((front == 0 && rear == 5) || (rear == (front - 1) % 5));
    }

    int getFront() const {
        if (isEmpty()) {
            throw "Dequeue is emtpy";
        }
        return dequeue[front];
    }

    int getRear() const {
        if (isEmpty()) {
            throw "Dequeue is emtpy";
        }
        return dequeue[rear];
    }

    void insertFront(const int& info) {
        if (isFull()) {
            throw "Dequeue is full";
        }
        if (isEmpty()) {
            front = rear = 0;
        } else if (front == 0) {
            front = 5;
        } else {
            front--;
        }
        dequeue[front] = info;
    }

    void insertRear(const int& info) {
        if (isFull()) {
            throw "Dequeue is full";
        }

        if (isEmpty()) {
            front = rear = 0;
        } else if (rear == 5) {
            rear = 0;
        } else {
            rear++;
        }
        dequeue[rear] = info;
    }

    void deleteFront() {
        if (isEmpty()) {
            cout << "Deque is empty\n";
        }
        if (front == rear) {
            front = rear = -1;
        } else if (front == 5) {
            front = 0;
        } else {
            front++;
        }
    }

    void deleteRear() {
        if (isEmpty()) {
            cout << "Deque is empty\n";
        }
        if (front == rear) {
            front = rear = -1;
        } else if (rear == 0) {
            rear = 5;
        } else {
            rear--;
        }
    }
};

int main() {
    
    Dequeue dq;
    dq.insertRear(5);
    dq.insertRear(10);
    cout << "Rear element: " << dq.getRear() << endl;
    dq.deleteRear();
    cout << "Rear element: " << dq.getRear() << endl;
    dq.insertFront(15);
    dq.insertFront(20);
    cout << "Front element: " << dq.getFront() << endl;
    dq.deleteFront();
    cout << "Front element: " << dq.getFront() << endl;

    return 0;
}
