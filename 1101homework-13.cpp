//A binary heap is a heap data structure that takes the form of a binary tree.
//A binary heap is defined as a binary tree with two additional constraints:
//1. Shape property: a binary heap is a complete binary tree; that is, all levels of the tree, except possibly the last one (deepest) are fully filled, 
//and if the last level of the tree is not complete, the nodes of that level are filled from left to right.
//2. Heap property: the key stored in each node is either greater than or equal to (≥) or less than or equal to (≤) the keys in the node's children, according to some total order.
#include <vector>
#include <stdexcept>
#include <iostream>

using namespace std;

template<class T>
class MaxHeap {
public:
    MaxHeap() {} 

    void insert(T value) {
        heap.push_back(value); 
        int index = heap.size() - 1; //index是插入新元素的索引(堆疊最後一個位置)
        
       
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index] <= heap[parentIndex]) break; 
            swap(heap[index], heap[parentIndex]); 
            index = parentIndex; 
        }
    }

    // 移除函式：移除並返回堆的最大值
    T extract() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        
        T maxValue = heap[0];        
        heap[0] = heap.back();       
        heap.pop_back();             
        
        int index = 0;
        int size = heap.size();

        while (true) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int largest = index;

            if (leftChild < size && heap[leftChild] > heap[largest]) { //先確保左子節點在範圍內，再看左子節點的值是否大於當前節點的值
                largest = leftChild;
            }
            if (rightChild < size && heap[rightChild] > heap[largest]) {
                largest = rightChild;
            }
            if (largest == index) break;
            swap(heap[index], heap[largest]); 
            index = largest; 
        }

        return maxValue; 
    }

    int count() {
        return heap.size();
    }

private:
    vector<T> heap; 
};
