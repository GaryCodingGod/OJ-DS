//In computer science, an AVL tree is a self-balancing binary search tree.
//Please complete the AVLTree class in template.
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <ctime>
using namespace std;

/*
AVL tree
1. 任何節點的兩棵子樹的高度差絕對值不超過 1
2. 透過旋轉操作恢復平衡 -- 單向旋轉、雙向旋轉
*/

// Node 類別模板
template<class T>
class Node
{
public:
    Node() {
        data = new T;
    }
    Node(T d) {
        data = new T;
        (*data) = d;
    }
    Node &operator=(T d) {
        (*data) = d;
        return *this;
    }
    friend std::ostream &operator<<(std::ostream &out, Node n) {
        out << *(n.data);
        return out;
    }
    friend std::ostream &operator<<(std::ostream &out, Node *n) {
        out << *(n->data);
        return out;
    }
    void setData(T d) {
        *data = d;
    }
    T &getData() const {
        return *data;
    }
protected:
    T *data;
};

// BinaryTreeNode 類別模板
template<class T>
class BinaryTreeNode : public Node<T>
{
public:
    BinaryTreeNode() : Node<T>() {
        left = NULL;
        right = NULL;
        height = 1;
    }
    BinaryTreeNode(T d) : Node<T>(d) {
        left = NULL;
        right = NULL;
        height = 1;
    }
    BinaryTreeNode(BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>() {
        left = l;
        right = r;
        height = 1;
    }
    BinaryTreeNode(T d, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>(d) {
        left = l;
        right = r;
        height = 1;
    }
    void setLeft(BinaryTreeNode<T> *l) {
        left = l;
    }
    void setRight(BinaryTreeNode<T> *r) {
        right = r;
    }
    BinaryTreeNode<T> *&getLeft() {
        return left;
    }
    BinaryTreeNode<T> *&getRight() {
        return right;
    }
    int getHeight() const {
        return height;
    }
    void setHeight(int h) {
        height = h;
    }
    bool operator>(BinaryTreeNode<T> n) {
        return *(this->data) > *(n.data);
    }
    bool operator==(BinaryTreeNode<T> n) {
        return *(this->data) == *(n.data);
    }
private:
    BinaryTreeNode<T> *left, *right;
    int height;
};

// AVLTree 類別模板
template<class T>
class AVLTree
{
private:
    BinaryTreeNode<T> *root;

    // 高度是以葉節點為 0 不斷地向上計算
    int height(BinaryTreeNode<T> *node) {
        return node ? node->getHeight() : 0;
    }

    int getBalance(BinaryTreeNode<T> *node) { // 回傳左子樹 - 右子樹之間的高度差
        return node ? height(node->getLeft()) - height(node->getRight()) : 0;
    }
    // 將左子樹的高度縮短
    BinaryTreeNode<T>* rotateRight(BinaryTreeNode<T> *y) {
        BinaryTreeNode<T> *x = y->getLeft();
        BinaryTreeNode<T> *T2 = x->getRight();

        x->setRight(y);
        y->setLeft(T2);

        y->setHeight(max(height(y->getLeft()), height(y->getRight())) + 1);
        x->setHeight(max(height(x->getLeft()), height(x->getRight())) + 1);

        return x;
    }
    // 將右子樹的高度縮短
    BinaryTreeNode<T>* rotateLeft(BinaryTreeNode<T> *x) {
        BinaryTreeNode<T> *y = x->getRight();
        BinaryTreeNode<T> *T2 = y->getLeft();

        y->setLeft(x);
        x->setRight(T2);

        x->setHeight(max(height(x->getLeft()), height(x->getRight())) + 1);
        y->setHeight(max(height(y->getLeft()), height(y->getRight())) + 1);

        return y;
    }

    BinaryTreeNode<T>* insert(BinaryTreeNode<T> *node, T key) {
        if (!node) {
            return new BinaryTreeNode<T>(key);
        }

        // 插入規則與二元樹一樣：左小右大
        if (key < node->getData()) {
            node->setLeft(insert(node->getLeft(), key));
        } else if (key > node->getData()) {
            node->setRight(insert(node->getRight(), key));
        } else {
            return node;
        }

        node->setHeight(1 + max(height(node->getLeft()), height(node->getRight()))); // 更新節點高度

        int balance = getBalance(node);

        // 進行單右旋
        if (balance > 1 && key < node->getLeft()->getData()) { // 高度差 > 1 且插入在左子樹的左側
            return rotateRight(node);
        }
        // 進行單左旋
        if (balance < -1 && key > node->getRight()->getData()) { // 高度差 < -1 且插入在右子樹的右側
            return rotateLeft(node);
        }

        // 左右雙旋：先對對左子節點進行左旋，再對根節點進行右旋
        if (balance > 1 && key > node->getLeft()->getData()) { // 高度差 > 1 且插入在左子樹的右側
            node->setLeft(rotateLeft(node->getLeft()));
            return rotateRight(node);
        }
        // 右左雙旋：先對右子節點進行右旋，再對根節點進行左旋
        if (balance < -1 && key < node->getRight()->getData()) { // 高度差 < -1 且插入在右子數的左側
            node->setRight(rotateRight(node->getRight()));
            return rotateLeft(node);
        }

        return node;
    }

    // 左節點 -> 根節點 -> 右節點
    void inorder(BinaryTreeNode<T> *cur, int n) {
        if (cur == NULL)
            return;
        inorder(cur->getRight(), n + 1);
        for (int j = 0; j < n; j++)
            cout << "  ";
        cout << cur << endl;
        inorder(cur->getLeft(), n + 1);
    }

public:
    AVLTree() : root(NULL) {}

    void insert(T key) {
        root = insert(root, key);
    }

    void inorder() {
        inorder(root, 0);
    }
};

int main() {
    AVLTree<int> *tree = new AVLTree<int>();
    srand(0);
    for (int j = 0; j < 20; j++) {
        tree->insert(rand() % 100);
        tree->inorder();
        cout << "--------------------" << endl;
    }
    delete tree;
    return 0;
};