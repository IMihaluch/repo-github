#include <cstring>
#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
using namespace std;

//PART-1.	Создать абстрактный класс Figure (фигура). Его наследниками являются классы Parallelogram (параллелограмм)//
//и Circle (круг). Класс Parallelogram — базовый для классов Rectangle (прямоугольник), Square (квадрат),//
//Rhombus (ромб). Для всех классов создать конструкторы. Для класса Figure добавить чисто виртуальную функцию area()//
//(площадь). Во всех остальных классах переопределить эту функцию, исходя из геометрических формул нахождения площади.//
class Figure
{
public:
    virtual double area() const = 0;
protected:
    const double P = 3.1415926535897932384626433832795;
};
class Parallelogram : public Figure
{
public:
