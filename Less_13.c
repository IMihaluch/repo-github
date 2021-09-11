#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;

const int n = 7;
bool visitedR[n];
int stack[n];
int matrix[n][n] = {
     {0, 1, 1, 0, 0, 0, 1},
     {0, 0, 0, 1, 1, 1, 0},
     {0, 0, 0, 0, 0, 1, 0},
     {1, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 1, 0, 0},
     {0, 0, 0, 1, 0, 0, 0},
   
};

int position = -1;
bool move(int value)
{
    if (position < n)
    {
        stack[++position] = value;
        return true;
    }
    else {
        cout << "Stack over full!" << endl;
        return false;
    }
}
