// Задание 1
#include <iostream>
int main (int argc, const char** argv)
{
  int arr[]={1, 1, 0, 0, 1, 0, 1, 1, 0, 0};
  for(int i = 0; i < 10; i++)
  {
    arr[i] = arr[i] - 1;
    printf(" - %d ", arr[i] );
  }
}


//Задание 2
#include <iostream>
int main (int argc, const char** argv)
{
  int arr[8];
  for(int i = 0; i < 8;)
  {
    arr[i] = ++i;
    arr[i] = arr[i] + - 2 + arr[i] + arr[i];
    printf("%d ", arr[i] );
  }
}
