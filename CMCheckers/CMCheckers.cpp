// Created by Ahmed Ali, Harshit Gupta and Hussein Abdulrahman
// Started on Nov 20 2018, Last Modified on Nov 28, 2018
// This program is based on the game "Cylindrical Mule Checkers"
// This game is played between two players with an even number board size that ranges between 8x8 to 16x16
// The game ends when one of the players: only has mules left, has no more mules, if the player has no more possible moves or if the player's mule becomes a king

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Declare the global constants
const int MAX_ARRAY_SIZE = 18;
const int MIN_ARRAY_SIZE = 8;
const int WHITEMULE = 2;
const int MAX_PIECES = 72;
const int WHITEWINS = 1;
const int REDWINS = 2;
const int WHITESOLDIER = 1;
const int WHITEKING = 3;
const int REDSOLDIER = 4;
const int REDMULE = 5;
const int REDKING = 6;
const int WHITEPLAYER = 1;
const int REDPLAYER = 2;


// These are the prototype functions used to write the program

void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);
void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);
int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);
bool CheckList(int inArray1[], int inArray2[], int xIndex, int yIndex);
int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);
bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc);
bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc);
bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped);
bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);



int main()
{
    const int MAX_TRIES = 3;
    int i = 0;
    int j = 0;
    int myCMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = { 0 };
    int xIndicesMove[MAX_PIECES] = { 0 };
    int yIndicesMove[MAX_PIECES] = { 0 };
    int xIndicesJump[MAX_PIECES] = { 0 };
    int yIndicesJump[MAX_PIECES] = { 0 };
	char close[1024] = { '\0' };
    int numRowsInBoard = 0;
    int tries = 0;
    int player = 1;
    int countJump = 0;
    int countMove = 0;
    int toYLoc = 0;
    int toXLoc = 0;
    int fromSquareNumber = 0;
    int toSquareNumber = 0;
    int fromYLoc = 0;
    int fromXLoc = 0;
    int squareNum = 0;
    int error = 0;
    bool jumped = 0;
	bool isJump = 0;
    
    //This prompts the player to choose the value of the board size and checks if the value is valid
    do
    {
        cout << "Enter the number of squares along each edge of the board\n";
        if (!(cin >> numRowsInBoard))
        {
            cerr << "ERROR:  Board size is not an integer\n8 <= number of squares <= 18\n";
            cin.clear();
            cin.ignore(1024, '\n');
        }
        else if (numRowsInBoard > MAX_ARRAY_SIZE)
        {
            cerr << "ERROR:  Board size too large\n8 <= number of squares <= 18\n";
        }
        else if (numRowsInBoard < MIN_ARRAY_SIZE)
        {
            cerr << "ERROR:  Board size too small\n8 <= number of squares <= 18\n";
        }
        else if (numRowsInBoard % 2 == 1)
        {
            cerr << "ERROR:  Board size odd\n8 <= number of squares <= 18\n";
        }
        else
        {
            break;
        }
        tries++;
    } while (tries < MAX_TRIES);
    
    if (tries >= MAX_TRIES)
    {
        cerr << "ERROR:  Too many errors entering the size of the board\n";
        return 1;
    }
    
    
    // Gameboard will be created and displayed
    InitializeBoard(myCMCheckersBoard, numRowsInBoard);
    DisplayBoard(myCMCheckersBoard, numRowsInBoard);
    
    // Game starts at this point
    do {
        // Checks board for the possible moves and jumps available
        countJump = CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump);
        countMove = CountMove1Squares(myCMCheckersBoard, numRowsInBoard, player, xIndicesMove, yIndicesMove);
        
        error = 0;
        isJump = false;
        
        if (player == WHITEWINS && countJump == 0 && countMove == 0)
        {
            cout << "White is unable to move\nGAME OVER, Red has won\nEnter any character to close the game\n";
        }
        else if (player == REDWINS && countJump == 0 && countMove == 0)
        {
            cout << "Red is unable to move\nGAME OVER, White has won\nEnter any character to close the game\n";
        }
        else if (player == WHITEPLAYER && (countJump != 0 || countMove != 0))
        {
            cout << "White takes a turn\n";
        }
        else if (player == REDPLAYER && (countJump != 0 || countMove != 0))
        {
            cout << "Red takes a turn\n";
        }
        do {
            do
            {
                error = 0;
                isJump = false;
                // Prompts the player to input the square number for which he wants the checker to move to and check if it is valid
                cout << "Enter the square number of the checker you want to move\n";
                if (!(cin >> fromSquareNumber))
                {
                    cerr << "ERROR:  you did not enter an integer\nTry again\n";
                    cin.clear();
                    cin.ignore(1024, '\n');
                    continue;
                }
                else if (fromSquareNumber < 0 || fromSquareNumber >(numRowsInBoard * numRowsInBoard - 1))
                {
                    cerr << "ERROR:  that square is not on the board.\nTry again\n";
                    continue;
                }
                fromYLoc = fromSquareNumber / numRowsInBoard;
                fromXLoc = fromSquareNumber % numRowsInBoard;
                if (player == WHITEPLAYER)
                {
                    if (myCMCheckersBoard[fromYLoc][fromXLoc] == REDSOLDIER || myCMCheckersBoard[fromYLoc][fromXLoc] == REDMULE || myCMCheckersBoard[fromYLoc][fromXLoc] == REDKING)
                    {
                        cerr << "ERROR:  that square contains an opponent's checker\nTry again\n";
                        continue;
                    }
                }
                if (player == REDPLAYER)
                {
                    if (myCMCheckersBoard[fromYLoc][fromXLoc] == WHITESOLDIER || myCMCheckersBoard[fromYLoc][fromXLoc] == WHITEMULE || myCMCheckersBoard[fromYLoc][fromXLoc] == WHITEKING)
                    {
                        cerr << "ERROR:  that square contains an opponent's checker\nTry again\n";
                        continue;
                    }
                }
                if (myCMCheckersBoard[fromYLoc][fromXLoc] == 0)
                {
                    cerr << "ERROR:  that square is empty\nTry again\n";
                    continue;
                }
                for (i = 0; i < countJump; i++)
                {
                    if (fromYLoc == yIndicesJump[i] && fromXLoc == xIndicesJump[i])
                    {
                        isJump = true;
                        break;
                    }
                    else if (i == countJump - 1)
                    {
                        error++;
                        cerr << "ERROR: You can jump with another checker, you may not move your chosen checker\n";
                        cerr << "You can jump using checkers on the following squares: ";
                        for (j = 0; j < countJump; j++)
                        {
                            squareNum = yIndicesJump[j] * numRowsInBoard + xIndicesJump[j];
                            cout << squareNum << " ";
                        }
                        cerr << "\nTry again\n";
                        break;
                    }
                }
                if (error == 1)
                {
                    continue;
                }
                
                
                
                for (i = 0; i < countMove; i++)
                {
                    if (fromYLoc == yIndicesMove[i] && fromXLoc == xIndicesMove[i])
                    {
                        break;
                    }
                    else if (i == countMove - 1 && isJump == false)
                    {
                        error++;
                        cerr << "ERROR: There is no legal move for this checker\nTry again\n";
                    }
                }
                if (error == 1)
                {
                    continue;
                }
                break;
            } while (player != 0);
            
            do
            {
                // Prompts the player to input the square number for which he wants the checker to move to and check if it is valid
                // Checks to see if the movement is valid and checks if there are jumps over moves
                error = 0;
                cout << "Enter the square number of the square you want to move your checker to\n";
                if (!(cin >> toSquareNumber))
                {
                    cerr << "ERROR:  you did not enter an integer\nTry again\n";
                    cin.clear();
                    cin.ignore(1024, '\n');
                    continue;
                }
                else if (toSquareNumber < 0 || toSquareNumber >(numRowsInBoard * numRowsInBoard - 1))
                {
                    cerr << "ERROR:  It is not possible to move to a square that is not on the board.\nTry again\n";
                    continue;
                }
                toYLoc = toSquareNumber / numRowsInBoard;
                toXLoc = toSquareNumber % numRowsInBoard;
                if (myCMCheckersBoard[toYLoc][toXLoc] != 0)
                {
                    cerr << "ERROR:  It is not possible to move to a square that is already occupied\nTry again\n";
                    continue;
                }
                
                for (i = 0; i < countJump; i++)
                {
                    if (xIndicesJump[i] == fromXLoc && yIndicesJump[i] == fromYLoc && abs(toYLoc - fromYLoc) == 1)
                    {
                        error++;
                        cerr << "ERROR:  You can jump with this checker, you must jump not move 1 space\nTry again\n";
                        break;
                    }
                }
                if (error == 1)
                {
                    continue;
                }
                if (!(MakeMove(myCMCheckersBoard, numRowsInBoard, player, fromSquareNumber, toSquareNumber, jumped)))
                {
                    cerr << "ERROR: moving to that square is not legal, Try again\n";
                    continue;
                }
                break;
            } while (player != 0);
            break;
        } while (player != 0);
        
        while (jumped)
        {
            //If the last move was a jump, the player will get a chance to move the same checker to another place if a jump can still be made
            //Checks all of the possibilities and asks for the new destination of the checker
            jumped = 0;
            if (IsJump(myCMCheckersBoard, numRowsInBoard, player, toXLoc, toYLoc))
            {
                DisplayBoard(myCMCheckersBoard, numRowsInBoard);
                fromSquareNumber = toYLoc * numRowsInBoard + toXLoc;
                fromXLoc = toXLoc;
                fromYLoc = toYLoc;
                do
                {
                    error = 0;
                    cout << "You can jump again,  Please enter the next square you wish to move your checker to\n";
                    if (!(cin >> toSquareNumber))
                    {
                        cerr << "ERROR:  you did not enter an integer\nTry again\n";
                        cin.clear();
                        cin.ignore(1024, '\n');
                        continue;
                    }
                    else if (toSquareNumber < 0 || toSquareNumber >(numRowsInBoard * numRowsInBoard - 1))
                    {
                        cerr << "ERROR:  It is not possible to move to a square that is not on the board.\nTry again\n";
                        continue;
                    }
                    toYLoc = toSquareNumber / numRowsInBoard;
                    toXLoc = toSquareNumber % numRowsInBoard;
                    if (myCMCheckersBoard[toYLoc][toXLoc] != 0)
                    {
                        cerr << "ERROR:  It is not possible to move to a square that is already occupied\nTry again\n";
                        continue;
                    }
                    
                    for (i = 0; i < countJump; i++)
                    {
                        if (xIndicesJump[i] == fromXLoc && yIndicesJump[i] == fromYLoc && abs(toYLoc - fromYLoc) == 1)
                        {
                            error++;
                            cerr << "ERROR:  You can jump with this checker, you must jump not move 1 space\nTry again\n";
                            break;
                        }
                    }
                    if (error == 1)
                    {
                        continue;
                    }
                    if (!(MakeMove(myCMCheckersBoard, numRowsInBoard, player, fromSquareNumber, toSquareNumber, jumped)))
                    {
                        cerr << "ERROR: moving to that square is not legal, Try again\n";
                        continue;
                    }
                    break;
                } while (player != 0);
            }
        }
        DisplayBoard(myCMCheckersBoard, numRowsInBoard);
        if (CheckWin(myCMCheckersBoard, numRowsInBoard))
        {
            //This checks to see if the player has won, if not the game continues
            cout << "Enter any character to terminate the game then press the enter key\n";
            if (cin >> close) break;
        }
        //This will change turns to the other player
        if (player == WHITEPLAYER)
        {
            player = REDPLAYER;
        }
        else
        {
            player = WHITEPLAYER;
        }
    } while (player != 0);
    
    
    
    return 0;
}

void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
    //This is going to initalize the board at the beginning
    int i = 0;
    int j = 0;
    
    for (i = 0; i < numRowsInBoard; i++)
    {
        for (j = 0; j < numRowsInBoard; j++)
        {
            if ((i == 0) && (j % 2 == 1))
            {
                CMCheckersBoard[i][j] = WHITEMULE;
            }
			else if ((i % 2 == 1) && (i < numRowsInBoard / 2 - 1) && (j % 2 == 0))
			{
				CMCheckersBoard[i][j] = WHITESOLDIER;
			}
			else if ((i % 2 == 0) && (i < numRowsInBoard / 2 - 1) && (j % 2 == 1))
            {
                CMCheckersBoard[i][j] = WHITESOLDIER;
            }
            
            else if ((i == numRowsInBoard - 1) && (j % 2 == 0))
            {
                CMCheckersBoard[i][j] = REDMULE;
            }
			else if ((i % 2 == 1) && (i > numRowsInBoard / 2) && (j % 2 == 0))
			{
				CMCheckersBoard[i][j] = REDSOLDIER;
			}
			else if ((i % 2 == 0) && (i > numRowsInBoard / 2) && (j % 2 == 1))
            {
                CMCheckersBoard[i][j] = REDSOLDIER;
            }
        }
    }
}

void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
    //Display the board
    int sum = 0;
    int i = 0;
    int j = 0;
    
    
    for (i = 0; i < numRowsInBoard; i++)
    {
        for (j = 0; j < numRowsInBoard; j++)
        {
            if (CMCheckersBoard[i][j] == WHITESOLDIER)
            {
                cout << setw(4) << left << "WS";
            }
            else if (CMCheckersBoard[i][j] == WHITEMULE)
            {
                cout << setw(4) << left << "WM";
            }
            else if (CMCheckersBoard[i][j] == WHITEKING)
            {
                cout << setw(4) << left << "WK";
            }
            else if (CMCheckersBoard[i][j] == REDSOLDIER)
            {
                cout << setw(4) << left << "RS";
            }
            else if (CMCheckersBoard[i][j] == REDMULE)
            {
                cout << setw(4) << left << "RM";
            }
            else if (CMCheckersBoard[i][j] == REDKING)
            {
                cout << setw(4) << left << "RK";
            }
            else
            {
                cout << setw(4) << left << sum;
            }
            sum++;
        }
        cout << endl;
    }
    cout << endl << endl << endl;
}

int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
    //Checks how many possible jumps and checks which checker can make the jumps possible
    int counter = 0;
    int i = 0;
    int j = 0;
    
    
    for (i = 0; i < numRowsInBoard; i++)
    {
        xLocArray[i] = -1;
        yLocArray[i] = -1;
    }
    
    for (i = 0; i < numRowsInBoard; i++)
    {
        for (j = 0; j < numRowsInBoard; j++)
        {
            if (IsJump(CMCheckersBoard, numRowsInBoard, player, j, i))
            {
                xLocArray[counter] = j;
                yLocArray[counter] = i;
                counter++;
            }
        }
    }
    return counter;
}

bool CheckList(int inArray1[], int inArray2[], int xIndex, int yIndex)
{
    
    int i = 0;
    
    for (i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        if (inArray1[i] == xIndex && inArray2[i] == yIndex)
        {
            return true;
        }
    }
    return false;
}

int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
    // Checks how many possible movements and checks which checker can make the moves possible

    int counter = 0;
    int i = 0;
    int j = 0;
    
    
    for (i = 0; i < numRowsInBoard; i++)
    {
        xLocArray[i] = -1;
        yLocArray[i] = -1;
    }
    
    for (i = 0; i < numRowsInBoard; i++)
    {
        for (j = 0; j < numRowsInBoard; j++)
        {
            if (IsMove1Square(CMCheckersBoard, numRowsInBoard, player, j, i))
            {
                xLocArray[counter] = j;
                yLocArray[counter] = i;
                counter++;
            }
        }
    }
    return counter;
}

bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
    //Checks to see if a checker can move
    if (player == WHITEPLAYER)
    {
        if ((CMCheckersBoard[yLoc][xLoc] == WHITESOLDIER || CMCheckersBoard[yLoc][xLoc] == WHITEMULE || CMCheckersBoard[yLoc][xLoc] == WHITEKING) && (yLoc != numRowsInBoard - 1))
        {
            if (xLoc == 0)
            {
                if (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == 0 || CMCheckersBoard[yLoc + 1][xLoc + 1] == 0)
                {
                    return true;
                }
            }
            else if (xLoc == numRowsInBoard - 1)
            {
                if (CMCheckersBoard[yLoc + 1][0] == 0 || CMCheckersBoard[yLoc + 1][xLoc - 1] == 0)
                {
                    return true;
                }
            }
            else if (CMCheckersBoard[yLoc + 1][xLoc + 1] == 0 || CMCheckersBoard[yLoc + 1][xLoc - 1] == 0)
            {
                return true;
            }
        }
        if (CMCheckersBoard[yLoc][xLoc] == WHITEKING && yLoc != 0)
        {
            if (xLoc == 0)
            {
                if (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == 0 || CMCheckersBoard[yLoc - 1][xLoc + 1] == 0)
                {
                    return true;
                }
            }
            else if (xLoc == numRowsInBoard - 1)
            {
                if (CMCheckersBoard[yLoc - 1][0] == 0 || CMCheckersBoard[yLoc - 1][xLoc - 1] == 0)
                {
                    return true;
                }
            }
            else if (CMCheckersBoard[yLoc - 1][xLoc + 1] == 0 || CMCheckersBoard[yLoc - 1][xLoc - 1] == 0)
            {
                return true;
            }
        }
    }
    
    else if (player == REDPLAYER)
    {
        if ((CMCheckersBoard[yLoc][xLoc] == REDSOLDIER || CMCheckersBoard[yLoc][xLoc] == REDMULE || CMCheckersBoard[yLoc][xLoc] == REDKING) && (yLoc != 0))
        {
            if (xLoc == 0)
            {
                if (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == 0 || CMCheckersBoard[yLoc - 1][xLoc + 1] == 0)
                {
                    return true;
                }
            }
            else if (xLoc == numRowsInBoard - 1)
            {
                if (CMCheckersBoard[yLoc - 1][0] == 0 || CMCheckersBoard[yLoc - 1][xLoc - 1] == 0)
                {
                    return true;
                }
            }
            else if (CMCheckersBoard[yLoc - 1][xLoc + 1] == 0 || CMCheckersBoard[yLoc - 1][xLoc - 1] == 0)
            {
                return true;
            }
        }
        if (CMCheckersBoard[yLoc][xLoc] == REDKING && yLoc != numRowsInBoard - 1)
        {
            if (xLoc == 0)
            {
                if (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == 0 || CMCheckersBoard[yLoc + 1][xLoc + 1] == 0)
                {
                    return true;
                }
            }
            else if (xLoc == numRowsInBoard - 1)
            {
                if (CMCheckersBoard[yLoc + 1][0] == 0 || CMCheckersBoard[yLoc + 1][xLoc - 1] == 0)
                {
                    return true;
                }
            }
            else if (CMCheckersBoard[yLoc + 1][xLoc + 1] == 0 || CMCheckersBoard[yLoc + 1][xLoc - 1] == 0)
            {
                return true;
            }
        }
    }
    
    return false;
}

bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
    //Checks to see if a checker can jump
    if (player == WHITEPLAYER)
    {
        if ((CMCheckersBoard[yLoc][xLoc] == WHITESOLDIER || CMCheckersBoard[yLoc][xLoc] == WHITEMULE || CMCheckersBoard[yLoc][xLoc] == WHITEKING) && (yLoc != numRowsInBoard - 1 && yLoc != numRowsInBoard - 2))
        {
            if (xLoc == 0 && (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == REDMULE || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == REDKING) && (CMCheckersBoard[yLoc + 2][numRowsInBoard - 2] == 0))
            {
                return true;
            }
            else if (xLoc == numRowsInBoard - 1 && (CMCheckersBoard[yLoc + 1][0] == REDSOLDIER || CMCheckersBoard[yLoc + 1][0] == REDMULE || CMCheckersBoard[yLoc + 1][0] == REDKING) && (CMCheckersBoard[yLoc + 2][1] == 0))
            {
                return true;
            }
            else if (xLoc == 1 && (CMCheckersBoard[yLoc + 1][0] == REDSOLDIER || CMCheckersBoard[yLoc + 1][0] == REDMULE || CMCheckersBoard[yLoc + 1][0] == REDKING) && (CMCheckersBoard[yLoc + 2][numRowsInBoard - 1] == 0))
            {
                return true;
            }
            else if (xLoc == numRowsInBoard - 2 && (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == REDMULE || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == REDKING) && (CMCheckersBoard[yLoc + 2][0] == 0))
            {
                return true;
            }
            else if ((CMCheckersBoard[yLoc + 1][xLoc + 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][xLoc + 1] == REDMULE || CMCheckersBoard[yLoc + 1][xLoc + 1] == REDKING) && (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0) && (xLoc != numRowsInBoard - 1 && xLoc != numRowsInBoard - 2))
            {
                return true;
            }
            else if ((CMCheckersBoard[yLoc + 1][xLoc - 1] == REDSOLDIER || CMCheckersBoard[yLoc + 1][xLoc - 1] == REDMULE || CMCheckersBoard[yLoc + 1][xLoc - 1] == REDKING) && (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0) && (xLoc != 0 && xLoc != 1))
            {
                return true;
            }
        }
        if (CMCheckersBoard[yLoc][xLoc] == WHITEKING && (yLoc != 0 && yLoc != 1))
        {
            if (xLoc == 0 && (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == REDMULE || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == REDKING) && (CMCheckersBoard[yLoc - 2][numRowsInBoard - 1] == 0))
            {
                return true;
            }
            else if (xLoc == numRowsInBoard - 1 && (CMCheckersBoard[yLoc - 1][0] == REDSOLDIER || CMCheckersBoard[yLoc - 1][0] == REDMULE || CMCheckersBoard[yLoc - 1][0] == REDKING) && (CMCheckersBoard[yLoc - 2][0] == 0))
            {
                return true;
            }
            else if (xLoc == 1 && (CMCheckersBoard[yLoc - 1][0] == REDSOLDIER || CMCheckersBoard[yLoc - 1][0] == REDMULE || CMCheckersBoard[yLoc - 1][0] == REDKING) && (CMCheckersBoard[yLoc - 2][numRowsInBoard - 1] == 0))
            {
                return true;
            }
            else if (xLoc == numRowsInBoard - 2 && (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == REDMULE || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == REDKING) && (CMCheckersBoard[yLoc - 2][0] == 0))
            {
                return true;
            }
            else if ((CMCheckersBoard[yLoc - 1][xLoc + 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][xLoc + 1] == REDMULE || CMCheckersBoard[yLoc - 1][xLoc + 1] == REDKING) && (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0) && (xLoc != numRowsInBoard - 1 && xLoc != numRowsInBoard - 2))
            {
                return true;
            }
            else if ((CMCheckersBoard[yLoc - 1][xLoc - 1] == REDSOLDIER || CMCheckersBoard[yLoc - 1][xLoc - 1] == REDMULE || CMCheckersBoard[yLoc - 1][xLoc - 1] == REDKING) && (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0) && (xLoc != 0 && xLoc != 1))
            {
                return true;
            }
        }
    }
    
    if (player == REDPLAYER)
    {
        if ((CMCheckersBoard[yLoc][xLoc] == REDSOLDIER || CMCheckersBoard[yLoc][xLoc] == REDMULE || CMCheckersBoard[yLoc][xLoc] == REDKING) && (yLoc != 0 && yLoc != 1))
        {
            if (xLoc == 0 && (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == WHITEKING) && (CMCheckersBoard[yLoc - 2][numRowsInBoard - 2] == 0))
            {
                return true;
            }
            else if (xLoc == numRowsInBoard - 1 && (CMCheckersBoard[yLoc - 1][0] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][0] == WHITEMULE || CMCheckersBoard[yLoc - 1][0] == WHITEKING) && (CMCheckersBoard[yLoc - 2][1] == 0))
            {
                return true;
            }
            else if (xLoc == 1 && (CMCheckersBoard[yLoc - 1][0] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][0] == WHITEMULE || CMCheckersBoard[yLoc - 1][0] == WHITEKING) && (CMCheckersBoard[yLoc - 2][numRowsInBoard - 1] == 0))
            {
                return true;
            }
            else if (xLoc == numRowsInBoard - 2 && (CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][numRowsInBoard - 1] == WHITEKING) && (CMCheckersBoard[yLoc - 2][0] == 0))
            {
                return true;
            }
            else if ((CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][xLoc + 1] == WHITEKING) && (CMCheckersBoard[yLoc - 2][xLoc + 2] == 0) && (xLoc != numRowsInBoard - 1 && xLoc != numRowsInBoard - 2))
            {
                return true;
            }
            else if ((CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITESOLDIER || CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEMULE || CMCheckersBoard[yLoc - 1][xLoc - 1] == WHITEKING) && (CMCheckersBoard[yLoc - 2][xLoc - 2] == 0) && (xLoc != 0 && xLoc != 1))
            {
                return true;
            }
        }
        if (CMCheckersBoard[yLoc][xLoc] == REDKING && (yLoc != numRowsInBoard - 1 && yLoc != numRowsInBoard - 2))
        {
            if (xLoc == 0 && (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITEKING) && (CMCheckersBoard[yLoc + 2][numRowsInBoard - 2] == 0))
            {
                return true;
            }
            else if (xLoc == numRowsInBoard - 1 && (CMCheckersBoard[yLoc + 1][0] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][0] == WHITEMULE || CMCheckersBoard[yLoc + 1][0] == WHITEKING) && (CMCheckersBoard[yLoc + 2][1] == 0))
            {
                return true;
            }
            else if (xLoc == 1 && (CMCheckersBoard[yLoc + 1][0] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][0] == WHITEMULE || CMCheckersBoard[yLoc + 1][0] == WHITEKING) && (CMCheckersBoard[yLoc + 2][numRowsInBoard - 1] == 0))
            {
                return true;
            }
            else if (xLoc == numRowsInBoard - 2 && (CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][numRowsInBoard - 1] == WHITEKING) && (CMCheckersBoard[yLoc + 2][0] == 0))
            {
                return true;
            }
            else if ((CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][xLoc + 1] == WHITEKING) && (CMCheckersBoard[yLoc + 2][xLoc + 2] == 0) && (xLoc != numRowsInBoard - 1 && xLoc != numRowsInBoard - 2))
            {
                return true;
            }
            else if ((CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITESOLDIER || CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEMULE || CMCheckersBoard[yLoc + 1][xLoc - 1] == WHITEKING) && (CMCheckersBoard[yLoc + 2][xLoc - 2] == 0) && (xLoc != 0 && xLoc != 1))
            {
                return true;
            }
        }
    }
    
    return false;
}

bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped)
{
    //This will move the checker if it meets all requirements
    int xdistance = 0;
    int ydistance = 0;
    int fromXLoc = 0;
    int fromYLoc = 0;
    int toXLoc = 0;
    int toYLoc = 0;
    char close[1024] = { '\0' };
    
    fromYLoc = fromSquareNum / numRowsInBoard;
    fromXLoc = fromSquareNum % numRowsInBoard;
    toYLoc = toSquareNum / numRowsInBoard;
    toXLoc = toSquareNum % numRowsInBoard;
    
    if (fromXLoc == 0 && toXLoc == numRowsInBoard - 1)
    {
        xdistance = 1;
    }
    else if (fromXLoc == numRowsInBoard - 1 && toXLoc == 0)
    {
        xdistance = 1;
    }
    else if (fromXLoc == 0 && toXLoc == numRowsInBoard - 2)
    {
        xdistance = 2;
    }
    else if (fromXLoc == numRowsInBoard - 2 && toXLoc == 0)
    {
        xdistance = 2;
    }
    else if (fromXLoc == numRowsInBoard - 1 && toXLoc == 1)
    {
        xdistance = 2;
    }
    else if (fromXLoc == 1 && toXLoc == numRowsInBoard - 1)
    {
        xdistance = 2;
    }
    else
    {
        xdistance = abs(toXLoc - fromXLoc);
    }
    ydistance = abs(toYLoc - fromYLoc);
    
    if (xdistance > 2 || ydistance > 2)
    {
        cerr << "Error;  illegal move\n";
        return false;
    }
    
    if (xdistance != ydistance)
    {
        cerr << "Error;  illegal move\n";
        return false;
    }
    
    if (player == WHITEPLAYER)
    {
        if (xdistance == 2)
        {
            if (toYLoc - fromYLoc > 0)
            {
                if (fromXLoc == 0 && toXLoc == numRowsInBoard - 2 && ((CMCheckersBoard[fromYLoc + 1][numRowsInBoard - 1] != REDSOLDIER && CMCheckersBoard[fromYLoc + 1][numRowsInBoard - 1] != REDMULE && CMCheckersBoard[fromYLoc + 1][numRowsInBoard - 1] != REDKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0)))
                {
                    cerr << "Error;  illegal move\n";
                    return false;
                }
                else if (fromXLoc == numRowsInBoard - 1 && toXLoc == 1 && ((CMCheckersBoard[fromYLoc + 1][0] != REDSOLDIER && CMCheckersBoard[fromYLoc + 1][0] != REDMULE && CMCheckersBoard[fromYLoc + 1][0] != REDKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0)))
                {
                    cerr << "Error;  illegal move\n";
                    return false;
                }
                else if (fromXLoc == 1 && toXLoc == numRowsInBoard - 1 && ((CMCheckersBoard[fromYLoc + 1][0] != REDSOLDIER && CMCheckersBoard[fromYLoc + 1][0] != REDMULE && CMCheckersBoard[fromYLoc + 1][0] != REDKING) && (CMCheckersBoard[toYLoc][toXLoc] != 0)))
                {
                    cerr << "Error;  illegal move\n";
                    return false;
                }
                else if (fromXLoc == numRowsInBoard - 2 && toXLoc == 0 && ((CMCheckersBoard[fromYLoc + 1][numRowsInBoard - 1] != REDSOLDIER && CMCheckersBoard[fromYLoc + 1][numRowsInBoard - 1] != REDMULE && CMCheckersBoard[fromYLoc + 1][numRowsInBoard - 1] != REDKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0)))
                {
                    cerr << "Error;  illegal move\n";
                    return false;
                }
                else if (toXLoc - fromXLoc > 0 && fromXLoc != 0 && fromXLoc != 1)
                {
                    if ((CMCheckersBoard[fromYLoc + 1][fromXLoc + 1] != REDSOLDIER && CMCheckersBoard[fromYLoc + 1][fromXLoc + 1] != REDMULE && CMCheckersBoard[fromYLoc + 1][fromXLoc + 1] != REDKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0))
                    {
                        cerr << "Error;  illegal move\n";
                        return false;
                    }
                }
                else if (toXLoc - fromXLoc < 0 && fromXLoc != numRowsInBoard - 1 && fromXLoc != numRowsInBoard - 2)
                {
                    if ((CMCheckersBoard[fromYLoc + 1][fromXLoc - 1] != REDSOLDIER && CMCheckersBoard[fromYLoc + 1][fromXLoc - 1] != REDMULE && CMCheckersBoard[fromYLoc + 1][fromXLoc - 1] != REDKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0))
                    {
                        cerr << "Error;  illegal move\n";
                        return false;
                    }
                }
            }
            else if (toYLoc - fromYLoc < 0 && (CMCheckersBoard[fromYLoc][fromXLoc] == WHITESOLDIER || CMCheckersBoard[fromYLoc][fromXLoc] == WHITEMULE))
            {
                cerr << "Error;  illegal move\n";
                return false;
            }
            else if (toYLoc - fromYLoc < 0 && (CMCheckersBoard[fromYLoc][fromXLoc] == WHITEKING))
            {
                if (fromXLoc == 0 && toXLoc == numRowsInBoard - 2 && ((CMCheckersBoard[fromYLoc - 1][numRowsInBoard - 1] != REDSOLDIER && CMCheckersBoard[fromYLoc - 1][numRowsInBoard - 1] != REDMULE && CMCheckersBoard[fromYLoc - 1][numRowsInBoard - 1] != REDKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0)))
                {
                    cerr << "Error;  illegal move\n";
                    return false;
                }
                else if (fromXLoc == numRowsInBoard - 1 && toXLoc == 1 && ((CMCheckersBoard[fromYLoc - 1][0] != REDSOLDIER && CMCheckersBoard[fromYLoc - 1][0] != REDMULE && CMCheckersBoard[fromYLoc - 1][0] != REDKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0)))
                {
                    cerr << "Error;  illegal move\n";
                    return false;
                }
                else if (fromXLoc == 1 && toXLoc == numRowsInBoard - 1 && ((CMCheckersBoard[fromYLoc - 1][0] != REDSOLDIER && CMCheckersBoard[fromYLoc - 1][0] != REDMULE && CMCheckersBoard[fromYLoc - 1][0] != REDKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0)))
                {
                    cerr << "Error;  illegal move\n";
                    return false;
                }
                else if (fromXLoc == numRowsInBoard - 2 && toXLoc == 0 && ((CMCheckersBoard[fromYLoc - 1][numRowsInBoard - 1] != REDSOLDIER && CMCheckersBoard[fromYLoc - 1][numRowsInBoard - 1] != REDMULE && CMCheckersBoard[fromYLoc - 1][numRowsInBoard - 1] != REDKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0)))
                {
                    cerr << "Error;  illegal move\n";
                    return false;
                }
                else if (toXLoc - fromXLoc > 0 && fromXLoc != 0 && fromXLoc != 1)
                {
                    if ((CMCheckersBoard[fromYLoc - 1][fromXLoc + 1] != REDSOLDIER && CMCheckersBoard[fromYLoc - 1][fromXLoc + 1] != REDMULE && CMCheckersBoard[fromYLoc - 1][fromXLoc + 1] != REDKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0))
                    {
                        cerr << "Error;  illegal move\n";
                        return false;
                    }
                }
                else if (toXLoc - fromXLoc < 0 && fromXLoc != numRowsInBoard - 1 && fromXLoc != numRowsInBoard - 2)
                {
                    if ((CMCheckersBoard[fromYLoc - 1][fromXLoc - 1] != REDSOLDIER && CMCheckersBoard[fromYLoc - 1][fromXLoc - 1] != REDMULE && CMCheckersBoard[fromYLoc - 1][fromXLoc - 1] != REDKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0))
                    {
                        cerr << "Error;  illegal move\n";
                        return false;
                    }
                }
            }
        }
        else if (toYLoc - fromYLoc < 0 && (CMCheckersBoard[fromYLoc][fromXLoc] == WHITESOLDIER || CMCheckersBoard[fromYLoc][fromXLoc] == WHITEMULE))
        {
            cerr << "Error;  illegal move\n";
            return false;
        }
    }
    
    if (player == REDPLAYER)
    {
        if (xdistance == ydistance && xdistance == 2)
        {
            if (toYLoc - fromYLoc < 0)
            {
                if (fromXLoc == 0 && toXLoc == numRowsInBoard - 2 && ((CMCheckersBoard[fromYLoc - 1][numRowsInBoard - 1] != WHITESOLDIER && CMCheckersBoard[fromYLoc - 1][numRowsInBoard - 1] != WHITEMULE && CMCheckersBoard[fromYLoc - 1][numRowsInBoard - 1] != WHITEKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0)))
                {
                    cerr << "Error;  illegal move\n";
                    return false;
                }
                else if (fromXLoc == numRowsInBoard - 1 && toXLoc == 1 && ((CMCheckersBoard[fromYLoc - 1][0] != WHITESOLDIER && CMCheckersBoard[fromYLoc - 1][0] != WHITEMULE && CMCheckersBoard[fromYLoc - 1][0] != WHITEKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0)))
                {
                    cerr << "Error;  illegal move\n";
                    return false;
                }
                else if (fromXLoc == 1 && toXLoc == numRowsInBoard - 1 && ((CMCheckersBoard[fromYLoc - 1][0] != WHITESOLDIER && CMCheckersBoard[fromYLoc - 1][0] != WHITEMULE && CMCheckersBoard[fromYLoc - 1][0] != WHITEKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0)))
                {
                    cerr << "Error;  illegal move\n";
                    return false;
                }
                else if (fromXLoc == numRowsInBoard - 2 && toXLoc == 0 && ((CMCheckersBoard[fromYLoc - 1][numRowsInBoard - 1] != WHITESOLDIER && CMCheckersBoard[fromYLoc - 1][numRowsInBoard - 1] != WHITEMULE && CMCheckersBoard[fromYLoc - 1][numRowsInBoard - 1] != WHITEKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0)))
                {
                    cerr << "Error;  illegal move\n";
                    return false;
                }
                else if (toXLoc - fromXLoc > 0 && fromXLoc != 0 && fromXLoc != 1)
                {
                    if ((CMCheckersBoard[fromYLoc - 1][fromXLoc + 1] != WHITESOLDIER && CMCheckersBoard[fromYLoc - 1][fromXLoc + 1] != WHITEMULE && CMCheckersBoard[fromYLoc - 1][fromXLoc + 1] != WHITEKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0))
                    {
                        cerr << "Error;  illegal move\n";
                        return false;
                    }
                }
                else if (toXLoc - fromXLoc < 0 && fromXLoc != numRowsInBoard - 1 && fromXLoc != numRowsInBoard - 2)
                {
                    if ((CMCheckersBoard[fromYLoc - 1][fromXLoc - 1] != WHITESOLDIER && CMCheckersBoard[fromYLoc - 1][fromXLoc - 1] != WHITEMULE && CMCheckersBoard[fromYLoc - 1][fromXLoc - 1] != WHITEKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0))
                    {
                        cerr << "Error;  illegal move\n";
                        return false;
                    }
                }
            }
            else if (toYLoc - fromYLoc > 0 && (CMCheckersBoard[fromYLoc][fromXLoc] == REDSOLDIER || CMCheckersBoard[fromYLoc][fromXLoc] == REDMULE))
            {
                cerr << "Error;  illegal move\n";
                return false;
            }
            else if (toYLoc - fromYLoc > 0 && (CMCheckersBoard[fromYLoc][fromXLoc] == REDKING))
            {
                if (fromXLoc == 0 && toXLoc == numRowsInBoard - 2 && ((CMCheckersBoard[fromYLoc + 1][numRowsInBoard - 1] != WHITESOLDIER && CMCheckersBoard[fromYLoc + 1][numRowsInBoard - 1] != WHITEMULE && CMCheckersBoard[fromYLoc + 1][numRowsInBoard - 1] != WHITEKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0)))
                {
                    cerr << "Error;  illegal move\n";
                    return false;
                }
                else if (fromXLoc == numRowsInBoard - 1 && toXLoc == 1 && ((CMCheckersBoard[fromYLoc + 1][0] != WHITESOLDIER && CMCheckersBoard[fromYLoc + 1][0] != WHITEMULE && CMCheckersBoard[fromYLoc + 1][0] != WHITEKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0)))
                {
                    cerr << "Error;  illegal move\n";
                    return false;
                }
                else if (fromXLoc == 1 && toXLoc == numRowsInBoard - 1 && ((CMCheckersBoard[fromYLoc + 1][0] != WHITESOLDIER && CMCheckersBoard[fromYLoc + 1][0] != WHITEMULE && CMCheckersBoard[fromYLoc + 1][0] != WHITEKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0)))
                {
                    cerr << "Error;  illegal move\n";
                    return false;
                }
                else if (fromXLoc == numRowsInBoard - 2 && toXLoc == 0 && ((CMCheckersBoard[fromYLoc + 1][numRowsInBoard - 1] != WHITESOLDIER && CMCheckersBoard[fromYLoc + 1][numRowsInBoard - 1] != WHITEMULE && CMCheckersBoard[fromYLoc + 1][numRowsInBoard - 1] != WHITEKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0)))
                {
                    cerr << "Error;  illegal move\n";
                    return false;
                }
                else if (toXLoc - fromXLoc > 0 && fromXLoc != 0 && fromXLoc != 1)
                {
                    if ((CMCheckersBoard[fromYLoc + 1][fromXLoc + 1] != WHITESOLDIER && CMCheckersBoard[fromYLoc + 1][fromXLoc + 1] != WHITEMULE && CMCheckersBoard[fromYLoc + 1][fromXLoc + 1] != WHITEKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0))
                    {
                        cerr << "Error;  illegal move\n";
                        return false;
                    }
                }
                else if (toXLoc - fromXLoc < 0 && fromXLoc != numRowsInBoard - 1 && fromXLoc != numRowsInBoard - 2)
                {
                    if ((CMCheckersBoard[fromYLoc + 1][fromXLoc - 1] != WHITESOLDIER && CMCheckersBoard[fromYLoc + 1][fromXLoc - 1] != WHITEMULE && CMCheckersBoard[fromYLoc + 1][fromXLoc - 1] != WHITEKING) || (CMCheckersBoard[toYLoc][toXLoc] != 0))
                    {
                        cerr << "Error;  illegal move\n";
                        return false;
                    }
                }
            }
        }
        else if (toYLoc - fromYLoc > 0 && (CMCheckersBoard[fromYLoc][fromXLoc] == REDSOLDIER || CMCheckersBoard[fromYLoc][fromXLoc] == REDMULE))
        {
            cerr << "Error;  illegal move\n";
            return false;
        }
    }
    CMCheckersBoard[toYLoc][toXLoc] = CMCheckersBoard[fromYLoc][fromXLoc];
    CMCheckersBoard[fromYLoc][fromXLoc] = 0;
    if (xdistance == ydistance && xdistance == 2)
    {
        if (toYLoc - fromYLoc > 0)
        {
            if (fromXLoc == 0 && toXLoc == numRowsInBoard - 2)
            {
                CMCheckersBoard[fromYLoc + 1][numRowsInBoard - 1] = 0;
            }
            else if (fromXLoc == numRowsInBoard - 1 && toXLoc == 1)
            {
                CMCheckersBoard[fromYLoc + 1][0] = 0;
            }
            else if (fromXLoc == 1 && toXLoc == numRowsInBoard - 1)
            {
                CMCheckersBoard[fromYLoc + 1][0] = 0;
            }
            else if (fromXLoc == numRowsInBoard - 2 && toXLoc == 0)
            {
                CMCheckersBoard[fromYLoc + 1][numRowsInBoard - 1] = 0;
            }
            else if (toXLoc - fromXLoc > 0)
            {
                CMCheckersBoard[fromYLoc + 1][fromXLoc + 1] = 0;
            }
            else if (toXLoc - fromXLoc < 0)
            {
                CMCheckersBoard[fromYLoc + 1][fromXLoc - 1] = 0;
            }
        }
        else if (toYLoc - fromYLoc < 0)
        {
            if (fromXLoc == 0 && toXLoc == numRowsInBoard - 2)
            {
                CMCheckersBoard[fromYLoc - 1][numRowsInBoard - 1] = 0;
            }
            else if (fromXLoc == numRowsInBoard - 1 && toXLoc == 1)
            {
                CMCheckersBoard[fromYLoc - 1][0] = 0;
            }
            else if (fromXLoc == 1 && toXLoc == numRowsInBoard - 1)
            {
                CMCheckersBoard[fromYLoc - 1][0] = 0;
            }
            else if (fromXLoc == numRowsInBoard - 2 && toXLoc == 0)
            {
                CMCheckersBoard[fromYLoc - 1][numRowsInBoard - 1] = 0;
            }
            else if (toXLoc - fromXLoc > 0)
            {
                CMCheckersBoard[fromYLoc - 1][fromXLoc + 1] = 0;
            }
            else if (toXLoc - fromXLoc < 0)
            {
                CMCheckersBoard[fromYLoc - 1][fromXLoc - 1] = 0;
            }
        }
    }
    
    if (toYLoc == numRowsInBoard - 1 && CMCheckersBoard[toYLoc][toXLoc] == WHITEMULE)
    {
        CMCheckersBoard[toYLoc][toXLoc] = WHITEKING;
        DisplayBoard(CMCheckersBoard, numRowsInBoard);
        cout << "White has created a Mule King, Red wins the game\n";
        cout << "Enter any character to terminate the game then press the enter key\n";
        if (cin >> close)
        {
            exit(1);
        }
    }
    else if (toYLoc == numRowsInBoard - 1 && CMCheckersBoard[toYLoc][toXLoc] == WHITESOLDIER)
    {
        CMCheckersBoard[toYLoc][toXLoc] = WHITEKING;
        return true;
    }
    
    if (toYLoc == 0 && CMCheckersBoard[toYLoc][toXLoc] == REDMULE)
    {
        CMCheckersBoard[toYLoc][toXLoc] = REDKING;
        DisplayBoard(CMCheckersBoard, numRowsInBoard);
        cout << "Red has created a Mule King,  White wins the game\n";
        cout << "Enter any character to terminate the game then press the enter key\n";
        if (cin >> close)
        {
            exit(2);
        }
    }
    else if (toYLoc == 0 && CMCheckersBoard[toYLoc][toXLoc] == REDSOLDIER)
    {
        CMCheckersBoard[toYLoc][toXLoc] = REDKING;
        return true;
    }
    if (ydistance == 2)
    {
        jumped = 1;
    }
    return true;
}

bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
    //This will check who has won the game when there is a winner
    int i = 0;
    int j = 0;
    int whiteMuleCounter = 0;
    int redMuleCounter = 0;
    int whiteSoldierCounter = 0;
    int redSoldierCounter = 0;
    int whiteKingCounter = 0;
    int redKingCounter = 0;
    
    for (i = 0; i < numRowsInBoard; i++)
    {
        for (j = 0; j < numRowsInBoard; j++)
        {
            if (CMCheckersBoard[i][j] == WHITEMULE)
            {
                whiteMuleCounter++;
            }
            else if (CMCheckersBoard[i][j] == WHITESOLDIER)
            {
                whiteSoldierCounter++;
            }
            else if (CMCheckersBoard[i][j] == WHITEKING)
            {
                whiteKingCounter++;
            }
            else if (CMCheckersBoard[i][j] == REDMULE)
            {
                redMuleCounter++;
            }
            else if (CMCheckersBoard[i][j] == REDSOLDIER)
            {
                redSoldierCounter++;
            }
            else if (CMCheckersBoard[i][j] == REDKING)
            {
                redKingCounter++;
            }
        }
    }
    
    if (redMuleCounter == 0)
    {
        cout << "The Red Player has won the game by losing all of the Red Mules" << endl;
        return true;
    }
    else if (whiteMuleCounter == 0)
    {
        cout << "The White Player has won the game by losing all of the White Mules" << endl;
        return true;
    }
    else if (whiteMuleCounter != 0 && whiteSoldierCounter == 0 && whiteKingCounter == 0)
    {
        cout << "The Red Player has won by capturing all of the white players soldiers and kings" << endl;
        return true;
    }
    else if (redMuleCounter != 0 && redSoldierCounter == 0 && redKingCounter == 0)
    {
        cout << "The White Player has won by capturing all of the red players soldiers and kings" << endl;
        return true;
    }
    else
    {
        return false;
    }
}

