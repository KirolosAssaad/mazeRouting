#include <iostream>
#include <vector>
#define Y_GRID_SIZE 10
#define X_GRID_SIZE 10
#define SOURCE 0
#define TARGERT -1
#define FREE_CELL -5
#define OBSTACLE -6

using namespace std;
int counter;

struct cell{
    int value;
    int layer;
    int x;
    int y;
    bool valid;
};


class boardClass{
public:
vector<vector<cell>  > board;
int SX;
int SY;
int TX;
int TY;

public:
void setSX(int sx);
void setSY(int sy);
void setTX(int tx);
void setTY(int ty);
void findPath();
void init();
void printGrid(vector<vector<cell>  > new_board);
bool isValid(vector<vector<cell>  > new_board ,int row, int col, int prev_cell);
void findShortestPath(vector<vector<cell>  > new_board, int i, int j, int x, int y, vector<vector<cell>  > &finalBoard);



};


int main (){

    // cout<< "in main" << endl;
    boardClass boardTest;

    boardTest.init();
    boardTest.printGrid(boardTest.board);
    return 0;

}

void boardClass::setSX(int sx){
    SX = sx;
}

void boardClass::setSY(int sy){
    SY = sy;
}


void boardClass::setTX(int tx){
    TX = tx;
}

void boardClass::setTY(int ty){
    TY = ty;
}

void boardClass::findPath(){
    board.resize(X_GRID_SIZE, vector<cell>(Y_GRID_SIZE));

    for (int i = 0;i<X_GRID_SIZE;i++)
        for(int j = 0; j<Y_GRID_SIZE;j++)
        {
            board[i][j].value = FREE_CELL;
            board[i][j].x = i;
            board[i][j].y = j;
            board[i][j].layer=1;
            board[i][j].valid=true;
            

        }

    board[SX][SY].value = SOURCE;
    board[TX][TY].value = TARGERT;

    bool atTarget = false;

    counter = 0;
    while (!atTarget)
    {
        for(int i= 0;i<X_GRID_SIZE; i++)
        {
            for(int j=0; j<Y_GRID_SIZE;j++)
            {

                if (board[i][j].value == counter)
                {
                    if(j < Y_GRID_SIZE && board[i][j+1].value == FREE_CELL)
                        board[i][j+1].value = counter +1;
                    else if (j < Y_GRID_SIZE && board[i][j+1].value == TARGERT)
                        atTarget = true;
                    if(j > 0 && board[i][j-1].value == FREE_CELL)
                        board[i][j-1].value = counter +1;
                    else if (j > 0 && board[i][j-1].value == TARGERT)
                        atTarget = true;
                    if(i < X_GRID_SIZE && board[i+1][j].value == FREE_CELL)
                        board[i+1][j].value = counter +1;
                    else if (i < X_GRID_SIZE && board[i+1][j].value == TARGERT)
                        atTarget = true;
                    if(i > 0 && board[i-1][j].value == FREE_CELL)
                        board[i-1][j].value = counter +1;
                    else if ( i> 0 && board[i-1][j].value == TARGERT)
                        atTarget = true;
                }
            }
        }
        counter ++;
    }    

    findShortestPath(board, TX, TY, SX, SY,  board);

}



void boardClass::init()
{
    setSX(0);
    setSY(1);    
    setTX(5);
    setTY(5);

    findPath();
}

void boardClass::printGrid(vector<vector<cell>  > new_board)
{
    for (int i =0; i<X_GRID_SIZE;i++)
    {
        for (int j = 0;j<Y_GRID_SIZE; j++)
        {   
                std::cout<<" "<<new_board[i][j].valid<<" ";
            // if (new_board[i][j].value>=0 && new_board[i][j].value<10)
            //     std::cout<<" "<<new_board[i][j].value<<" ";
            // else
            //     std::cout<<new_board[i][j].value<<" ";
        }
        std::cout<<std::endl;
    }
}

bool boardClass::isValid(vector<vector<cell>  > new_board ,int row, int col, int prev_cell){
    // cout << row<<"  "<<col << endl;
    if(row<0 || row>= X_GRID_SIZE || col<0 || col >= Y_GRID_SIZE )
    {
        // cout<<"cond 1\n";
        return false;
    }
    if (new_board[row][col].valid == false)
    {
    
        // cout<<"cond2\n";
        return false;
    }
    if (new_board[row][col].value == prev_cell-1 )
    {
        // cout<<"true\n";
        return true;
    }

    if (prev_cell==-1)
    {
        if (new_board[row][col].value == counter-1)
        {
            // cout<<"true\n";
            return true;
        }
    }
    return false;
}

void boardClass::findShortestPath(vector<vector<cell>  > new_board, int i, int j, int x, int y, vector<vector<cell>  > &finalBoard)
{
    //if the destination is found, update `min_dist`
    if (i==x && j==y)
    {
        // cout<<"here----------------------------------------"<<endl;
        // printGrid(new_board);
        // cout<<"----------------------------------------"<<endl;
        finalBoard = new_board;
        return;
    }
 
    // set (i, j) cell as visited
    if (new_board[i][j].value != SOURCE && new_board[i][j].value != TARGERT ){

        new_board[i][j].valid= false;
        // cout<<"-------------------eeee---------------------"<<endl;

        // printGrid(new_board);    
        // cout<<"----------------------------------------"<<endl;

    }
 
    // go to the bottom cell
    if (isValid(new_board, i + 1, j, new_board[i][j].value)) {
        findShortestPath(new_board, i + 1, j, x, y, finalBoard);
    }
 
    // go to the right cell
    if (isValid(new_board, i, j + 1, new_board[i][j].value)) {
        findShortestPath(new_board, i, j + 1, x, y, finalBoard);
    }
 
    // go to the top cell
    if (isValid(new_board, i - 1, j, new_board[i][j].value)) {
        findShortestPath(new_board, i - 1, j, x, y, finalBoard);
    }
 
    // go to the left cell
    if (isValid(new_board, i, j - 1,new_board[i][j].value)) {
        findShortestPath(new_board, i, j - 1, x, y, finalBoard);
    }

    // return;
 
}

 
