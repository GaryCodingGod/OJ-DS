//Please finish function enqueue and dequeue
//Function enqueue will insert the data from the top of queue and return 1 on success, return -1 if not.
//Function dequeue will remove one data from the bottom of queue and return a pointer point the data, return NULL if there are on data.
//You can get 80 point if you finish this two function.
//You can get 100 point if you queue is circularity.
#include <iostream>
#include <cstring>

#define SIZE 100

using namespace std;

class Queue
{
public:
    Queue()
    {
        top = 0;
        bot = -1; 
    }

    int enqueue(int data)
    {
        if((top + 1) % SIZE == bot) // 如果佇列已滿，無法插入資料
        {
            return -1; 
        }

        // 如果 bot 為 -1，表示佇列為空，將 bot 設為 0
        if(bot == -1)
        {
            bot = 0;
        }

        // 插入資料到 top 位置
        this->data[top] = data;
        top = (top + 1) % SIZE;  // top 移到下一個位置，使用 % SIZE 確保循環

        return 1;   // 成功插入資料
    }

    int *dequeue()
    {
        // 如果佇列為空，返回 NULL
        if(bot == -1 || bot == top)
        {
            return NULL; // 佇列為空
        }

        // 取出 bot 位置的資料
        int *res = &data[bot];
        
        bot = (bot + 1) % SIZE;

        return res;  // 返回資料的指標
    }

private:
    int data[SIZE];  // 儲存資料的陣列
    int top, bot;    // top 表示插入位置，bot 表示取出位置
};

int main()
{
    int data, *temp;
    char command[50];
    Queue *queue = new Queue();
    while(1)
    {
        cin >> command;
        if(strcmp(command, "exit") == 0)
        {
            break;
        }
        else if(strcmp(command, "enqueue") == 0)
        {
            cout << "Please input a integer data:";
            cin >> data;
            if(queue->enqueue(data) == 1)
            {
                cout << "Successfully enqueue data " << data << " into queue." << endl;
            }
            else
            {
                cout << "Failed to enqueue data into queue." << endl;
            }
        }
        else if(strcmp(command, "dequeue") == 0)
        {
            temp = queue->dequeue();
            if(temp == NULL)
            {
                cout << "Failed to dequeue a data from queue.\n";
            }
            else
            {
                cout << "Dequeue data " << *temp << " from queue." << endl;
            }
        }
    }
}
