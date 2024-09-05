#include <iostream>
#include <vector>

using namespace std;

class Sudoku9x9 {
public:
    //vector board is a 9x9 array of ints
    vector<vector<int>> board;

    //constructor
    Sudoku9x9(vector<vector<int>> board) {
        this->board = board;
    }

    void takeInput() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cin >> board[i][j];
            }
        }
    }

    Sudoku9x9() {
        this->board = vector<vector<int>>(9, vector<int>(9, 0));
    }

    //print the board
    void printBoard() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool canPlace(int row, int col, int num) {
        //check row
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == num) {
                return false;
            }
        }

        //check column
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == num) {
                return false;
            }
        }

        //check 3x3 box
        int boxRow = row / 3;
        int boxCol = col / 3;
        for (int i = boxRow * 3; i < boxRow * 3 + 3; i++) {
            for (int j = boxCol * 3; j < boxCol * 3 + 3; j++) {
                if (board[i][j] == num) {
                    return false;
                }
            }
        }

        return true;
    }

    vector<int> findPlacebles(int row, int col) {
        vector<int> placebles;
        for (int i = 1; i <= 9; i++) {
            if (canPlace(row, col, i)) {
                placebles.push_back(i);
            }
        }
        return placebles;
    }

    bool SolveSudoku() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == 0) {
                    vector<int> placebles = findPlacebles(i, j);
                    for (int k = 0; k < placebles.size(); k++) {
                        board[i][j] = placebles[k];
                        if (SolveSudoku()) {
                            return true;
                        }
                        board[i][j] = 0;
                    }
                    return false;
                }
            }
        }
        return true;
    }

    void copyArray(vector<vector<int>> &board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                this->board[i][j] = board[i][j];
            }
        }
    }

    void nextEmpty(int &row, int &col) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == 0) {
                    row = i;
                    col = j;
                    return;
                }
            }
        }
    }

};
class Sudoku16x16{

    bool canPlace(int row, int col, int num) {
        //check row
        for (int i = 0; i < 16; i++) {
            if (board[row][i] == num) {
                return false;
            }
        }

        //check column
        for (int i = 0; i < 16; i++) {
            if (board[i][col] == num) {
                return false;
            }
        }

        //check 4x4 box
        int boxRow = row / 4;
        int boxCol = col / 4;
        for (int i = boxRow * 4; i < boxRow * 4 + 4; i++) {
            for (int j = boxCol * 4; j < boxCol * 4 + 4; j++) {
                if (board[i][j] == num) {
                    return false;
                }
            }
        }

        return true;
    }

    vector<int> findPlacebles(int row, int col) {
        vector<int> placebles;
        for (int i = 1; i < 17; i++) {
            if (canPlace(row, col, i)) {
                placebles.push_back(i);
            }
        }
        return placebles;
    }

    bool solve() {
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                if (board[i][j] == 0) {
                    vector<int> placebles = findPlacebles(i, j);
                    for (int k = 0; k < placebles.size(); k++) {
                        board[i][j] = placebles[k];
                        if (solve()) {
                            return true;
                        }
                        board[i][j] = 0;
                    }
                    return false;
                }
            }
        }
        return true;
    }


public:
//constructor
    Sudoku16x16(vector<vector<int>> board) {
        this->board = board;
    }

    bool SolveSudoku() {
        return solve();
    }

//print the board
    void printBoard() {
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

//16x16 board
    vector<vector<int>> board;

    Sudoku16x16() {
        this->board = vector<vector<int>>(16, vector<int>(16, 0));
    }

    void printLetterBoard() {
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                if (board[i][j] == 0) {
                    cout << "  ";
                } else {
                    cout << (char) (board[i][j] + 55) << " ";
                }
            }
            cout << endl;
        }
    }

};

int main() {
   /* vector<vector<int>> board = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };*/

    Sudoku9x9 sudoku;

    sudoku.takeInput();
    if(sudoku.SolveSudoku()) {
        sudoku.printBoard();
    } else {
        cout << "No Solution" << endl;
    }

    return 0;
}


/*Sample input:
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
8 0 0 0 6 0 0 0 3
4 0 0 8 0 3 0 0 1
7 0 0 0 2 0 0 0 6
0 6 0 0 0 0 2 8 0
0 0 0 4 1 9 0 0 5
0 0 0 0 8 0 0 7 9

Sample Output:
5 3 4 6 7 8 9 1 2
6 7 2 1 9 5 3 4 8
1 9 8 3 4 2 5 6 7
8 5 9 7 6 1 4 2 3
4 2 6 8 5 3 7 9 1
7 1 3 9 2 4 8 5 6
9 6 1 5 3 7 2 8 4
2 8 7 4 1 9 6 3 5
3 4 5 2 8 6 1 7 9

*/
