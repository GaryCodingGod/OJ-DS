//

#include<iostream>
#include<cstdlib>
#include<ctime>

#define SIZE 10

using namespace std;

class Node
{
public:
    Node() : row(0), col(0) {}
    Node(int r, int c) : row(r), col(c) {}

    int getRow() { return row; }
    int getCol() { return col; }
    void setRow(int r) { if(r >= 0 && r < SIZE) row = r; }
    void setCol(int c) { if(c >= 0 && c < SIZE) col = c; }

private:
    int col, row;
};

class List
{
public:
    List() { top = 0; }
/*
	function addElement
	Insert an element from list
*/
    void addElement(int r, int c)
    {
        if (top < SIZE * SIZE) // 檢查是否超過最大容量
        {
            data[top].setRow(r);
            data[top].setCol(c);
            top++;
        }
    }
/*
	function removeElement
	remove an element from list and return a pointer point to the element.
	If list is empty, return NULL.
*/

    Node *removeElement()
    {
        if (top > 0)
        {
            top--;
            return &data[top];  // 返回最後一個元素
        }
        return NULL; 
    }

    void printList()
    {
        for(int j = 0; j < top; j++)
        {
            cout << "(" << data[j].getRow() << ", " << data[j].getCol() << ")" << endl;
        }
    }

private:
    Node data[SIZE * SIZE];
    int top;
};

 /*
	function initMaze
	Alocate a 2-D array with s * s sizes as the map of maze.
	Inside the maze where 0 represent empty space and 1 represent wall.
	[0][0] is start point and [s - 1][s - 1] is finish point.
	Randomly generate 20% wall in the maze.
	Make sure [0][0] and [s - 1][s - 1] are 0

	動態配置一個二維的陣列，大小是 s * s ，用這個陣列表示迷宮的地圖
	陣列中 0 的值表示可以移動的空間， 1 表示牆壁 
	[0][0] 的位置表示起點 [s - 1][s - 1] 的位置表示終點
	請在迷宮中加入 20% 的牆壁 
	然後確定起點跟終點都是可以移動的位置 
*/
class Maze
{
public:
    Maze()
    {
        initMaze(SIZE);
    }

    void initMaze(int s)
    {
        maze = new int*[s];
        for(int i = 0; i < s; ++i)
        {
            maze[i] = new int[s];
        }

        srand(time(NULL));

        // 完成迷宮，隨機生成 20% 的牆壁，其他地方是空地
        for(int i = 0; i < s; ++i)
        {
            for(int j = 0; j < s; ++j)
            {
                int randomValue = rand() % 100; // 生成 0 到 99 的隨機數
                maze[i][j] = (randomValue < 20) ? 1 : 0; // 20% 機率設為牆壁
            }
        }

        maze[0][0] = 0;          // 確保起點 
        maze[s-1][s-1] = 0;      // 確保終點 
    }

/*
	function getPath
	This function will find a path between start point and finish point.
	Return a list content the path information inside.
	If there is no path between two point then the list will be empty.

	這個函數會找到起點到終點間的一條路徑
	回傳一個 list 包含著路徑的資訊
	如果找不到路徑的話 list 就會是空的 
*/
    List *getPath()
    {
        List *path = new List();  
        int x = 0, y = 0;         

        while (x < SIZE - 1 || y < SIZE - 1)
        {
            if (y + 1 < SIZE && maze[x][y + 1] == 0)
            {
                y++;  
                path->addElement(x, y);  
            }
            else if (x + 1 < SIZE && maze[x + 1][y] == 0)
            {
                x++;  
                path->addElement(x, y);  
            }
            else
            {
                break;  
            }
        }

        if (x == SIZE - 1 && y == SIZE - 1)
        {
            path->addElement(x, y);  
            return path;            
        }

        delete path;
        return new List();  
    }

    void printMaze()
    {
        for(int j = 0; j < SIZE; j++)
        {
            for(int k = 0; k < SIZE; k++)
            {
                if(maze[j][k] == 0)
                    cout << " ";
                else if(maze[j][k] == 1)
                    cout << "*";
            }
            cout << "\n";
        }
    }

    ~Maze()
    {
        for(int i = 0; i < SIZE; i++)
        {
            delete[] maze[i];
        }
        delete[] maze;
    }

private:
    int **maze;
};

int main()
{
    Maze *maze = new Maze();
    maze->printMaze();
    maze->getPath()->printList();
    delete maze; // 刪除 maze 釋放記憶體
}
