//I create a class WeightedGraph for you but leaves the method minimumSpanningTree blank, please finish it.
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <limits>

using namespace std;

template <class T>
class Node {
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

template <class T>
class ListNode : public Node<T> { // 繼承自 Node<T>，用於實作雙向鏈結（Doubly Linked List）
public:
    ListNode() : Node<T>() {
        prev = NULL;
        next = NULL;
    }
    ListNode(T d) : Node<T>(d) {
        prev = NULL;
        next = NULL;
    }
    ListNode(ListNode *p, ListNode *n) : Node<T>() {
        prev = p;
        next = n;
    }
    ListNode(T d, ListNode *p, ListNode *n) : Node<T>(d) {
        prev = p;
        next = n;
    }
    ListNode *getNext() const {
        return next;
    }
    ListNode *getPrev() const {
        return prev;
    }
    void setNext(ListNode *n) {
        next = n;
    }
    void setPrev(ListNode *p) {
        prev = p;
    }
    ListNode &operator=(T d) {
        this->setData(d);
        return *this;
    }

private:
    ListNode *prev, *next;
};

template <class T>
class LinkList { // 儲存圖的頂點或邊
public:
    LinkList() {
        head = NULL;
        tail = NULL;
    }
    void addFromHead(T d) {
        ListNode<T> *node = new ListNode<T>(d);
        if (head != NULL) {
            head->setPrev(node);
        }
        node->setNext(head);
        head = node;
        if (tail == NULL)
            tail = node;
    }
    void addFromTail(T d) {
        ListNode<T> *node = new ListNode<T>(d);
        if (tail != NULL) {
            tail->setNext(node);
        }
        node->setPrev(tail);
        tail = node;
        if (head == NULL)
            head = node;
    }
    void addAfter(ListNode<T> *at, T d) {
        if (!exist(at))
            return;
        ListNode<T> *node = new ListNode<T>(d);
        if (at->getNext() != NULL)
            at->getNext()->setPrev(node);
        node->setNext(at->getNext());
        at->setNext(node);
        node->setPrev(at);
        if (node->getNext() == NULL)
            tail = node;
    }
    ListNode<T> *removeFromHead() {
        ListNode<T> *n = head;
        if (head != NULL) {
            head = head->getNext();
            if (head != NULL)
                head->setPrev(NULL);
            else
                tail = NULL;
            n->setNext(NULL);
        }
        return n;
    }
    ListNode<T> *removeFromTail() {
        ListNode<T> *n = tail;
        if (tail != NULL) {
            tail = tail->getPrev();
            if (tail != NULL)
                tail->setNext(NULL);
            else
                head = NULL;
            n->setPrev(NULL);
        }
        return n;
    }
    ListNode<T> *remove(ListNode<T> *n) {
        if (!exist(n))
            return NULL;
        if (n == head)
            return removeFromHead();
        if (n == tail)
            return removeFromTail();
        n->getPrev()->setNext(n->getNext());
        n->getNext()->setPrev(n->getPrev());
        n->setNext(NULL);
        n->setPrev(NULL);
        return n;
    }
    ListNode<T> *exist(T d) {
        ListNode<T> *j = head;
        while (j != NULL) {
            if (j->getData() == d)
                return j;
            j = j->getNext();
        }
        return NULL;
    }
    bool exist(ListNode<T> *n) {
        ListNode<T> *j = head;
        while (j != NULL) {
            if (j == n)
                return true;
            j = j->getNext();
        }
        return false;
    }
    ListNode<T> &operator[](int i) {
        ListNode<T> *j = head;
        int k;
        for (k = 0; k < i && j != NULL; k++)
            j = j->getNext();
        if (j == NULL)
            throw std::invalid_argument("index does not exist.");
        return *j;
    }
    void print() const {
        ListNode<T> *j = head;
        while (j != NULL) {
            std::cout << (*j) << " ";
            j = j->getNext();
        }
        std::cout << std::endl;
    }

protected:
    ListNode<T> *head, *tail;
};

template <class V, class E>
class WeightedGraphEdge;

template <class V, class E>
class WeightedGraphVertex : public Node<V> {
public:
    WeightedGraphVertex() : Node<V>() {
        list = new LinkList<WeightedGraphEdge<V, E> *>();
    }
    WeightedGraphVertex(V d) : Node<V>(d) {
        list = new LinkList<WeightedGraphEdge<V, E> *>();
    }
    void addEdge(WeightedGraphEdge<V, E> *edge) {
        list->addFromTail(edge);
    }
    void remove(WeightedGraphEdge<V, E> *node) { //暫不實作
    }
    ListNode<WeightedGraphEdge<V, E> *> *operator[](int n) {
        try {
            return (&(*list)[n]);
        } catch (std::invalid_argument e) {
            return NULL;
        }
    }

private:
    LinkList<WeightedGraphEdge<V, E> *> *list;
};

template <class V, class E>
class WeightedGraphEdge : public Node<E> {
public:
    WeightedGraphEdge() : Node<E>() {
        end[0] = NULL;
        end[1] = NULL;
    }
    WeightedGraphEdge(E d) : Node<E>(d) {
        end[0] = NULL;
        end[1] = NULL;
    }
    WeightedGraphEdge(E d, WeightedGraphVertex<V, E> *v1, WeightedGraphVertex<V, E> *v2) : Node<E>(d) {
        end[0] = v1;
        end[1] = v2;
    }
    WeightedGraphVertex<V, E> *&getAnotherEnd(WeightedGraphVertex<V, E> *v) {
        if (v != end[0])
            return end[0];
        return end[1];
    }
    WeightedGraphVertex<V, E> *getFirstEnd() const { //取得邊的第一個端點
        return end[0];
    }
    WeightedGraphVertex<V, E> *getSecondEnd() const {//取得邊的第二個端點
        return end[1];
    }

private:
    WeightedGraphVertex<V, E> *end[2];
};

template <class V, class E>
class WeightedGraph {
public:
    WeightedGraph() {
        vertex = new LinkList<WeightedGraphVertex<V, E> *>();//儲存圖中的所有節點
        edge = new LinkList<WeightedGraphEdge<V, E> *>();// 儲存圖中的所有邊
        vertexCount = 0;
        edgeCount = 0;
    }

    WeightedGraphVertex<V, E> *operator[](int n) { //取出對應索引的節點，並回傳該節點的資料
        try {
            return (*vertex)[n].getData();
        } catch (std::invalid_argument e) {
            return NULL;
        }
    }
    void addLink(WeightedGraphVertex<V, E> *v1, WeightedGraphVertex<V, E> *v2, E w) {//建立一條新的邊，並新增至 edge 容器中
        WeightedGraphEdge<V, E> *newEdge = new WeightedGraphEdge<V, E>(w, v1, v2);
        v1->addEdge(newEdge);
        if (v1 != v2)
            v2->addEdge(newEdge);
        edge->addFromTail(newEdge);
        edgeCount++;
    }
    WeightedGraphVertex<V, E> *addVertex(V d) {//建立一個新的節點，並新增至 vertex 當中
        WeightedGraphVertex<V, E> *v = new WeightedGraphVertex<V, E>(d);
        vertex->addFromTail(v);
        vertexCount++;
        return v;
    }
    void adjList() { //輸出整個圖的鄰接表
        ListNode<WeightedGraphVertex<V, E> *> *cur = &(*vertex)[0];
        while (cur != NULL) {
            WeightedGraphVertex<V, E> *temp = cur->getData();
            std::cout << temp << ": ";
            ListNode<WeightedGraphEdge<V, E> *> *e = (*temp)[0];
            while (e != NULL) {
                std::cout << e->getData()->getAnotherEnd(temp) << "(" << e->getData() << ") ";
                e = e->getNext();
            }
            std::cout << std::endl;
            cur = cur->getNext();
        }
    }

    WeightedGraph *minimumSpanningTree(WeightedGraphVertex<V, E> *root) {
        if (root == NULL) return NULL;

        WeightedGraph *mst = new WeightedGraph(); //新建一個圖，用來存儲最小生成樹
        LinkList<WeightedGraphVertex<V, E> *> visited;
        LinkList<WeightedGraphEdge<V, E> *> candidates;

        mst->addVertex(root->getData());
        visited.addFromTail(root);

        auto addEdges = [&candidates](WeightedGraphVertex<V, E> *v) { //將起始節點的相鄰邊加入候選清單
            ListNode<WeightedGraphEdge<V, E> *> *edgeNode = (*v)[0];
            while (edgeNode != NULL) {
                if (!candidates.exist(edgeNode->getData())) { //確保邊不重複加入
                    candidates.addFromTail(edgeNode->getData());
                }
                edgeNode = edgeNode->getNext();
            }
        };

        addEdges(root);

        while (candidates.removeFromHead() != NULL) {
            WeightedGraphEdge<V, E> *minEdge = NULL;
            E minWeight = std::numeric_limits<E>::max();

            //從候選邊中選擇最小的邊
            ListNode<WeightedGraphEdge<V, E> *> *candidateNode = candidates.exist((WeightedGraphEdge<V, E> *)NULL); //儲存尚未訪問的邊
            while (candidateNode != NULL) {
                WeightedGraphEdge<V, E> *currentEdge = candidateNode->getData();
                WeightedGraphVertex<V, E> *v1 = currentEdge->getFirstEnd();
                WeightedGraphVertex<V, E> *v2 = currentEdge->getSecondEnd();
                WeightedGraphVertex<V, E> *unvisitedVertex = NULL;

                if (visited.exist(v1) == NULL && visited.exist(v2) != NULL) //判斷此邊是否連接一個已訪問節點和一個未訪問節點，其權重小於當前最小權重
                    unvisitedVertex = v1;
                else if (visited.exist(v2) == NULL && visited.exist(v1) != NULL)
                    unvisitedVertex = v2;

                if (unvisitedVertex != NULL && currentEdge->getData() < minWeight) {
                    minWeight = currentEdge->getData();
                    minEdge = currentEdge;
                }

                candidateNode = candidateNode->getNext();
            }

            if (minEdge == NULL) break;

            // 根據最小邊的兩個端點，決定要加入最小生成樹的「新頂點」
            // minEdge->getFirstEnd() == root -> 判斷這條邊的第一端點是否已經在最小生成樹中
            WeightedGraphVertex<V, E> *newVertex = mst->addVertex(minEdge->getFirstEnd() == root
                                                                      ? minEdge->getSecondEnd()->getData()
                                                                      : minEdge->getFirstEnd()->getData());

            mst->addLink(root, newVertex, minEdge->getData());
            visited.addFromTail(newVertex);
            addEdges(newVertex);
        }

        return mst;
    }

private:
    LinkList<WeightedGraphVertex<V, E> *> *vertex;
    LinkList<WeightedGraphEdge<V, E> *> *edge;
    int vertexCount, edgeCount;
};

int main() {
    WeightedGraph<char, int> *g = new WeightedGraph<char, int>();
    WeightedGraph<char, int> *tree;
    int j, k, i, l;
    srand(time(NULL));
    for (j = 0; j < 5; j++) {
        g->addVertex(j + 'a');
    }
    for (j = 0; j < 5; j++) {
        k = rand() % 5;
        i = rand() % 5;
        l = rand() % 100;
        g->addLink((*g)[k], (*g)[i], l);
    }
    g->adjList();
    tree = g->minimumSpanningTree((*g)[0]);
    tree->adjList();
    return 0;
}

