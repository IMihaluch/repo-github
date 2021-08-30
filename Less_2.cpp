#include <iostream>
#include <cstring>

//===========================================================================================================//
//1.Создать класс Person(человек) с полями : имя, возраст, пол и вес.Определить методы переназначения имени,//
//  изменения возраста и веса.Создать производный класс Student(студент), имеющий поле года обучения.      //
// Определить методы переназначения и увеличения этого значения.Создать счетчик количества созданных      //
// студентов.В функции main() создать несколько студентов.По запросу вывести определенного человека.     //
//======================================================================================================//

using namespace std;

class Person 
{

public:
    string name;
    int age;
    double weight;
    const string gender;


 public:
    Person(const string gender, string name, int age = 0, double weight = 0) : name(name), age(age), gender(gender), weight(weight) { }

    void set_Name(string name) { name = name; }
    string getName() const { return name; }

    void set_Age(int age) { age = age; }
    int getAge() const { return age; }

    void set_Weight(double weight) { weight = weight; }
    double getWeight() const { return weight; }
    
    ~Person() { }
};

class Student : public Person 
{

public:
    Student(const string gender = " ", string name = " ", int age = 0, double weight = 0, int year = 0) : Person(gender, name, age, weight), yearStudy(year)
    {
        counter++;
    }
    void set_YearStudy(int year) { yearStudy = year; }
    
    
    void increaseYS() 
    { 
        yearStudy++; 
    }

public:

    static int counter;
    int yearStudy;

    ~Student() {}
    
};

int Student::counter = 0;


void print(const Student& student)
{
   cout << "Name: " << student.name << "\n" << "Gender: " << student.gender << "\n" << "Age: " << student.age << " years\n" <<
       "Weight: " << student.weight << "\n" << "Year education: " << student.yearStudy << " year." << endl;

}

//==============================================================================================================//
//PART-2.Создать классы Apple(яблоко) и Banana(банан), которые наследуют класс Fruit(фрукт).У Fruit есть две    //
//переменные - члена : name(имя) и color(цвет).Добавить новый класс GrannySmith, который наследует класс Apple.//
//============================================================================================================//

class Fruit
{
protected:
    string name;
    string color;
public:
    Fruit(string name, string color) : name(name), color(color) { }
    
    string getName() const { return name; }
    string getColor() const { return color; }
    ~Fruit() { }
};
class Apple : public Fruit
{
public:
    Apple(string color) : Fruit("apple", color) { }
    ~Apple() { }
};
class Banana : public Fruit
{
public:
    Banana() : Fruit("banana", "yellow") { }
    ~Banana() { }
};

class GrannySmith : public Apple
{
public:
    GrannySmith() : Apple("green") { }
    string getName() 
    {
        return "GrannySmith ";
    }
    ~GrannySmith() { }
};
int main() 
{
    cout << endl << "PART-1. ===================================================" << endl << endl; 
    {
        Student Ivan("male");
        Ivan.set_Name("Petrov Ivan Mihailovich");
        Ivan.set_Age(23);
        Student Mihail("male", "Zorov Mihail Konstantinovich", 37, 81, 2021);
        Student Marina("female", "Nikitenko Marina Vladimirovna", 41);
        Marina.set_YearStudy(1998);

        print(Mihail);
    }
    cout << endl << "PART-2. ===================================================" << endl << endl; 
    {
        Apple a("red");
        Banana b;
        GrannySmith c;
        std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
        std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
        std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";
    }
    
    return 0;
}
