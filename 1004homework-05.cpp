//Please finish the three sorting function in template, bubble sort, selection sort and insertion sort.
//When swap, you should swap the value in each node rathen then node itself.
//You will get 80 point if you finish one of three, 90 point if two and 100 point for all three.
#include <iostream>
#include <cstdlib>
#include <ctime>

#define SIZE 100

using namespace std;

class Node
{
public:
 Node()
 {
  next = NULL;
  pre = NULL;
 }
 Node(int n)
 {
  data = n;
  next = NULL;
  pre = NULL;
 }
 int getData() { return data; }
 Node *getNext() { return next; }
 Node *getPre() { return pre; }
 void setData(int d) { data = d; }
 void setNext(Node *n) { next = n; }
 void setPre(Node *p) { pre = p; }
private:
 int data;
 Node *next, *pre; 
};

class List
{
public:
 List() { list = NULL; }
 List(int n) { generate(n); }
 
 void generate(int n)
 {
  int j;
  list = NULL;
  for(j = 0;j < n;j ++)
   generate();
 }
 
 void generate()
 {
  Node *buf = new Node(rand());
  buf->setNext(list);
  if(list != NULL)
   list->setPre(buf);
  list = buf;
 }
 
 void bubbleSort()
 {
  if (list == NULL) return;

  bool swapped; //是否進行了交換
  Node *cur;

  do {

   swapped = false;
   cur = list;

   while (cur->getNext() != NULL) {

    if (cur->getData() > cur->getNext()->getData()) {
    //交換相鄰節點的數據
     int temp = cur->getData();
     cur->setData(cur->getNext()->getData());
     cur->getNext()->setData(temp);

     swapped = true;
    }
    cur = cur->getNext();
   }
  } while (swapped);
 } 
 
 void selectionSort()
 {
  if (list == NULL) return;

  Node *min; //儲存最小值的節點
  Node *cur = list;

  while (cur->getNext() != NULL) {

   min = cur;
   Node *nxt = cur->getNext();

   while (nxt != NULL) {
    if (min->getData() > nxt->getData()) {
     min = nxt; //找到比當前最小值更小的節點
    }
    nxt = nxt->getNext();
   }
    //交換當前節點和找到的最小值節點的數據 
   int temp = cur->getData();
   cur->setData(min->getData());
   min->setData(temp);

   cur = cur->getNext(); 
  }
 }
 
 void insertionSort()
 {
  if (list == NULL) return;

  Node *cur = list->getNext();

  while (cur != NULL) {

   Node* insert_num = cur; //當前要插入的節點
   Node *pre = cur->getPre();//已排序部分的最後一個節點
    
   // 從後往前比較，找到正確的插入位置
   while (pre != NULL && insert_num->getData() < pre->getData()) {
    pre->getNext()->setData(pre->getData());
    pre = pre->getPre();
   }
    //如果已到頭，或插入點已經找到
   if (pre == NULL) {
             list->setData(insert_num->getData()); 
         } else {
             pre->getNext()->setData(insert_num->getData()); 
         }

   cur = cur->getNext();
  }
 } 
 
 void print()
 {
  Node *cur = list;
  while(cur != NULL)
  {
   cout<<cur->getData()<<" ";
   cur = cur->getNext();
  }
  cout<<endl;
 }
private:
 Node *list;
};

int main()
{
 srand(time(NULL));
 List *l = new List(10);
 l->print();
 l->bubbleSort();
 l->print();
 
 l = new List(10);
 l->print();
 l->insertionSort();
 l->print();
 
 l = new List(10);
 l->print();
 l->selectionSort();
 l->print();
}