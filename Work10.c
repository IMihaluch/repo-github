#include "Header.h"
using namespace std;
#define value 1

///Написать программу, которая определяет, является ли введенная скобочная последовательность правильной.
///Примеры правильных скобочных выражений : (), ([])(), {}(), ([{}]), 
/// неправильных — )(, ())({ ), (, ]) }), ([(]) для скобок[, (, { .

typedef struct Node
{
    char symb;
    struct Node* follow;
} Node;
typedef struct OLIntLst 
{
    int size;
    Node* head;
} OLIntLst;

void cleans(OLIntLst* lst, Node* part)
{
    if (lst->head == part)
    {
        lst->head = part->follow;
        lst->size--;
    }
    else 
    {
        Node* curent = lst->head;
        Node* last = nullptr;
        while (curent != part) 
        {
            last = curent;
            curent = curent->follow;
        }
        last->follow = curent->follow;
        lst->size--;
    }
}

void rem(OLIntLst* lst, Node* head) 
{
    if (lst->head == nullptr) 
    {
        return;
    }
    else if (head->follow == nullptr)
    {
        cleans(lst, head);
        return;
    }
    else {
        rem(lst, head->follow);
    }
}
void init(OLIntLst* lst)
{
    lst->head = nullptr;
    lst->size = 0;

}
void ins(OLIntLst* lst, char num)
{
    Node* nextNode = (Node*)malloc(sizeof(Node));
    if (nextNode == nullptr)
    {
        printf("Stack overflow\n");
        return;
    }
    nextNode->symb = num;
    nextNode->follow = nullptr;
    if (lst->head == nullptr)
    {
        lst->head = nextNode;
        lst->size++;
    }
    else {
        Node* current = lst->head;
        while (current->follow != nullptr)
        {
        current = current->follow;
        }
        current->follow = nextNode;
        lst->size++;
    }
}
bool CheckSequenceBrackets(std::string parss)
{
    OLIntLst* stack = (OLIntLst*)malloc(sizeof(OLIntLst));
    init(stack);
    int i = 0;
    while (parss[i])
    {
        if
            (parss[i] == '(')
            (parss[i] == ')') or
            (parss[i] == '[') or
            (parss[i] == ']') or
            (parss[i] == '{') or
            (parss[i] == '}');
        {
            int N = parss[i];
            ins(stack, N);
        }
        i++;
    }
        if (stack->size < value)
        {
        rem(stack, stack->head);
        return false;
        }
    else 
    {
       Node* curent = stack->head;
       while (curent->follow != nullptr)
        {
            if 
                ((curent->symb == '(' and curent->follow->symb == ')') or
                 (curent->symb == '[' and curent->follow->symb == ']' ) or
                 (curent->symb == '{' and curent->follow->symb == '}' ))
            {
                cleans(stack, curent->follow);
                cleans(stack, curent);
                if (stack->size < value) break;
                curent = stack->head;
                continue;
            }
            curent = curent->follow;
        }
        if (stack->size == 0)
        {
         return true;
        }
        else {
            rem(stack, stack->head);
         return false;
        }
    }
}
int main()
{
    printf("Enter the expression enclosed in parentheses. For example: (), ([])(), {}(), ([{}]):\n");
    std::string parentheses;
    getline(cin, parentheses);
    if (CheckSequenceBrackets(parentheses))
    {
        printf("The brackets are placed correctly\n");
    }
    else
    {
        printf("The brackets are positioned incorrectly!\n");
    }
    return 0;
}
