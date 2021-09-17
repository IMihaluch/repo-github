#include <iostream>
#include <string>

using namespace std;

//===========================================================================================================//
//PART-1. Написать шаблонную функцию div, которая должна вычислять результат деления двух параметров и      //
//запускать исключение DivisionByZero, если второй параметр равен 0. В функции main выводить результат     //
//вызова функции div в консоль, а также ловить исключения.                                                //
//=======================================================================================================//

class DivisionByZero
{
private:
	string prevent_ex;
public:
	DivisionByZero(string prevent = "") : prevent_ex(prevent) {}
	const string& getPrevent() const { return prevent_ex; }
};

namespace dbz
{
	template <typename T>
		double div(T a, T b)
	{
		if (b == 0)
			throw DivisionByZero("Division by zero!");
		return a / b;
	}
}

void part_1()
{
	try
	{
		double calculate = dbz::div(10, 0);
		cout << calculate << endl;
	}
	catch (const DivisionByZero& ex)
	{
		cerr << ex.getPrevent() << endl;
	}
}

//==================================================================================================================//
//PART-2. Написать класс Ex, хранящий вещественное число x и имеющий конструктор по вещественному числу, инициализирующий  //
//x значением параметра. Написать класс Bar, хранящий вещественное число y (конструктор по умолчанию инициализирует// 
//его нулем) и имеющий метод set с единственным вещественным параметром a. Если y + a > 100, возбуждается         //
//исключение типа Ex с данными a*y, иначе в y заносится значение a. В функции main завести переменную класса     //
//Bar и в цикле в блоке try вводить с клавиатуры целое n. Использовать его в качестве параметра метода set      //
//до тех пор, пока не будет введено 0. В обработчике исключения выводить сообщение об ошибке, содержащее       //
//данные объекта исключения.                                                                                  //
//===========================================================================================================//
class Ex
{
public:
	double x_pos;
	Ex(double x) : x_pos(x) {};
};

class Bar
{
private:
	double y_pos;
public:
	Bar(double y = 0.0) : y_pos(y) {}
	void set(double a)
	{
		if ((y_pos + a) > 100)
			throw Ex(a * y_pos);
		else
			y_pos = a;
	}
};

void part_2()
{
	Bar a;
	int y;
	try
	{
		while (true)
		{
			cout << "Enter the n (if n=0 end!): ";
			cin >> y;
			if (y == 0)
				break;
			a.set(y);
		}
	}
	catch (const Ex& i)
	{
		cout << i.x_pos << endl;
	}
}
//=========================================================================================================//
//PART-3. Написать класс «робот», моделирующий перемещения робота по сетке 10x10, у которого есть метод,  //
//означающий задание переместиться на соседнюю позицию. Эти методы должны запускать классы-исключения    //
//OffTheField, если робот должен уйти с сетки, и IllegalCommand, если подана неверная команда (направление //
//не находится в нужном диапазоне). Объект исключения должен содержать всю необходимую информацию — текущую//
//позицию и направление движения. Написать функцию main, пользующуюся этим классом и перехватывающую все  //
//исключения от его методов, а также выводящую подробную информацию о всех возникающих ошибках.          //
//======================================================================================================//

class OffTheField
{
	int cur_posX;
	int cur_posY;
	int rou_posX;
	int rou_posY;
	string m_msg;
public:
	OffTheField(int c_x, int c_y, int r_x, int r_y) :
		cur_posX(c_x), cur_posY(c_y), rou_posX(r_x), rou_posY(r_y), m_msg("")
	{
		if (rou_posX > 10 || rou_posX < 1)
		{
			m_msg += "X coordinate error! The robot goes out of the field!\n";
			m_msg += '[' + to_string(cur_posX) + ';' + to_string(cur_posY) + "] => [" +
				to_string(rou_posX) + ';' + to_string(rou_posY) + "]\n";
		}
		if (rou_posY > 10 || rou_posY < 1)
		{
			m_msg += "Y coordinate error! The robot goes out of the field!\n";
			m_msg += '[' + to_string(cur_posX) + ';' + to_string(cur_posY) + "] => [" +
				to_string(rou_posX) + ';' + to_string(rou_posY) + "]\n";
		}
	}
	const string& getInfo() const
	{
		return m_msg;
	}
};

class IllegalCommand
{
private:
	int cur_posX;
	int cur_posY;
	int rou_posX;
	int rou_posY;
	string m_msg;
public:
	IllegalCommand(int c_x, int c_y, int r_x, int r_y) :
		cur_posX(c_x), cur_posY(c_y), rou_posX(r_x), rou_posY(r_y), m_msg("")
	{
		if (abs(cur_posX - rou_posX) > 1)
		{
			m_msg += "X coordinate error! The step is too big!\n";
			m_msg += '[' + std::to_string(cur_posX) + ';' + to_string(cur_posY) + "] => [" +
				to_string(rou_posX) + ';' + to_string(rou_posY) + "]\n";
		}
		if (abs(cur_posY - rou_posY) > 1)
		{
			m_msg += "Y coordinate error! The step is too big!\n";
			m_msg += '[' + to_string(cur_posX) + ';' + to_string(cur_posY) + "] => [" +
				to_string(rou_posX) + ';' + to_string(rou_posY) + "]\n";
		}
		if (cur_posX == rou_posX && cur_posY == rou_posY)
		{
			m_msg += "Error of the X and Y coordinates! You can't step into the current place!\n";
			m_msg += '[' + to_string(cur_posX) + ';' + to_string(cur_posY) + "] => [" +
				to_string(rou_posX) + ';' + to_string(rou_posY) + "]\n";
		}
	}
	const string& getInfo() const
	{
		return m_msg;
	}
};

class Robot
{
private:
	int posX;
	int posY;
public:
	Robot(int x = 5, int y = 5) : posX(x), posY(y)
	{
		cout << "The initial position of the robot: [" << posX << ';' << posY << ']' << endl;
	}

	void move(int x, int y)
	{
		if (abs(posX - x) > 1 || abs(posY - y) > 1 || (posX == x && posY == y))
			throw IllegalCommand(posX, posY, x, y);
		if (x > 10 || x < 1 || y > 10 || y < 1)
			throw OffTheField(posX, posY, x, y);
		cout << "Robot moved from position [" << posX << ';' << posY << "] to a position [" << x << ';' << y << ']' << endl;

		posX = x;
		posY = y;
	}
};

void part_3()
{
	int x = 0;
	int	y = 0;
	Robot r;

	while (true)
	{
		cout << "Enter the x: ";
		cin >> x;
		cout << "Enter the y: ";
		cin >> y;

		if (x == 0 && y == 0)
			break;
		try
		{
			r.move(x, y);
		}
		catch (const IllegalCommand& e)
		{
			cerr << e.getInfo() << endl;
		}
		catch (const OffTheField& e)
		{
			cerr << e.getInfo() << endl;
		}
	}
}
int main()
{
	cout << endl << "PART-1.\n=====================================================" << endl << endl;
	{
		cout << "10/0= ";
		
		part_1();
	}
	cout << endl << "PART-2.\n=====================================================" << endl << endl;
	{
		part_2();
	}
	cout << endl << "PART-3.\n=====================================================" << endl << endl;
	{
		part_3();
	}
	return 0;
}
