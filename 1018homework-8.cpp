#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

#define SIZE 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Grid
{
public:
 Grid()
 {
  state = 0;
        dir[UP] = NULL;
        dir[DOWN] = NULL;
        dir[LEFT] = NULL;
        dir[RIGHT] = NULL;
 }
 Grid(int s)
 {
  state = s;
  dir[UP] = NULL;
  dir[DOWN] = NULL;
  dir[LEFT] = NULL;
  dir[RIGHT] = NULL;
 }
 Grid *getDir(int d) { return dir[d]; }
 int getState() { return state; }
 void setDir(int d, Grid *g) { dir[d] = g; }
 void setState(int s) { state = s;}
private:
 Grid *dir[4]; // 定義一個名為 dir 的指標陣列，陣列的每個元素都是指向 Grid 物件的指標
 int state;
};

struct List
{
public:
 List()
 {
  top = 0; // 表示目前 data 陣列中元素的數量
 }
 void addElement(Grid *g) // g 是一個指向 Grid 類別物件的指標
 {
        if (top < SIZE * SIZE) {
            data[top++] = g;
        }
 }
 Grid *removeElement()
 {
        if (top > 0) {
            return data[--top]; // 回傳第 top 個元素，也就是回傳陣列中第 top - 1 個元素
        }
        return NULL;
 }
 void printPath()
 {
  int j;
  for(j = 1;j < top;j ++)
  { 
   // 檢查目前的格子是否等於前一個格子相鄰的四個方向（上、下、左、右）
   if(data[j] == data[j - 1]->getDir(UP))
   {
    cout<<"UP\n";
   }
   else if(data[j] == data[j - 1]->getDir(DOWN))
   {
    cout<<"DOWN\n";
   }
   else if(data[j] == data[j - 1]->getDir(LEFT))
   {
    cout<<"LEFT\n";
   }
   else if(data[j] == data[j - 1]->getDir(RIGHT))
   {
    cout<<"RIGHT\n";
   }
  }
 }
private:
 Grid *data[SIZE * SIZE];
 int top;
};

class Maze
{
public:
 Maze()
 {
  initMaze(SIZE);
 }
 
 void initMaze(int s)
 {
        srand(time(0)); // srand() 亂數產生器
        maze = new Grid(0);  // 生成迷宮起始點
        Grid *current = maze; // 表示的是從起點開始
  Grid *above = NULL; // 因為第一列不具有上方相鄰的格子

        for (int i = 0; i < s; i++) {
            Grid *rowStart = current;  // 每一列的起點
            for (int j = 0; j < s; j++) {
                if (i == 0 && j == 0) {
                    current->setState(0);  // 起點
                } else if (i == s-1 && j == s-1) {
                    current->setState(0);  // 終點
                    finish = current;
                } else {
                    current->setState((rand() % 100) < 20 ? 1 : 0);  // 20% 機率生成牆壁
                }

                // 設置左右連接
                if (j < s - 1) {
                    current->setDir(RIGHT, new Grid()); // 將當前格子的右邊連接到新創建的格子
                    current->getDir(RIGHT)->setDir(LEFT, current); // 將新創建格子的左邊連接回當前的格子
     // 以上這麼做的原因，是確保左右格子之間一定是相鄰的
                    current = current->getDir(RIGHT); // 將當前的格子移動到新創建的格子
                }
            }

            // 設置上下連接
            if (i < s - 1) { // 確保當前的列不是最後一列，因為最後一列不需要設置「下方」格子
                above = rowStart; // 先將當前列的起始格子指派給 above
                current = new Grid(); // 再設置新的下方格子

    // 先在當前格子的下方設置新的格子，再將新創建的格子上方設置為當前的格子，以確保上下之間是相鄰的
                rowStart->setDir(DOWN, current);
                current->setDir(UP, rowStart);
                rowStart = rowStart->getDir(DOWN); // 將當前的格子移動到下方的新格子
            }
        }
 }
 bool dfs(Grid *current, List &path) {
  if (!current || current->getState() == 1) return false;  // 碰到牆壁或無效的節點
  if (current == finish) return true;  // 找到終點

  path.addElement(current);  // 將當前節點加入路徑
  current->setState(1);  // 標記為已走過

  // 從當前格子的四個方向，不斷的進行探索出去的路徑
  for (int d = 0; d < 4; d++) {
   if (dfs(current->getDir(d), path)) {
    return true;  // 如果找到路徑，返回
   }
  }

  path.removeElement();  // 沒有找到路徑，回溯
  return false;
 }
 List *getPath()
 {
        List *path = new List();
        dfs(maze, *path);  // 從起點開始搜尋
        return path;
 }
 void printMaze()
 {
  Grid *j = maze, *k; // j 表示的是起點
  while(j != NULL)
  {
   k = j; // k 表示的是目前列的起點
   while(k != NULL)
   { 
    // 由左到右依序印出
    cout<<k->getState();
    k = k->getDir(RIGHT); 
   }
   cout<<endl;
   j = j->getDir(DOWN); // 讓 j 移動到下一列的起始點
  }
 }
private:
 Grid *maze;
    Grid *finish;
};

int main()
{
 Maze *maze = new Maze();
 maze->printMaze();
 maze->getPath()->printPath();
}