//Suppose we want to extend the Sequence abstract data type with functions indexOfElement(e)and positionOfElement(e)
//which respectively return the index and the position of the (first occurrenceof) element e in the sequence.
//Show how to implement these functions by expressing them in terms ofother functions of the Sequence interface
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
    
    class Iterator {
    private:
        T *seq;           // 指向序列的指標
        int position;     // 當前的環形位置
        int capacity;     // 環形序列的容量
        friend class CircularSequence;
    public:
        Iterator(T *seq, int position, int capacity) 
            : seq(seq), position(position), capacity(capacity) {}

        T &operator*() const {
            return seq[position]; // 取得當前位置的值
        }

        Iterator &operator++() {
            position = (position + 1) % capacity;
            return *this;
        }

        Iterator &operator--() {
            position = (position - 1 + capacity) % capacity;
            return *this;
        }

        bool operator!=(const Iterator &other) const {
            return position != other.position || seq != other.seq;
        }
    };

    
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
            throw overflow_error("The Sequence is full");
        }
        seq[back] = val;
        back = (back + 1) % capacity;
        size++;
    }

    void insertFront(T val) {
        if (size == capacity) {
            throw overflow_error("The Sequence is full");
        }
        front = (front - 1 + capacity) % capacity;
        seq[front] = val;
        size++;
    }

    T erase(int idx) {
        if (idx < 0 || idx >= size) {
            throw runtime_error("Index out of range");
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

    Iterator begin() const {
        return Iterator(seq, front, capacity);
    }

    Iterator end() const {
        return Iterator(seq, back, capacity);
    }

    // 根據索引返回迭代器
    Iterator atIndex(int i) const {
        if (i < 0 || i >= size) {
            throw runtime_error("Index out of range");
        }
        int position = (front + i) % capacity;
        return Iterator(seq, position, capacity);
    }

    // 根據迭代器返回索引
    int indexOf(const Iterator &p) const {
        int iterPos = p.position;
        if (iterPos >= front) {
            return (iterPos - front);
        } else {
            return (capacity - front + iterPos);
        }
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
    sequence.insertBack(10);
    sequence.insertBack(20);
    sequence.insertBack(30);
    sequence.insertFront(5);
    sequence.insertFront(1);

    sequence.display();

    // 測試 atIndex 和 indexOf
    auto iter = sequence.atIndex(2);
    cout << "Value at index 2: " << *iter << endl; 

    int index = sequence.indexOf(iter);
    cout << "Index of iterator: " << index << endl; 

    return 0;
}
