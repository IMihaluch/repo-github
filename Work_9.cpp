#include "Qlist.h"
#define T char


typedef struct {
    int pr;
    int dat;
} Node;

Node* arr[SZ];
int head;
int tail;
int items;

void init() {
    for (int i = 0; i < SZ; i++) {
        arr[i] = nullptr;
    }
    head = 0;
    tail = 0;
    items = 0;
}

void printQue() {

    for (int i = 0; i < SZ; i++) {
        if (arr[i] == nullptr) {
            printf("[* , *]");
        }
        else {
            printf("[%d, %d] ", arr[i]->pr, arr[i]->dat);
        }

    }

}

    ///===========================================///
   /// Описать очередь с приоритетным исключением///
  ///===========================================///

void ins(int pr, int dat) {
    Node* element = (Node*)malloc(sizeof(Node));
    element->pr = pr;
    element->dat = dat;

    if (items == SZ) {
        printf("%s \n", "\nQueue is full!");
        return;
    }

    arr[tail++ % SZ] = element;
    items++;
}

Node* rem() {
    if (items == 0) {
        printf("%s \n","Queue is empty!");
        return nullptr;
    }
    else if (items == 1) {
        int indx = head++ % SZ;
        Node* temp = arr[indx];
        arr[indx] = nullptr;
        items--;
        return temp;
    }
    else {
        int i, index;

        for (int k = 1; k <= SZ; k++) {
            for (i = head; i < tail; i++) {
                index = i % SZ;

                if (arr[index]->pr == k) {
                    Node* temp = arr[index];
                    Node* swap;

                    while (i > head) {
                        index = i % SZ;
                        swap = arr[index];
                        arr[index] = arr[index - 1];
                        arr[index - 1] = swap;
                        i--;
                    }
                    arr[head] = nullptr;
                    items--;
                    head++;
                    return temp;
                }
            }
        }

    }
}

     ///======================================================================================///
    /// Реализовать перевод из десятичной в двоичную систему счисления с использованием стека///
   ///======================================================================================///
typedef int boolean;

T stack[SIZE] = { 0 };
int cursor = -1;

boolean push(T data) {
    if (cursor < SIZE) {
        stack[++cursor] = data;
        return true;
    }
    else {
        printf("%s \n", "Stack overflow!");
        return false;
    }
}

T pop() {
    if (cursor != -1) {
        return stack[cursor--];
    }
    else {
        printf("%s \n","Stack is empty!");
    }
}
void bynary(T n) {
    printf("Binary from of number %d =", n);

    if (n == 0) {
        printf("%d", 0);

    }

    while (n > 0) {
        push(n % 2);
        n /= 2;
    }

    while (cursor != -1) {
        printf("%2d", pop());
    }

}
int main(const int argc, const char** argv) {
      ///===========================================///
     /// Описать очередь с приоритетным исключением///
    ///===========================================///
    printf("PART-1 ===============================================\n");

    init();
    printQue();
    ins(5, 16);
    ins(1, 14);
    ins(2, 10);
    ins(4, 13);
    ins(6, 11);
    ins(3, 17);
    ins(7, 15);
    ins(1, 12);
    printQue();
    rem();
    rem();
    rem();
    rem();
    printQue();
    ins(1, 13);
    ins(3, 12);
    ins(7, 10);
    ins(6, 14);
    ins(1, 14);
    ins(2, 17);
    ins(7, 16);
    ins(4, 11);
    printQue();
     ///======================================================================================///
    /// Реализовать перевод из десятичной в двоичную систему счисления с использованием стека///
   ///======================================================================================///
    printf("\nPART-2 ===========================================");

    int num;

    printf("\n Enter number: ");
    scanf_s("%d", &num);
    printf("\n");

    bynary(num);
    printf("\n");
    system("pause");
    return 0;
}
