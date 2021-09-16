#include <iostream>
using namespace std;
//==========================================================================================================//
//PART 1. Создайте класс Date с полями день, месяц, год и методами доступа к этим полям.                   //
//Перегрузите оператор вывода для данного класса. Создайте два "умных" указателя today и date.            //
//Первому присвойте значение сегодняшней даты. Для него вызовите по отдельности методы доступа к полям   //
//класса Date, а также выведите на экран данные всего объекта с помощью перегруженного оператора вывода.// 
//Затем переместите ресурс, которым владеет указатель today в указатель date. Проверьте, являются ли   //
//нулевыми указатели today и date и выведите соответствующую информацию об этом в консоль.            //
//===================================================================================================//
class Date
{
private:
	int day, month, year;
public:

	Date(int D, int M, int Y) : day(D), month(M), year(Y) {}
		const int& get_Day() const
	{
		return day;
	}
		const int& get_Month() const
	{
		return month;
	}
	const int& get_Year() const
	{
		return year;
	}
		friend std::ostream& operator<<(std::ostream& out, const Date& d)
	{
		out << d.day << '.' << '0' << d.month << '.' << d.year;
		return out;
	}
};

template <class T>
class Uptr
{
private:
	T* Mptr;
public:
	Uptr(T* ptr = nullptr) : Mptr(ptr) {}
	~Uptr() { delete Mptr; }

	Uptr(Uptr& u)
	{
		Mptr = u.Mptr;
		u.Mptr = nullptr;
	}

	Uptr& operator=(Uptr& u)
	{
		if (&u == this)
			return *this;

		delete Mptr;
		Mptr = u.Mptr;
		u.Mptr = nullptr;

		return *this;
	}

	T& operator*() const { return *Mptr; }
	T* operator->() const { return Mptr; }

	bool zero() const { return Mptr == nullptr; }
};

const Uptr<Date>& compares_dates(const Uptr<Date>&, const Uptr<Date>&);
//PART 1
void part_1()
{
	Uptr<Date> today(new Date(16, 9, 2021));

	cout << "Day: " << today->get_Day() << endl;
	cout << "Month: "<<'0' << today->get_Month() << endl;
	cout << "Year: " << today->get_Year() << endl;
	cout << "today: " << *today << endl;

	Uptr<Date> date;

	cout << "today is " << (today.zero() ? "zero value\n" : "not zero value\n");
	cout << "date is " << (date.zero() ? "zero value\n" : "not zero value\n");

	date = today;

	cout << "today is " << (today.zero() ? "zero value\n" : "not zero value\n");
	cout << "date is " << (date.zero() ? "zero value\n" : "not zero value\n");

	cout << "date: " << *date << endl;
}
const Uptr<Date>& compares_dates(const Uptr<Date>& a, const Uptr<Date>& i)
{
	if (a->get_Year() > i->get_Year())
		return a;
	else if (a->get_Year() < i->get_Year())
		return i;
	else
	{
		if (a->get_Month() > i->get_Month())
			return a;
		else if (a->get_Month() < i->get_Month())
			return i;
		else
		{
			if (a->get_Day() > i->get_Day())
				return a;
			else
				return i;
		}
	}
}

void swap_dates(Uptr<Date>& a, Uptr<Date>& i)
{
	Uptr<Date> temp(a);
	a = i;
	i = temp;
}

//========================================================================================================//
//PART-2. По условию предыдущей задачи создайте два умных указателя date1 и date2.                       //
//Создайте функцию, которая принимает в качестве параметра два умных указателя типа Date                //
//и сравнивает их между собой(сравнение происходит по датам).Функция должна вернуть более позднюю дату.//
//Создайте функцию, которая обменивает ресурсами(датами) два умных указателя, переданных в функцию в  //
//качестве параметров.                                                                               //
//==================================================================================================//

void part_2()
{
	Uptr<Date> date1(new Date(12, 9, 2022));
	Uptr<Date> date2(new Date(15, 9, 2022));
	Uptr<Date> date3(new Date(17, 9, 2022));

	cout << *compares_dates(date1, date2) << endl;
	swap_dates(date2, date3);
	cout << *compares_dates(date1, date2) << endl;
}
int main()
{
cout << endl << "PART-1.\n=====================================================" << endl << endl;
{
	part_1();
}
cout << endl << "PART-2.\n=====================================================" << endl << endl;
{
	part_2();
}
	return 0;
}
