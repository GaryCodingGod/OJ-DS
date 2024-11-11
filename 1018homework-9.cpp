//Complete function displayInorder, displayPreorder and displayPostorder in class BinaryTreeInArray.
//Complete function addElementAsCompleteTree,displayInorder, displayPreorder and displayPostorder in classBinaryTreeInLinkedList.
//Sample output:7  Sample input: 3 1 4 0 5 2 6 
//                               3 1 4 0 5 2 6 
//                               0 1 3 4 2 5 6 
//                               0 1 3 4 2 5 6 
//                               3 4 1 5 6 2 0 
//                               3 4 1 5 6 2 0 
#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

template<class T>
class BinaryTreeInArray {
private:
    T *array;
    int height;
    int numOfElement;

    void resize(int size) {
        T *temp = new T[numOfElement];//暫時儲存當前二元樹中的所有元素
        int j;
        for (j = 0; j < numOfElement; j++)
            temp[j] = array[j];
        delete[] array;
        array = new T[static_cast<int>(pow(2, height + 1)) - 1];//將原來的元素儲存到更大的陣列中
        for (j = 0; j < numOfElement; j++)
            array[j] = temp[j];
        height++;
        delete[] temp;
    }

    void inorder(int index) { //節點在陣列中的位置
        if (index >= numOfElement || array[index] == -1)
            return;
        inorder(2 * index + 1); 
        cout << array[index] << " "; 
        inorder(2 * index + 2); 
    }

    
    void preorder(int index) {
        if (index >= numOfElement || array[index] == -1)//判斷到樹的末端或是節點是空的
            return;
        cout << array[index] << " "; 
        preorder(2 * index + 1); 
        preorder(2 * index + 2); 
    }

    void postorder(int index) {
        if (index >= numOfElement || array[index] == -1)
            return;
        postorder(2 * index + 1); 
        postorder(2 * index + 2); 
        cout << array[index] << " "; 
    }

public:
    BinaryTreeInArray() : array(nullptr), height(0), numOfElement(0) {}

    void addElementAsCompleteTree(T data) {
        int cap = pow(2, height) - 1;//計算當前二元樹所能容納的最大節點數量
        if (numOfElement + 1 > cap)
            resize((cap + 1) * 2 - 1);
        array[numOfElement] = data;
        numOfElement++;
    }

    void displayInorder() {
        inorder(0);
        cout << endl;
    }

    void displayPreorder() {
        preorder(0);
        cout << endl;
    }

    void displayPostorder() {
        postorder(0);
        cout << endl;
    }
};

template<class T>
class BinaryTreeInLinkedList {
private:
    class TreeNode {
    public:
        T data;
        TreeNode *left, *right;

        TreeNode(T d) : data(d), left(nullptr), right(nullptr) {}
    };

    TreeNode *root;//指向樹的根節點
    int numOfElement;

    
    void inorder(TreeNode *node) {
        if (node == nullptr)
            return;
        inorder(node->left); 
        cout << node->data << " "; 
        inorder(node->right); 
    }
    void preorder(TreeNode *node) {
        if (node == nullptr)
            return;
        cout << node->data << " "; 
        preorder(node->left); 
        preorder(node->right); 
    }

    void postorder(TreeNode *node) {
        if (node == nullptr)
            return;
        postorder(node->left); 
        postorder(node->right); 
        cout << node->data << " "; 
    }

public:
    BinaryTreeInLinkedList() : root(nullptr), numOfElement(0) {}

    void addElementAsCompleteTree(T data) {
        TreeNode *newNode = new TreeNode(data);
        if (root == nullptr) {
            root = newNode;
        } else {
            queue<TreeNode *> q;
            q.push(root);//BFS搜尋法，從根節點開始找空位插入

            while (!q.empty()) {
                TreeNode *current = q.front();
                q.pop();

                if (current->left == nullptr) {
                    current->left = newNode;
                    break;
                } else {
                    q.push(current->left);
                }

                if (current->right == nullptr) {
                    current->right = newNode;
                    break;
                } else {
                    q.push(current->right);
                }
            }
        }
        numOfElement++;
    }

    void displayInorder() {
        inorder(root);
        cout << endl;
    }

    void displayPreorder() {
        preorder(root);
        cout << endl;
    }

    void displayPostorder() {
        postorder(root);
        cout << endl;
    }
};

int main() {
    BinaryTreeInArray<int> *b = new BinaryTreeInArray<int>;
    BinaryTreeInLinkedList<int> *tree = new BinaryTreeInLinkedList<int>;
    int j, n;
    cin >> n;

    for (j = 0; j < n; j++) {
        b->addElementAsCompleteTree(j);
        tree->addElementAsCompleteTree(j);
    }

    b->displayInorder();
    tree->displayInorder();

    b->displayPreorder();
    tree->displayPreorder();

    b->displayPostorder();
    tree->displayPostorder();

    return 0;
}