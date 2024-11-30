//Please finish two function push and pop
//Function push will push the data into stack and return 1 if success, return -1 if not.
//Function pop will pop the top data from stack and return a pointer point to the data, return NULL if there is no data.
#include <iostream>
#include <cstring>

#define SIZE 100

using namespace std;

class Stack
{
public:
    Stack()
    {
        top = 0; //堆疊是空的
    }
    int push(int data)
    { 
      if(top < SIZE) //堆疊還沒滿
      {
        this->data[top] = data;
        top++;
        return 1;   
      }
       return -1;
    }

    int *pop()
    {
      if (top > 0)
      {
        top--;
        return &data[top];
         }
        return NULL;
    }
private:
    int data[SIZE];
    int top;
};

int main()
{
    int data, *temp;
    char command[50];
    Stack *stack = new Stack();
    while(1)
    {
        cin>>command;
        if(strcmp(command, "exit") == 0)
        {
            break;
        }
        else if(strcmp(command, "push") == 0)
        {
            cout<<"Please input a integer data:";
            cin>>data;
            if(stack->push(data) == 1)
            {
                cout<<"Successfully push data "<<data<<" into stack.\n";
            }
            else
            {
                cout<<"Failed to push data into stack.\n";
            }
        }
        else if(strcmp(command, "pop") == 0) 
        {
            temp = stack->pop();
            if(temp == NULL)
            {
                cout<<"Failed to pop a data from stack.\n";
            }
            else
            {
                cout<<"Pop data "<<*temp<<" from stack.\n"<<endl;
            }
        }
    }
}