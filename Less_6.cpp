#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>  

using namespace std;

enum Suit { Spades, Hearts, Diamonds, Clubs, Trump };
enum Value { Zero, Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };

class Card
{
protected:
    Value value;
    Suit suit;
    bool stateopen;
public:
    Card(Value val, Suit su, bool staopen = true) : value(val), suit(su), stateopen(staopen) { }
    void Flip() { stateopen = !stateopen; }
    int GetValue() const
    {
        if (stateopen)
            return value;
        else
            return 0;
    }
    friend ostream& operator << (ostream& out, const Card& acard);
    ~Card() { }
};

class Hand
{
protected:
    vector<Card*>m_Cards;
public:
    Hand() { }
    virtual ~Hand()
    {
        Clear();
    }
    void add(Card* pCard)
    {
        m_Cards.push_back(pCard);
    }
    void Clear()
    {
        if (m_Cards.empty())
            return;
        else
        {
            for (int index = 0; index < m_Cards.size(); index++)
            {
                delete m_Cards[index];
                m_Cards[index] = nullptr;
            }
            m_Cards.resize(0);
        }
    }
    int GetTotal() const
    {
        int verify = 0;
        int sum = 0;
        for (int index = 0; index < m_Cards.size(); index++)
        {
            if (m_Cards[index]->GetValue() > 10) {
                
            sum += 10;
        } 
          else
          {
            sum += m_Cards[index]->GetValue();
          }
            if (m_Cards[index]->GetValue() == Ace)
                verify++;
        }
        while (verify > 0)
        {
            if (sum + 10 <= 21 && verify == 1)
            {
                sum += 10;
            }
            verify--;
        }
        return sum;
    }
};

class GenericPlayer : public Hand
{
protected:
    string m_name;
public:
    GenericPlayer(string name = " ") : m_name(name) { };
    virtual ~GenericPlayer() {}
    virtual bool IsHitting() const = 0;

    bool Is_Busted() const
    {
        return (GetTotal() > 21);
    }
    void Bust() const
    {
        cout << "A player  " << m_name << " Bust!" << endl;
    }
    friend ostream& operator<< (ostream& out, const GenericPlayer& aGenericPlayer);
};
//==============================================================================================================//
//PART-1. Создать программу, которая считывает целое число типа int.И поставить «защиту от дурака» :           //
//если пользователь вводит что - то кроме одного целочисленного значения, нужно вывести сообщение об ошибке   //
//и предложить ввести число еще раз.                                                                         //
//==========================================================================================================//
void notcharone()
{
    int num;
    cout << "Enter number: ";
    while (true)
    {
        cin >> num;
        if (cin.good() && cin.peek() == '\n')
        {
            cin.ignore(9223372036854775807, '\n');
            break;
        }
        cin.clear();
        cout << "Error! The values for example: a-z, 1a-1z, 1.1 are incorrect!\nEnter number again: ";
        cin.ignore(9223372036854775807, '\n');
    }
    cout << "Correctly! " << num << " is integer:)\n " << endl;
}
//==================================================================================================================//
//PART-2.Создать собственный манипулятор endll для стандартного потока вывода, который выводит два перевода строки //
//и сбрасывает буфер.                                                                                             //
//===============================================================================================================//
class endline
{
public:
    friend ostream& operator<<(ostream& out, const endline&);
};
ostream& operator<<(ostream& out, const endline&)
{
    out << "\n\n";
    out.flush();
    return out;
}
endline myendl;
//============================================================================================================//
//PART-3. Реализовать класс Player, который наследует от класса GenericPlayer. У этого класса будет 4 метода://
// virtual bool IsHitting() const - реализация чисто виртуальной функции базового класса.                   //
// Метод спрашивает у пользователя, нужна ли ему еще одна карта и возвращает ответ пользователя в виде true//
// или false.                                                                                             //
// void Win() const - выводит на экран имя игрока и сообщение, что он выиграл.                           //
// void Lose() const - выводит на экран имя игрока и сообщение, что он проиграл.                        //
// void Push() const - выводит на экран имя игрока и сообщение, что он сыграл вничью.                  //
//====================================================================================================//

class Player : public GenericPlayer
{
public:
    Player(const string& name = "") : GenericPlayer(name) { }

    ~Player() { };
    virtual bool IsHitting() const
    {
        char response;
        cout << m_name << ", would you like another card? (Y/N): ";
        cin >> response;
        return (response == 'y' || response == 'Y');
    }
    void Win() const
    {
        cout << m_name << " Wins.\n";
    }
    void Lose() const
    {
        cout << m_name << " Loses.\n";
    }
    void Push() const
    {
        cout << m_name << " Pushes.\n";
    }
};
//=================================================================================================================================================//
//PART-4.Реализовать класс House, который представляет дилера. Этот класс наследует от класса GenericPlayer. У него есть 2 метода:                //
//virtual bool IsHitting() const - метод указывает, нужна ли дилеру еще одна карта.Если у дилера не больше 16 очков, то он берет еще одну карту. //
//void FlipFirstCard() - метод переворачивает первую карту дилера.                                                                              //
//=============================================================================================================================================//
class House : public GenericPlayer
{
public:
    House(const string& name = "House") : GenericPlayer(name) { }
    virtual ~House() { }
    virtual bool IsHitting() const
    {
        return (GetTotal() <= 16);
    }
    void FlipFirstCard()
    {
        if (!(m_Cards.empty()))
            m_Cards[0]->Flip();
        else
            cout << "No card to flip!\n";
    }
    friend ostream& operator<< (const ostream& out, const GenericPlayer& aGenericPlayer);
};

//=========================================================================================================//
//PART-5. Написать перегрузку оператора вывода для класса Card. Если карта перевернута рубашкой вверх     //
//(мы ее не видим), вывести ХХ, если мы ее видим, вывести масть и номинал карты. Также для класса        //
//GenericPlayer написать перегрузку оператора вывода, который должен отображать имя игрока и его карты, //
//а также общую сумму очков его карт.                                                                  //
//====================================================================================================//
ostream& operator<<(ostream& out, const Card& acard)
{
    const string suit_name[] = { "Spades", "Hearts", "Diamonds", "Clubs", "Trump" };
    const string value_name[] = { "0", "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
    if (acard.stateopen) {
        out << value_name[acard.value] <<" "<< suit_name[acard.suit];
    }
    else {
        out << "XX";
         }
     
    return out;
};

ostream& operator<<(ostream& out, const GenericPlayer& aGenericPlayer)
{
    out << aGenericPlayer.m_name << ":\t";

    vector<Card*>::const_iterator pCard;
    if (!aGenericPlayer.m_Cards.empty())
    {
        for (pCard = aGenericPlayer.m_Cards.begin();
            pCard != aGenericPlayer.m_Cards.end();
            ++pCard)
        {
            out << *(*pCard) << "\t";
        }
        if (aGenericPlayer.GetTotal() != 0)
        {
            cout << "(" << aGenericPlayer.GetTotal() << ")";
        }
    }
    else
    {
       out << "<empty>";
    }
    return out;
}

int main()
{
    cout << endl << "PART-1.\n=====================================================" << endl << endl;
    {
        notcharone();
    }
    cout << endl << "PART-2.\n=====================================================" << endl << endl;
    cout << "New " << myendl << "line";

    cout << endl << "\nPART-5.\n=====================================================" << endl << endl;
    {
        Player one("Vika");
        Card card1(King, Clubs);
        Card card2(Eight, Trump);
        one.add(&card1);
        one.add(&card2);
        cout << one << endl;
    }
    return 0;
}
