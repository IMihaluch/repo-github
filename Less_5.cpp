#include <iostream>
#include <vector>
#include <cstring>
#include <cassert>

using namespace std;
//===============================================================================================================//
//PART -1. Реализовать шаблон класса Pair1, который позволяет пользователю передавать данные одного типа парами.//
//=============================================================================================================//
template <class T>
class Pair1
{
private:
    T element_f;
    T element_s;
public:
    Pair1(T first, T second) : element_f(first), element_s(second) {  }
    const T first();
    const T second();
 };
template <class T>
    const T Pair1<T>::first() 
    { return element_f; }
template <class T>
    const T Pair1<T>::second() 
    { return element_s; }
   
//========================================================================================================//
//PART -2.Реализовать класс Pair, который позволяет использовать разные типы данных в передаваемых парах.//
//======================================================================================================//
template <class T, class T2>
class Pair
{
private:
    T element_f;
    T2 element_s;
public:
    Pair(T first, T2 second) : element_f(first), element_s(second) {  }
    const T first();
    const T2 second();
};
template <class T, class T2>
    const T Pair<T, T2>::first()
    {return element_f;}
template <class T, class T2>
    const T2 Pair<T, T2>::second()
    {return element_s;}
    
//==========================================================================================================//
//PART -3.Реализовать класс Pair, который позволяет использовать разные типы данных в передаваемых парах.  //
// Написать шаблон класса StringValuePair, в котором первое значение всегда типа string,                  //
// а второе — любого типа. Этот шаблон класса должен наследовать частично специализированный класс Pair, //
//======================================================================================================//


template <class T2>
class stringValuePair : public Pair <std::string, T2> 
{
public:
    stringValuePair(std::string first, T2 second) : Pair<std::string, T2>(first, second) { }
};
//=========================================================================================================================//
//PART -4. Согласно иерархии классов, которая представлена в методичке к уроку 3, от класса Hand наследует класс          //
// GenericPlayer, который обобщенно представляет игрока, ведь у нас будет два типа игроков - человек и компьютер.        //
// Создать класс GenericPlayer, в который добавить поле name - имя игрока. Также добавить 3 метода:                     //
//IsHitting() - чисто виртуальная функция, возвращает информацию, нужна ли игроку еще одна карта.                      //
//IsBoosted() - возвращает bool значение, есть ли у игрока перебор                                                    //
//Bust() - выводит на экран имя игрока и объявляет, что у него перебор.                                              //
//==================================================================================================================//
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
    bool stateopen;
public:
    Card(Value val, Suit su, bool staopen = 0) : value(val), suit(su), stateopen(staopen) { }
    void Flip() { stateopen = !stateopen; }
    int GetValue() const
    {
        if (stateopen)
            return value;
        else
            return 0;
    }
    ~Card() { }
};

class Hand
{
private:
    vector<Card*>m_Cards;
public:
    Hand() { }
    ~Hand() 
    { Clear(); }
    void Add(Card* pCard) 
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
            sum += m_Cards[index]->GetValue();
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
    virtual ~GenericPlayer();
    virtual bool IsHitting() const = 0;
   
        bool Is_Busted() const 
        {
            return (GetTotal() > 21);
        }
      void Bust() const
    {
        cout << "A player  " << m_name << " Bust!" << endl;
    }
};

int main() 
{
    cout << endl << "PART-1.\n=====================================================" << endl << endl;
    {
       Pair1<int> p1(6, 9);
       cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
       Pair1<double> p2(3.4, 7.8);
       cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
       
    }
    cout << endl << "PART-2.\n=====================================================" << endl << endl;
    {
        Pair<int, double> p1(6, 7.8);
        cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
        Pair<double, int> p2(3.4, 5);
        cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
    }
    cout << endl << "PART-3.\n=====================================================" << endl << endl;
    {
        stringValuePair<int> svp("Amazing", 7);
        std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
    }
    
    return 0;
}
