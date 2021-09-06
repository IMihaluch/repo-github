#include <vector>
#include <iostream>
#include <cstring>
#include <cassert>


using namespace std;

//1. Добавить в контейнерный класс, который был написан в этом уроке, методы:
//для удаления последнего элемента массива(аналог функции pop_back() в векторах)
//для удаления первого элемента массива(аналог pop_front() в векторах)
//для сортировки массива
//для вывода на экран элементов.
//2. Дан вектор чисел, требуется выяснить, сколько среди них различных.Постараться использовать максимально быстрый алгоритм.
//3.Реализовать класс Hand, который представляет собой коллекцию карт.В классе будет одно поле : вектор указателей карт(удобно использовать вектор, 
// т.к.это по сути динамический массив, а тип его элементов должен быть - указатель на объекты класса Card).Также в классе Hand должно быть 3 метода :
// метод Add, который добавляет в коллекцию карт новую карту, соответственно он принимает в качестве параметра указатель на новую карту
//метод Clear, который очищает руку от карт
//метод GetValue, который возвращает сумму очков карт руки(здесь предусмотреть возможность того, что туз может быть равен 11).

class  Arrayint 
{
private:
    int m_lenght;
    int *m_data;
public:
    Arrayint() : m_lenght(0), m_data(nullptr) { }
    Arrayint(int lenght) : m_lenght(lenght) {
        assert(lenght >= 0);

        if (lenght > 0)
            m_data = new int[lenght];
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
    void cleaner() 
    {
        for (int index = 0; index < m_lenght; index++) {
            m_data[index] = 0;
        }
    }
    int getlenght() { return m_lenght; }
    int& operator[] (int index) {
        assert(index >= 0 && index < m_lenght);
        return m_data[index];
    }
    void resize(int newlenght) 
    {
        if (newlenght == m_lenght)
            return;
        if (newlenght <= 0) {
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
    void push_back(int value) 
    {
        insertbefore(value, m_lenght); 
    }
    
