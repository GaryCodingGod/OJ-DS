// A Threaded Tree is a type of binary tree designed to optimize tree traversal, particularly for in-order traversal 
// without using additional data structures like stacks or recursion. It achieves this by utilizing otherwise null pointers in a binary tree to store threads 
// which are pointers to the node's in-order predecessor or successor**
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

template<class T>
class TreeNode {
public:
    T *data;
    TreeNode *left, *right;
    bool isThread; // 標記右指標是否為Thread（true 表示是Thread）

    TreeNode(T d) : right(nullptr), left(nullptr), isThread(false) {
        data = new T {d};
    }
    TreeNode() : data(nullptr), right(nullptr), left(nullptr), isThread(false) {}
};

template<class T>
class Tree {
private:
    TreeNode<T> *root;

    // 建立Thread結構：將每個節點的空右指標設為中序遍歷的後繼節點
    void createThread(TreeNode<T> *node, TreeNode<T> *&prev) {
        if (!node || !node->data) return; 
        createThread(node->left, prev);

        // 線索處理：如果前一個節點的右指標為空，將其設為當前節點
        if (prev && prev->right == nullptr) {
            prev->right = node;
            prev->isThread = true;
        }
            prev = node;

        if (!node->isThread)
            createThread(node->right, prev);
    }

public:
    Tree() : root(nullptr) {} 

    Tree<T> *insert(T d) {
        if (!root) { 
            root = new TreeNode<T>(d);
            return this;
        }

        TreeNode<T> *current = root; // 從根節點開始插入
        while (true) {
            if (*current->data > d) {
                if (!current->left) { 
                    current->left = new TreeNode<T>(d);
                    return this;
                }
                current = current->left;
            } else {
                if (!current->right || current->isThread) { 
                    current->right = new TreeNode<T>(d);
                    current->isThread = false; 
                    return this;
                }
                current = current->right; 
            }
        }
    }

    // 建立線索二元樹 
    void CreateThread() {
        TreeNode<T> *prev = nullptr;
        createThread(root, prev); 
    }

    // 中序遍歷並輸出節點資料
    void print() {
        TreeNode<T> *current = root;

        // 找到中序遍歷的第一個節點（最左）
        while (current && current->left) {
            current = current->left;
        }

        // 使用線索進行中序遍歷
        while (current) {
            cout << *(current->data) << " ";
            if (current->isThread) {
                current = current->right;
            } else {
                current = current->right;
                while (current && current->left) {
                    current = current->left;
                }
            }
        }
    }
};
int main() {
    int j;
    Tree<int> tree;
    srand(time(nullptr)); 

    for (j = 0; j < 10; j++)
        tree.insert(rand() % 100);
    tree.CreateThread(); // CreateThread
    tree.print();

    return 0;
}