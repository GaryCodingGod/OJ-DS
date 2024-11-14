//Please compete class MinMaxHeap, A Min-Max Heap is a specialized data structure that combines properties of both min-heaps and max-heaps.
//It allows efficient access to both the minimum and maximum elements in constant time.
//This structure is useful in scenarios where we need to frequently retrieve and manage both the smallest and largest values in a set of data.
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

template<typename T>
class MinMaxHeap {
public:
    MinMaxHeap() {} 

    void insert(const T& value);  
    T getMin() const;  
    T getMax() const;  
    void deleteMin(); 
    void deleteMax(); 

private:
    std::vector<T> heap;  //儲存堆中的元素
//FIXME
    void bubbleUp(size_t index);  
    void sinkDown(size_t index);  

    bool isMinLevel(size_t index) const; 
    void bubbleUpMin(size_t index); 
    void bubbleUpMax(size_t index);  

    void sinkDownMin(size_t index);  
    void sinkDownMax(size_t index);  

    size_t findMinDescendant(size_t index) const;  
    size_t findMaxDescendant(size_t index) const;  
};

template<typename T>
void MinMaxHeap<T>::insert(const T& value) {
    heap.push_back(value);  // 新增值到尾端
    bubbleUp(heap.size() - 1);  // 進行浮上操作，確保 MinMaxHeap 結構
}

template<typename T>
T MinMaxHeap<T>::getMin() const {
    if (heap.empty())
        throw std::runtime_error("Heap is empty");
    return heap[0];  // 最小值位於根節點
}

template<typename T>
T MinMaxHeap<T>::getMax() const {
    if (heap.empty())
        throw std::runtime_error("Heap is empty");
    if (heap.size() == 1)
        return heap[0];  // 若堆僅有一個元素，則返回該元素
    else if (heap.size() == 2)
        return heap[1];  // 若堆僅有兩個元素，最大值為第二個節點
    else
        return std::max(heap[1], heap[2]);  // 否則最大值位於第二或第三個節點
}

template<typename T>
void MinMaxHeap<T>::deleteMin() {
    if (heap.empty())
        throw std::runtime_error("Heap is empty");
    heap[0] = heap.back();  // 用最後一個元素替換根節點
    heap.pop_back();  // 移除最後一個元素
    if (!heap.empty())
        sinkDown(0);  // 進行沉下操作，確保 MinMaxHeap 結構
}

template<typename T>
void MinMaxHeap<T>::deleteMax() {
    if (heap.empty())
        throw std::runtime_error("Heap is empty"); 
    size_t maxIndex;
    if (heap.size() == 1) {
        heap.pop_back();  // 若只有一個元素，直接刪除
        return;
    } else {
        if (heap.size() == 2 || heap[1] > heap[2])
            maxIndex = 1;  
        else
            maxIndex = 2; 
        heap[maxIndex] = heap.back();  // 用最後一個元素替換最大值位置
        heap.pop_back();  // 移除最後一個元素
        if (maxIndex < heap.size())
            sinkDown(maxIndex);  // 進行沉下操作
    }
}

template<typename T>
void MinMaxHeap<T>::bubbleUp(size_t index) {
    if (index == 0)
        return; 
    size_t parent = (index - 1) / 2;
    if (isMinLevel(index)) {
        if (heap[index] > heap[parent]) {
            std::swap(heap[index], heap[parent]);  // 若在 Min Level 且值大於父節點，交換並浮上到 Max Level
            bubbleUpMax(parent);
        } else {
            bubbleUpMin(index); 
        }
    } else {
        if (heap[index] < heap[parent]) {
            std::swap(heap[index], heap[parent]); 
            bubbleUpMin(parent);
        } else {
            bubbleUpMax(index);  
        }
    }
}

template<typename T>
void MinMaxHeap<T>::sinkDown(size_t index) {
    if (isMinLevel(index))
        sinkDownMin(index);  // 在 Min Level 執行沉下操作
    else
        sinkDownMax(index);  // 在 Max Level 執行沉下操作
}

template<typename T>
bool MinMaxHeap<T>::isMinLevel(size_t index) const {
    size_t level = 0;
    while (index > 0) {
        index = (index - 1) / 2;  // 計算層級，判斷是否為 Min Level
        level++;
    }
    return (level % 2) == 0;
}

template<typename T>
void MinMaxHeap<T>::bubbleUpMin(size_t index) {
    if (index >= 3) {
        size_t grandparent = (index - 3) / 4;
        if (heap[index] < heap[grandparent]) {
            std::swap(heap[index], heap[grandparent]);  // 與祖父節點交換，繼續浮上
            bubbleUpMin(grandparent);
        }
    }
}

template<typename T>
void MinMaxHeap<T>::bubbleUpMax(size_t index) {
    if (index >= 3) {
        size_t grandparent = (index - 3) / 4;
        if (heap[index] > heap[grandparent]) {
            std::swap(heap[index], heap[grandparent]);  // 與祖父節點交換，繼續浮上
            bubbleUpMax(grandparent);
        }
    }
}

template<typename T>
void MinMaxHeap<T>::sinkDownMin(size_t index) {
    size_t m = findMinDescendant(index);
    if (m == -1)
        return;
    if (heap[m] < heap[index]) {
        std::swap(heap[m], heap[index]); 
        if (m >= 3 && heap[m] > heap[(m - 1) / 2])
            std::swap(heap[m], heap[(m - 1) / 2]);
        sinkDownMin(m);
    }
}

template<typename T>
void MinMaxHeap<T>::sinkDownMax(size_t index) {
    size_t m = findMaxDescendant(index);
    if (m == -1)
        return;
    if (heap[m] > heap[index]) {
        std::swap(heap[m], heap[index]);
        if (m >= 3 && heap[m] < heap[(m - 1) / 2])
            std::swap(heap[m], heap[(m - 1) / 2]);
        sinkDownMax(m);
    }
}

template<typename T>
size_t MinMaxHeap<T>::findMinDescendant(size_t index) const {
    std::vector<size_t> candidates;
    size_t firstChild = 2 * index + 1;
    size_t lastChild = std::min(heap.size() - 1, firstChild + 1);
    for (size_t i = firstChild; i <= lastChild; ++i) {
        candidates.push_back(i);
        size_t firstGrandChild = 2 * i + 1;
        size_t lastGrandChild = std::min(heap.size() - 1, firstGrandChild + 1);
        for (size_t j = firstGrandChild; j <= lastGrandChild; ++j) {
            candidates.push_back(j);
        }
    }
    if (candidates.empty()) return -1;
    size_t minIndex = candidates[0];
    for (size_t i = 1; i < candidates.size(); ++i) {
        if (heap[candidates[i]] < heap[minIndex]) {
            minIndex = candidates[i];
        }
    }
    return minIndex;
}

template<typename T>
size_t MinMaxHeap<T>::findMaxDescendant(size_t index) const {
    std::vector<size_t> candidates;
    size_t firstChild = 2 * index + 1;
    size_t lastChild = std::min(heap.size() - 1, firstChild + 1);
    for (size_t i = firstChild; i <= lastChild; ++i) {
        candidates.push_back(i);
        size_t firstGrandChild = 2 * i + 1;
        size_t lastGrandChild = std::min(heap.size() - 1, firstGrandChild + 1);
        for (size_t j = firstGrandChild; j <= lastGrandChild; ++j) {
            candidates.push_back(j);
        }
    }
    if (candidates.empty()) return -1;
    size_t maxIndex = candidates[0];
    for (size_t i = 1; i < candidates.size(); ++i) {
        if (heap[candidates[i]] > heap[maxIndex]) {
            maxIndex = candidates[i];
        }
    }
    return maxIndex;
}

int main() {
    MinMaxHeap<int> mmHeap;
    mmHeap.insert(10);
    mmHeap.insert(5);
    mmHeap.insert(20);
    mmHeap.insert(15);
    mmHeap.insert(2);
    mmHeap.insert(30);

    std::cout << "Min: " << mmHeap.getMin() << std::endl;
    std::cout << "Max: " << mmHeap.getMax() << std::endl;

    mmHeap.deleteMin();
    std::cout << "Min after deleteMin: " << mmHeap.getMin() << std::endl;

    mmHeap.deleteMax();
    std::cout << "Max after deleteMax: " << mmHeap.getMax() << std::endl;

    return 0;
}
