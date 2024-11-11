//Complete function displayPreorder and displayPostorder in classTreeInLinkedList.
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class TreeInLinkedList
{
private:
    class TreeNode
    {
    public:
        TreeNode(T d, TreeNode *p) : data(d), parent(p) {}
        TreeNode *parent;
        T data;
    };
    vector<TreeNode *> *nodeList;
/*
vector 儲存的優缺點
優點：
1. 可以提供動態大小的調整
2. 存取速度快

缺點：
1. 當樹的結構不規則或深度不確定時，會浪費部分的記憶體空間
2. 無法方便地處理樹的動態變化
*/
public:
    TreeInLinkedList()
    {
        nodeList = new vector<TreeNode *>(); // 使 nodeList 指標指向一個新的、空的 vector，且當中儲存能夠指向 TreeNode 物件的指標
    }
    void addElement(T data)
    {
        int j, k = nodeList->size();
        if (data == 1)
        {
            nodeList->clear();
            nodeList = new vector<TreeNode *>();
            TreeNode *newNode = new TreeNode(data, nullptr);
            nodeList->push_back(newNode);
        } 
        else
        {
            for (j = 0; j < k; j++)
            {
                if (data % (*nodeList)[j]->data == 0) // 從現有的節點中尋找能整除 data 的節點，並將其設為父節點
                {
                    TreeNode *newNode = new TreeNode(data, (*nodeList)[j]);
                    nodeList->push_back(newNode);
                }
            }
        }
    }
    void displayPreorder()
    {
        if (!nodeList->empty()) // 判斷 vector 是否為空
        {
            displayPreorderHelper((*nodeList)[0]); // 將根節點傳入
        }
    }
    void displayPostorder()
    {
        if (!nodeList->empty())
        {
            displayPostorderHelper((*nodeList)[0]);
        }
    }
    void displayPreorderHelper(TreeNode *node)
    {
        if (!node) return;
        cout << node->data << " ";
        for (auto it = nodeList->begin(); it != nodeList->end(); it++) // auto 相當於 vector<TreeNode *>::iterator
        {   
            TreeNode *child = *it; 
            if (child->parent == node) 
            {
                displayPreorderHelper(child);
            }
        }
    }

    // 先輸出子節點，再輸出父節點
    void displayPostorderHelper(TreeNode *node)
    {
        if (!node) return;
        for (auto it = nodeList->begin(); it != nodeList->end(); it++)
        {
            TreeNode *child = *it;
            if (child->parent == node)
            {
                displayPostorderHelper(child);
            }
        }
        cout << node->data << " ";
    }
};

int main()
{
    TreeInLinkedList<int> *tree = new TreeInLinkedList<int>();
    int j;
    int n;
    cin >> n;
    for (j = 1; j <= n; j++)
        tree->addElement(j);
    tree->displayPreorder();
    cout << endl;
    tree->displayPostorder();
    cout << endl;
}