#include <cstring>
#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;
//==============================================================================================================//
// PART-4. Создать класс Card, описывающий карту в игре БлэкДжек.У этого класса должно быть три поля :         //
//масть, значение карты и положение карты (вверх лицом или рубашкой). Сделать поля масть и значение           //
//карты типом перечисления (enum). Положение карты - тип bool. Также в этом классе должно быть два метода:    //
//	-метод Flip(), который переворачивает карту, т.е. если она была рубашкой вверх, то он ее поворачивает лицом //
//  вверх, и наоборот.                                                                                           //
//	-метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1.                      //
//==============================================================================================================//
enum Suit { Spades, Hearts, Diamonds, Clubs, Trump };
enum Value {
    Ace = 11, King = 10, Queen = 10, Jack = 10, Ten = 10,
    Nine = 9, Eight = 8, Seven = 7, Six = 6, Five = 5,
    Four = 4, Three = 3, Two = 2
};
class Card
{
private:
    Value value;
    Suit suit;
    bool state;
public:
    Card(Value val, Suit su, bool sta = 0) : value(val), suit(su), state(sta) { }
    void Flip() { state =!state; }
    
    int GetValue()
    {
        if (value == Ace);
        return((int)value > 10 ? 1 : (int)value); // считаем что перебор и туз не == 11 а == 1
    }
    ~Card() { }
};
int main()
{
    Card card1(Three, Trump);
    Card card2(King, Hearts);
    Card card3(Ace, Spades);
    int sum = card1.GetValue() + card2.GetValue() + card3.GetValue();
    cout << "Three + King + Ace = " << sum << " \n" << endl;


    return 0;
}
