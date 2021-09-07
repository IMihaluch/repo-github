#include <vector>
#include <iostream>
#include <cstring>
#include <cassert>
#include <set>

using namespace std;
//=========================================================================================================================//
//PART-1. Добавить в контейнерный класс, который был написан в этом уроке, методы:                                        //
//для удаления последнего элемента массива(аналог функции pop_back() в векторах)                                         //
//для удаления первого элемента массива(аналог pop_front() в векторах)                                                  //
//для сортировки массива                                                                                               //
//для вывода на экран элементов.                                                                                      //
//===================================================================================================================//

class  Arrayint 
{
private:
    int m_lenght;
    int *m_data;
public:
    Arrayint() : m_lenght(0), m_data(nullptr) { }
    Arrayint(int lenght) : m_lenght(lenght)
    {
        assert(lenght >= 0);

        if (lenght > 0) 
        {
            m_data = new int[lenght];
            
        }
        else
            m_data = nullptr;
    }
    ~Arrayint() 
    {
        delete[] m_data;
    }
    
    void erase() 
    {
        delete[] m_data;
        m_data = nullptr;
        m_lenght = 0;
    }
    
    int getlenght() { return m_lenght; }
    int& operator[] (int index)
    {
        assert(index >= 0 && index < m_lenght);
        return m_data[index];
    }
    void resize(int newlenght) 
    {
        if (newlenght == m_lenght) return;
        if (newlenght <= 0)
        {
            erase();
            return;
        }

        int* data = new int[newlenght];

        if (m_lenght > 0) 
        {
            int elementsTocopy = (newlenght > m_lenght) ? m_lenght : newlenght;

            for (int index = 0; index < elementsTocopy; index++) {
                data[index] = m_data[index];
            }
        }

        delete[] m_data;
        m_data = data;
        m_lenght = newlenght;
    }
    void insertbefore(int value, int index)
    {
        assert(index >= 0 && index <= m_lenght);

        int* data = new int[m_lenght + 1];

        for (int before = 0; before < index; before++)
        {
            data[before] = m_data[before];
        }

        data[index] = value;

        for (int after = index; after < m_lenght; after++) 
        {
            data[after + 1] = m_data[after];
        }

        delete[] m_data;
        m_data = data;
        m_lenght++;
    }
    void push_back(int value) { insertbefore(value, m_lenght);}
    
    void pop_front()
        // по аналогии resize
    { 
        if (m_lenght == 0) return;
        if (m_lenght == 1) 
        {
            erase();
            return;
        }
        // по аналогии insertbefore
        int* data = new int[m_lenght - 1];

        for (int before = 1; before < m_lenght; before++)
        {
            data[before - 1] = m_data[before];
        }

        delete[] m_data;
        m_data = data;
        m_lenght--;
    }
    void change(int of, int to) 
    {
        int value = m_data[of];
        m_data[of] = m_data[to];
        m_data[to] = value;
   }
    void sort()
    {
        for (int i = 0; i < m_lenght; i++) 
        {
            for (int a = 0; a < m_lenght - 1 - i; a++)
            {
                if (m_data[a] > m_data[a + 1]) 
                {
                    change(a, a + 1);
                }
            }
        }
    }
    void pop_back() { resize(m_lenght - 1); }
    void push_front(int value) { insertbefore(value, 0); }
    void print()  
    {
        for (int print = 0; print < m_lenght; print++)
        {
            cout << "  " << m_data[print];
        }
            cout << endl;
    }
};

/// // PART-3.// ///

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
    int GetValue() 
    {
        if (value == Ace);
        return((int)value > 10 ? 1 : (int)value); // считаем что перебор и туз не == 11 а == 1
    }
    ~Card() { }
};
//=========================================================================================================================//
// PART-3. Реализовать класс Hand, который представляет собой коллекцию карт. В классе будет одно поле:                   //
// вектор указателей карт (удобно использовать вектор, т.к. это по сути динамический массив, а тип его элементов должен  //
//  быть - указатель на объекты класса Card). Также в классе Hand должно быть 3 метода:                                 //
//метод Add, который добавляет в коллекцию карт новую карту, соответственно он принимает в качестве параметра указатель// 
// на новую карту;                                                                                                     //
//метод Clear, который очищает руку от карт;                                                                             //
//метод GetValue, который возвращает сумму очков карт руки(здесь предусмотреть возможность того, что туз может быть равен 11).//
//===========================================================================================================================//

class Hand
{
private:
    vector<Card*>m_Cards; // Коллекция карт. Хранит указатели на объекты типа Сard
public:
    Hand() { }
    ~Hand() { }
    void Add(Card* pCard)  // Добавляем карту в руку и указатель на объект типа Сard в вектор m_Сards
    {
        m_Cards.push_back(pCard);
    }
    void Clear() // Очищаем руку от карт и Удаляем все указатели из вектора m_Сards, устраняя все связанные с ними объекты в куче
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
    int GetTotal()
    {
        int verify = 0;
        int sum = 0;
        for (int index = 0; index < m_Cards.size(); index++)
        {
            sum += m_Cards[index]->GetValue();
            if (m_Cards[index]->GetValue() == Ace)
                verify++;
        }
        while (verify > 0) {
            if (sum + 10 <= 21 && verify == 1)
            {
                sum += 10;
            }
            verify--;
        }
        return sum;
    }
};

int main( )
{

    cout << endl << "PART-1.\n=====================================================" << endl << endl;
    {
        Arrayint darry (9);
        
        //Доступ к элементам  массива
        darry[8] = 7;
        darry[2] = 5;
        darry[6] = 9;
        darry[4] = 1;
        darry[1] = 4;
        darry[0] = 8;
        darry[3] = 3;
        darry[5] = 2;
        darry[7] = 6;

        //для удаления последнего элемента массива (аналог функции pop_back()
        darry.pop_back();
        darry.print();

        //для удаления первого элемента массива (аналог pop_front() в векторах)
        darry.pop_front();
        darry.print();

        darry.push_back(8);
        darry.push_front(7);
        //для сортировки массива
        darry.sort();
        //для вывода на экран элементов.
        darry.print();
       
    }
cout << endl << "PART-2.\n=====================================================" << endl << endl;
//====================================================================================================================================//
// PART-2. Дан вектор чисел, требуется выяснить, сколько среди них различных. Постараться использовать максимально быстрый алгоритм. //
//==================================================================================================================================//
{
    vector<int> num = { 4, 5, 3, 3, 7, 7, 5, 9, 9 };
    cout << " There are numbers is: 4, 5, 3, 3, 7, 7, 5, 9, 9, " <<  endl;
    set<int> se(num.begin(), num.end());
    cout << " Total numbers: " << num.size() << endl;
    cout << " Unique numbers: " << se.size() << endl;
 }

return 0;
}

