#include <iostream>
#include <vector>
using namespace std;

void displayBoard(const vector<vector<bool>> &board)
{
    for (const auto &row : board)
    {
        for (bool cell : row)
        {
            if (cell)
                cout << "Q ";
            else
                cout << "* ";
        }
        cout << endl;
    }
    cout << endl;
}

int queensBT(vector<vector<bool>> &board, int row, int n)
{
    if (n == row)
    {
        displayBoard(board);
        cout << endl;
        return 1;
    }

    int count = 0;

    for (int col = 0; col < n; col++)
    {
        bool isSafe = true;

        for (int i = 0; i < row; i++)
        {
            if (board[i][col])
            {
                isSafe = false;
                break;
            }
        }

        int leftshift = min(row, col);
        for (int i = 1; i <= leftshift; i++)
        {
            if (board[row - i][col - i])
            {
                isSafe = false;
                break;
            }
        }

        int rightShift = min(row, n - col - 1);
        for (int i = 1; i <= rightShift; i++)
        {
            if (board[row - i][col + i])
            {
                isSafe = false;
                break;
            }
        }

        if (isSafe)
        {
            board[row][col] = true;
            displayBoard(board);
            count += queensBT(board, row + 1, n);
            board[row][col] = false;
        }
    }

    return count;
}

int cnt = 1;
void queensBNB(vector<vector<bool>> &board, int row, vector<bool> &colAttacked, vector<bool> &leftDiagonalAttacked, vector<bool> &rightDiagonalAttacekd, int n)
{
    if (n == row)
    {
        cout << "Final Arrangement: " << cnt << endl;
        cnt++;
        displayBoard(board);
        return;
    }

    for (int col = 0; col < n; col++)
    {
        if (!colAttacked[col] && !leftDiagonalAttacked[row + col] && !rightDiagonalAttacekd[row - col + n - 1])
        {
            board[row][col] = true;
            colAttacked[col] = true;
            leftDiagonalAttacked[row + col] = true;
            rightDiagonalAttacekd[row - col + n - 1] = true;

            queensBNB(board, row + 1, colAttacked, leftDiagonalAttacked, rightDiagonalAttacekd, n);

            board[row][col] = false;
            colAttacked[col] = false;
            leftDiagonalAttacked[row + col] = false;
            rightDiagonalAttacekd[row - col + n - 1] = false;
        }
    }
}

void backTrackQueen(int n)
{
    vector<vector<bool>> board(n, vector<bool>(n, false));
    int noOfPossibleSol = queensBT(board, 0, n);
    cout << noOfPossibleSol;
}

void branchAndBound(int n)
{
    vector<vector<bool>> board(n, vector<bool>(n, false));
    vector<bool> colAttacked(n, false);
    vector<bool> leftDiagonalAttacked(2 * n - 1, false);
    vector<bool> rightDiagonalAttacekd(2 * n - 1, false);
    queensBNB(board, 0, colAttacked, leftDiagonalAttacked, rightDiagonalAttacekd, n);
}

int main()
{
    int noOfQueens;
    cout << "Enter the Number of Queens: ";
    cin >> noOfQueens;

    while (true)
    {
        cout << "\n1. Brack-Track\n";
        cout << "2. Branch and Bound\n";
        cout << "3. Exit\n";

        int ch;
        cout << "\nEnter Your Choice: ";
        cin >> ch;

        if (ch == 1)
        {
            backTrackQueen(noOfQueens);
        }

        else if (ch == 2)
        {
            branchAndBound(noOfQueens);
        }

        else if (ch == 3)
        {
            break;
        }

        else
        {
            break;
        }
    }

    return 0;
}
