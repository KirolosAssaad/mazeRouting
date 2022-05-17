#include <iostream>
#define Y_GRID_SIZE 750
#define X_GRID_SIZE 750
#define SOURCE 0
#define TARGERT -1
#define FREE_CELL -5
#define OBSTACLE -6


struct cell{
    int value;
    int layer = 1;
    int x;
    int y;
};


class boardClass{
cell board[X_GRID_SIZE][Y_GRID_SIZE];
int SX;
int SY;
int TX;
int TY;

public:
void setSX(int sx);
void setSY(int sy);
void setTX(int tx);
void setTY(int ty);
void fillBoard();
void init();
void printGrid();
};


int main (){


    boardClass boardTest;

    boardTest.init();
    boardTest.printGrid();
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

void boardClass::fillBoard(){

    for (int i = 0;i<X_GRID_SIZE;i++)
        for(int j = 0; j<Y_GRID_SIZE;j++)
        {
            board[i][j].value = FREE_CELL;
            board[i][j].x = i;
            board[i][j].y = j;
        }

    board[SX][SY].value = SOURCE;
    board[TX][TY].value = TARGERT;

    bool atTarget = false;

    int counter = 0;
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

}



void boardClass::init()
{
    setSX(5);
    setSY(15);    
    setTX(40);
    setTY(20);

    fillBoard();
}

void boardClass::printGrid()
{
    for (int i =0; i<X_GRID_SIZE;i++)
    {
        for (int j = 0;j<Y_GRID_SIZE; j++)
        {   
            if (board[i][j].value>=0 && board[i][j].value<10)
                std::cout<<" "<<board[i][j].value<<" ";
            else
                std::cout<<board[i][j].value<<" ";
        }
        std::cout<<std::endl;
    }
}