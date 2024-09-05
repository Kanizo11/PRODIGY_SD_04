#include <iostream>
#include <forward_list> 
#include <vector>
#include <cmath> 
#include <sstream> 

using namespace std;
//global variables
bool isSolved = false;
vector<vector<int>> mySudoku;
int sudokuSize=16;

class Sudoku16x16
{
public:
    int getSudWidth() const {
        return sudWidth;
    }

    void setSudWidth(int sudWidth) {
        Sudoku16x16::sudWidth = sudWidth;
    }

    int getCurrNum() const {
        return currNum;
    }

    void setCurrNum(int currNum) {
        Sudoku16x16::currNum = currNum;
    }

    int getSudHeight() const {
        return sudHeight;
    }

    void setSudHeight(int sudHeight) {
        Sudoku16x16::sudHeight = sudHeight;
    }

    int getDimension() const {
        return dimension;
    }

    void setDimension(int dimension) {
        Sudoku16x16::dimension = dimension;
    }

    const forward_list<int> &getQuickSud() const {
        return quickSud;
    }

    void setQuickSud(const forward_list<int> &quickSud) {
        Sudoku16x16::quickSud = quickSud;
    }

private:
    class Root;
    int  sudWidth = 16;
    int currNum;


    static char intXchar(int c){
        if(c<10){
            return char(c+48);
        }
        else{
            return char(c+55);
        }
    }


    class node
    {
    public:
        int row;
        Root *head;
        node *up, *down, *left, *right;
    };


    class Root : public node
    {
    public:
        int numOfNodes;
        Root *left, *right;
    };

    vector<Root> onY;

    int  sudHeight;
    int dimension;

    Root *rootLink;

    vector<vector<node>>onX;


public:

    Sudoku16x16()
    {
        dimension = sudokuSize;
        currNum = 16;
        sudHeight = (currNum * dimension * 4) + 1;

        
        sudWidth = (currNum * 16 ) * currNum;

        onX  = vector<vector<node>>(sudWidth, vector<node>(4, node()));
        
        onY= vector<Root>(sudHeight, Root());

        rootLink = &(onY[sudHeight - 1]);

        for (int i = 0; i < sudHeight; i++) 
        {

            onY[i].up = &onY[i];

            onY[i].down = &onY[i];

            onY[i].left = &(onY[(i + sudHeight - 1) % sudHeight]);

            onY[i].right = &(onY[(i + 1) % sudHeight]);

            onY[i].numOfNodes = 0;
        }

        int _size = dimension * currNum;
        int x_expansion =sqrt(currNum);
        int vertices;

        for (int i = 0; i < sudWidth; i++){

            int theeNum = i % currNum;
            int currRow = i / (currNum * dimension);
            int currCol = (i / currNum) % dimension;

            if (mySudoku[currRow][currCol] != 0 && mySudoku[currRow][currCol] != theeNum + 1)
                continue;

            for (int myTest = 0; myTest < 4; myTest++)
            {
                if(myTest == 0){
                    vertices = i / currNum;
                } else if(myTest == 1){
                    vertices = _size + (i % currNum) + (currCol * currNum);
                } else if(myTest == 2){
                    vertices = (2 * _size) + (currRow * currNum) + (i % currNum);
                } else if(myTest == 3){
                    vertices = (3 * _size) + (i % currNum) + (currRow / x_expansion) * x_expansion * currNum + (currCol / x_expansion) * currNum;
                } else{
                    //do nothing baby...!
                }


                onX[i][myTest].row = i;
                onX[i][myTest].down = &onY[vertices];

                int val1 =1;
                int val2 =4;
                onX[i][myTest].right = &(onX[i][(myTest + val1) % val2]);
                val1 = 3;
                onX[i][myTest].left = &(onX[i][(myTest + val1) % val2]);

                onX[i][myTest].up = onY[vertices].up;

                onX[i][myTest].head = &onY[vertices];

                onX[i][myTest].up->down = &onX[i][myTest];

                onX[i][myTest].down = &onY[vertices];

                onY[vertices].up->down = &(onX[i][myTest]);

                onY[vertices].up = &(onX[i][myTest]);


                onY[vertices].numOfNodes++; 
            }
        }
    };
    forward_list<int> quickSud;

    void printBoard()
    {
        int row_now;
        int col_now;
        int magicVal;

        for (int &r : quickSud)
        {

            row_now = r / (dimension * dimension);
            col_now = (r / dimension) % dimension;
            magicVal = r % dimension + 1;

            mySudoku[row_now][col_now] = magicVal;
        }

        for (int i = 0; i < dimension; i++)
        {
            for (int j = 0; j < dimension; j++)
            {
                cout << intXchar(mySudoku[i][j])<<" ";
            }
            cout << endl;
        }
    }

    void solveSud()
    {
        if (rootLink->right == rootLink)
        {
            isSolved = true;
            if (isSolved){
                printBoard();
            return;
            }
        }

        Root *optimalColumn = rootLink->right;

        for (Root *c =rootLink->right; c != rootLink; c = c->right)
        {
            if (c->numOfNodes < optimalColumn->numOfNodes)
            {optimalColumn = c;}

        }

        _conseal(optimalColumn);

        for (node *row_now = optimalColumn->down; row_now != optimalColumn; row_now = row_now->down)
        {

            quickSud.push_front(row_now->row);

            for (node *col_now = row_now->right; col_now != row_now; col_now = col_now->right) {
                _conseal(col_now->head);
            }
            solveSud();
            quickSud.pop_front();

            for (node *currCol = row_now->left; currCol != row_now; currCol = currCol->left){

                _reveal(currCol->head);
            }

        }

        _reveal(optimalColumn);
    }

private:
    
    static void _conseal(Root *col)
    {
        col->right->left = col->left;
        col->left->right = col->right;

        for (node *r = col->down; r != col; r = r->down)
        {
            for (node *c = r->right; c != r; c = c->right)
            {
                c->up->down = c->down;
                c->down->up = c->up;
                c->head->numOfNodes--;
            }
        }
    }

    static void _reveal(Root *column)
    {

        for (node *node_now = column->up; node_now != column; node_now = node_now->up){
            for (node *_curr = node_now->left; _curr != node_now; _curr = _curr->left){
                _curr->up->down = _curr;
                _curr->down->up = _curr;
                _curr->head->numOfNodes++;
            }
        }

        column->right->left = column;
        column->left->right = column;
    }
};

static int charxint(char c){

    if((int)c<58 && (int)c>47){

        return (int)c - 48;
    }
    else{

        return (int)c - 55;
    }
}

int main()
{
    string line;

    for (int i =0; i<16;++i)
    {
        vector<int>  row;
        getline(cin, line);

        stringstream currLine(line);

        string rowToAdd;

        while (getline(currLine, rowToAdd, ' ')){
          row.push_back(charxint(rowToAdd[0]));
        }
        mySudoku.push_back(row);
    }


    Sudoku16x16 mySudoku16x16;
    mySudoku16x16.solveSud();

    if (!isSolved){
        cout << "No Solution" << endl;
    }
    return 0;
}

