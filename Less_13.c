#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;

//================================================//
//PART1-1. обход в глубину с использованием стека//
//==============================================//

const int n = 12;
bool visitedR[n];
int stack[n];
int matrix[n][n] ={
     {0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0},
     {0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1},
     {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
     {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
     {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
     {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0},
     {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
     {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
     {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1},
     {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0}

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

int pop()
{
    if (position >= 0)
    {
        return stack[position--];
    }
}

int link[n] = { 0 };
void push()
{
    while (position >= 0)
    {
        int value;
        value = pop();
        cout << value << "- " << link[value] << endl;
    }
}

void reset1mas(int* arr, int size)
{
    for (int i = 0; i < size; i++) 
    {
        arr[i] = 0;
    }
}
int visitedD[n] = { 0 };
void DepthFirstTravUsaStack(int start)
{
    int next;
    visitedD[start] = 1;
    for (next = 0; next < n; next++) 
    {
        if (matrix[start][next] == 1) 
        {
            link[start]++;
            if (!visitedD[next]) 
            {
                DepthFirstTravUsaStack(next);
            }
        }
    }
    move(start);
}

//===============================================================================================//
//PART-2. Моделируем робот поисковой системы. Дан готовый простой граф с циклическими связями...// 
//=============================================================================================//

void TraversD(int start = 0) 
{
    int next;
    visitedD[start] = 1;
    for (next = 0; next < n; next++)
    {
        if (matrix[start][next] == 1)
        {
            link[next]++;
            if (!visitedD[next]) {
                TraversD(next);
            }
        }
    }
}

void Referchek()
{
    int host[n] = { 0 };
    int refer[n] = { 0 };

    for (int i = 0; i < n; i++) 
    {
        for (int a = 0; a < n; a++) 
        {
            if (matrix[i][a] == 1)
                link[i]++;
        }
    }
    for (int i = 0; i < n; i++) 
    {
        refer[i] = link[i];
        host[i] = i;
    }
    int mem1, mem2, adr;
    for (int i = 1; i < n; ++i) 
    {
        mem1 = host[i];
        mem2 = refer[i];
        adr = i - 1;
        while (adr >= 0 && refer[adr] > mem2)
        {
            refer[adr + 1] = refer[adr];
            host[adr + 1] = host[adr];
            adr--;
        }
        refer[adr + 1] = mem2;
        host[adr + 1] = mem1;
    }
    for (int i = n - 1; i >= 0; i--)
    {
        cout << host[i] << " - " << refer[i] << endl;
    }
    reset1mas(link, n);
    reset1mas(visitedD, n);
}

//=========================================================================================//
//PART-3. обход графа рекурсивной функцией(с подсчётом только смежных со стартовой вершин)//
//=======================================================================================//

void RecursiveTransition(int vertex, int& count)
{
    visitedR[vertex] = true;
    count++;
    std::cout << vertex + 1 << ' ';
    for (int i = 0; i < n; ++i)
    {
        if (matrix[vertex][i] != 0 && !visitedR[i])
        {
            RecursiveTransition(i, count);
        }
    }
}
int main() 
{
   cout << "PART-1. ====================================" << endl << endl;

    DepthFirstTravUsaStack(1);
    while (position >= 0)
    {
        cout << pop() << " ";
    }
    cout << endl;
    reset1mas(visitedD, n);
    reset1mas(link, n);

    DepthFirstTravUsaStack(7);
    while (position >= 0)
    {
        cout << pop() << " ";
    }
    cout << endl;
    reset1mas(visitedD, n);
    reset1mas(link, n);

    cout << endl;
    
    cout << "PART-2. ====================================" << endl << endl;

    DepthFirstTravUsaStack(3);
    push();
    reset1mas(link, n);
    reset1mas(visitedD, n);
    cout << endl;
    Referchek();

    cout << "PART-3. ====================================" << endl << endl;
     
    int apex;
    std::cout << "Input elements from 1 to 12): ";
    std::cin >> apex;

    std::cout << "Travers graph: ";
    int calc = -1;
    RecursiveTransition(apex - 1, calc);
    std::cout << endl;
    std::cout << "Number of adjacent vertices: " << calc << std::endl;
        
    return 0;
}
