#include <iostream>
#include <stdexcept>

using namespace std;

class CircularSequence {
private:
    int* array;
    int capacity;
    int size;
    int front;
    int back;

    int circularIndex(int index) const {
        return (front + index) % capacity;
    }

public:
    CircularSequence(int cap) : capacity(cap), size(0), front(0), back(0) {
        array = new int[capacity];
    }

    ~CircularSequence() {
        delete[] array;
    }

    void insertFront(int value) {
        if (size == capacity) {
            throw overflow_error("Sequence is full");
        }
        front = (front - 1 + capacity) % capacity;
        array[front] = value;
        size++;
    }

    void insertBack(int value) {
        if (size == capacity) {
            throw overflow_error("Sequence is full");
        }
        array[back] = value;
        back = (back + 1) % capacity;
        size++;
    }

    int removeFront() {
        if (size == 0) {
            throw underflow_error("Sequence is empty");
        }
        int value = array[front];
        front = (front + 1) % capacity;
        size--;
        return value;
    }

    int removeBack() {
        if (size == 0) {
            throw underflow_error("Sequence is empty");
        }
        back = (back - 1 + capacity) % capacity;
        int value = array[back];
        size--;
        return value;
    }

    int atIndex(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        return array[circularIndex(index)];
    }

    int indexOf(int value) const {
        for (int i = 0; i < size; i++) {
            if (array[circularIndex(i)] == value) {
                return i;
            }
        }
        return -1; 
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            cout << atIndex(i) << " ";
        }
        cout << endl;
    }

    // Iterator class
    class Iterator {
    private:
        const CircularSequence& sequence;
        int current;
        int count;

    public:
        Iterator(const CircularSequence& seq) : sequence(seq), current(seq.front), count(0) {}

        bool hasNext() const {
            return count < sequence.size;
        }

        int next() {
            if (!hasNext()) {
                throw out_of_range("No more elements in the sequence");
            }
            int value = sequence.array[current];
            current = (current + 1) % sequence.capacity;
            count++;
            return value;
        }
    };

    Iterator iterator() const {
        return Iterator(*this);
    }
};

int main() {
    CircularSequence seq(5); // Capacity of 5

    seq.insertBack(10);
    seq.insertBack(20);
    seq.insertBack(30);
    seq.insertFront(5);
    seq.print(); // Output: 5 10 20 30

    cout << "Element at index 2: " << seq.atIndex(2) << endl; // Output: 20
    cout << "Index of element 10: " << seq.indexOf(10) << endl; // Output: 1

    seq.removeFront();
    seq.print(); // Output: 10 20 30

    seq.removeBack();
    seq.print(); // Output: 10 20

    auto it = seq.iterator();
    while (it.hasNext()) {
        cout << it.next() << " ";
    }
    cout << endl; // Output: 10 20

    return 0;
}
