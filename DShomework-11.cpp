#include <iostream>

using namespace std;

template <class T>
class CircularSequence {
private:
    T *seq;
    int capacity;
    int size;
    int front;
    int back;

public:
    CircularSequence(int cap) : capacity(cap), size(0), front(0), back(0) {
        seq = new T[capacity];
    }

    ~CircularSequence() {
        delete[] seq;
    }

    int sizeOfSequence() const {
        return size;
    }

    bool empty() const {
        return size == 0;
    }

    void insertBack(T val) {
        if (size == capacity) {
            throw overflow_error("Cannot insert, the sequence is full");
        }
        seq[back] = val;
        back = (back + 1) % capacity;
        size++;
    }

    void insertFront(T val) {
        if (size == capacity) {
            throw overflow_error("Cannot insert, the sequence is full");
        }
        front = (front - 1 + capacity) % capacity;
        seq[front] = val;
        size++;
    }

    void insert(int idx, T val) {
        if (idx < 0 || idx > size) {
            throw runtime_error("Index out of range in insert function");
        }

        if (idx == 0) {
            insertFront(val);
            return;
        }

        if (idx == size) {
            insertBack(val);
            return;
        }

        int insertPos = (front + idx) % capacity;
        for (int i = size; i > idx; i--) {
            int cur = (front + i) % capacity;
            int pre = (front + i - 1) % capacity;
            seq[cur] = seq[pre];
        }
        seq[insertPos] = val;
        back = (back + 1) % capacity;
        size++;
    }

    T erase(int idx) {
        if (idx < 0 || idx >= size) {
            throw runtime_error("Index out of range in erase function");
        }

        int erasePos = (front + idx) % capacity;
        T erasedValue = seq[erasePos];

        for (int i = idx; i < size - 1; i++) {
            int curPos = (front + i) % capacity;
            int nextPos = (front + i + 1) % capacity;
            seq[curPos] = seq[nextPos];
        }

        back = (back - 1 + capacity) % capacity;
        size--;

        return erasedValue;
    }

    T peekFront() const {
        if (empty()) {
            throw runtime_error("Sequence is empty");
        }
        return seq[front];
    }

    T peekBack() const {
        if (empty()) {
            throw runtime_error("Sequence is empty");
        }
        return seq[(back - 1 + capacity) % capacity];
    }

    void clear() {
        size = 0;
        front = 0;
        back = 0;
    }

    void display() const {
        for (int i = 0; i < size; i++) {
            cout << seq[(front + i) % capacity] << " ";
        }
        cout << endl;
    }
};

int main() {
    CircularSequence<int> sequence(5);

    // 測試插入操作
    sequence.insertBack(10);
    sequence.insertBack(20);
    sequence.insertBack(30);
    sequence.insertFront(5);
    sequence.display(); // 5 10 20 30

    cout << "Erased value: " << sequence.erase(1) << endl;
    sequence.display(); // 5 20 30

    // 測試邊界情況
    sequence.insertBack(40);
    sequence.insertBack(50);
    try {
        sequence.insertBack(60); // 超過容量
    } catch (const overflow_error &e) {
        cout << e.what() << endl;
    }
    sequence.display(); // 5 20 30 40 50

    // 測試刪除首尾
    cout << "Erased value: " << sequence.erase(0) << endl; // 刪除第一個元素
    sequence.display(); // 20 30 40 50
    cout << "Erased value: " << sequence.erase(sequence.sizeOfSequence() - 1) << endl; // 刪除最後一個元素
    sequence.display(); // 20 30 40

    // 測試清空
    sequence.clear();
    sequence.display();

    return 0;
}