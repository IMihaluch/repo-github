#include <iostream>
#include <cstdlib>
#include <cstring>

int main(int argc, const char** argv) { 
    char letter;
    letter = 'X';
    bool b = true;
    printf("%d", letter);
   
    enum xo {x, o};
    using xo = enum xo;
    xo game =x;
    
    std::cout << 
