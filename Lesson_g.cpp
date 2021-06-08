


#include <iostream>

#define MIN_VALUE 0    


int main ()
{
    int x = 9;
    int MAX_VALUE = 9;
    scanf ("%d", &x);
    printf ("Number %d is inside range %d...%d :  %d  \n", x,
      MIN_VALUE, MAX_VALUE, MIN_VALUE <= x && x < MAX_VALUE);
       
    return 0;
}



#include <iostream>

#define ROWS 10
#define COLS 20

int main(void) {
    int** arr = new int*[ROWS];
    for(int j = 0; j < ROWS; ++j)
    arr[j] = new int[COLS];
    
    int** ptr = (int**)arr;
    int** end = (int**)arr + ROWS;
    
    int* e;
    while(ptr !=end) {
        e = (int*)*ptr + COLS; 
        for(int* i = *ptr; i != e; )
        *i++ = 0;
        ++ptr;
    }
    for(int r = 0; r < ROWS; ++r)
    delete[] arr[r];
    delete[] arr;
    return 0;
}
