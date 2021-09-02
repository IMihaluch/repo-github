#include <cstring>
#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
using namespace std;
//==============================================================================================================//
//PART-1.	Создать абстрактный класс Figure (фигура). Его наследниками являются классы Parallelogram (параллелограмм)//
//и Circle (круг). Класс Parallelogram — базовый для классов Rectangle (прямоугольник), Square (квадрат),//
//Rhombus (ромб). Для всех классов создать конструкторы. Для класса Figure добавить чисто виртуальную функцию area()//
//(площадь). Во всех остальных классах переопределить эту функцию, исходя из геометрических формул нахождения площади.//
//==============================================================================================================//
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
    Parallelogram(double xw, double yw, double ang) : xway(xw), yway(yw), angle(ang) { }
    double area() const override
    {
        double angl = angle / 180.0 * P;
        return xway * yway * sin(angl);
    };
    virtual ~Parallelogram() { }
private:
    double xway;
    double yway;
    double angle;
};
class Circle : public Figure
{
public:
    Circle(double r) : rad(r) { }
    double area() const override
    {
        return P * rad * rad;
    }
private:
    double rad;
    ~Circle() { }
};
class Rectangle : public Parallelogram
{
public:
    Rectangle(double xw, double yw) : Parallelogram(xw, yw, 90) { }
    ~Rectangle() override { }
};
class Square : public Parallelogram
{
public:
    Square(double way) : Parallelogram(way, way, 90) { }
    ~Square() override { }
};
class Rhombus : public Parallelogram
{
public:
    Rhombus(double way, double angle) : Parallelogram(way, way, angle) { }
    ~Rhombus() override { }
};
//==============================================================================================================//
//PART-2.Создать класс Car (автомобиль) с полями company (компания) и model (модель). Классы-наследники: //
//PassengerCar (легковой автомобиль) и Bus (автобус). От этих классов наследует класс Minivan (минивэн).//
//Создать конструкторы для каждого из классов, чтобы они выводили данные о классах. Создать объекты для каждого//
//из классов и посмотреть, в какой последовательности выполняются конструкторы. Обратить внимание на проблему//
//«алмаз смерти». //
//==============================================================================================================//
class Car
{
public:
    Car() { }
    Car(string Co, string mod) :company(Co), model(mod) { cout << "Car- " << company << " " << model << endl; }
protected:
    string company;
    string model;
};
class PassengerCar : virtual public Car
{
public:
    PassengerCar() { cout << "Class- PassengerCar" << endl; }
    PassengerCar(string Co, string mod) : Car(Co, mod) { cout << "Class- PassengerCar" << endl;}
    ~PassengerCar() { }
};
class Bus : virtual public Car
{
public:
    Bus() { cout << "Class- Bus" << endl; }
    Bus(string Co, string mod) : Car(Co, mod) { cout << "Class- Bus" << endl;}
    ~Bus() { }
};
class Minivan : public PassengerCar, public Bus
{
public:
    Minivan(string Co, string mod) : Bus(Co, mod), PassengerCar(Co, mod), Car(Co, mod) {cout << "Class- Minivan" << endl;}
    ~Minivan() { }
};
int main()
{
    cout << endl << "PART-1. ===================================================" << endl << endl;
    {

            vector<Figure*> figure1, figure2, figure3, figure4, figure5;
            figure1.push_back(new Parallelogram(10, 5, 33));
            figure2.push_back(new Circle(10));
            figure3.push_back(new Rectangle(10, 5));
            figure4.push_back(new Square(11));
            figure5.push_back(new Rhombus(10, 33));
                   
                cout << "The area of the parallelogram: " << figure1[0]->area() << endl;
                cout << "The area of the circle: " << figure2[0]->area() << endl;
                cout << "The area of the rectangle: " << figure3[0]->area() << endl;
                cout << "The area of the square: " << figure4[0]->area() << endl;
                cout << "The area of the rhombus: " << figure5[0]->area() << endl;
            
             delete figure1[0];
             delete figure2[0];
             delete figure3[0];
             delete figure4[0];
             delete figure5[0];
              
    }
    cout << endl << "PART-2. ===================================================" << endl << endl;
        {
            Car car1("Shkoda", "Rapid"); cout;
            PassengerCar car2("KIA", "Sorento"); cout << endl;
            Bus car3("Skania", "Touring"); cout << endl;
            Minivan car4("Toyota", "Sienna"); cout << endl;
            Minivan car5("KIA", "Sedona"); cout << endl;
        }
    return 0;
}
