#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Wood_Functions.h"

#define countingWood  50
#define numberNodes  10000
#define MAX 10000

using namespace std;


int main() {
	
// 1. Функция проверяющая является ли переданное в неё бинарное дерево сбалансированным//
//=====================================================================================//
// 2. Создать [50] деревьев по [10000] узлов и заполнит узлы целочисленными значениями//
//=====================================================================================//
// 3. Рассчитать, какой процент из созданных деревьев являются сбалансированными//
//=====================================================================================//
	int balancWd = 0;
	int manBalancWoodcalc = 0;
	int ch = 5;
  
	Wood_Functions wood[countingWood];
	        for (int a = 0; a < countingWood; a++) 
	{
		      wood[a] = Wood_Functions(numberNodes, MAX);		

		          if (a % ch == 0)
		 {
			        wood[a].balance();
			        manBalancWoodcalc++;
		}

		      if (wood[a].checkBalance()) balancWd++;
	}
	printf("\n  Balanced wood manual: - %d \n  Balanced wood normal: - %d \n  Wood balances:- %d from %d \n \n Percentage of the created trees are balanced- result: %.0f%%\n\n ", manBalancWoodcalc, balancWd - manBalancWoodcalc, balancWd, countingWood, ((float) balancWd * 100 / countingWood));

// 4. Написать рекурсивную функцию бинарного поиска в дереве хранящемся в узлах, а не в массиве//

	Wood_Functions trust;
	trust. enter(0); trust.enter(3); trust.enter(4); trust.enter(10); trust.enter(14);
	trust.enter(6); trust.enter(5); trust.enter(17); trust.enter(11); trust.enter(9);
	
		trust.balance();
	              trust.print(); 

	int arr[] = {5,8,10,19,24,0,1,7,22,9};
	for(int a = 0; a < 10; a++) {
		cout << arr[a] << " is " << (trust.find(arr[a]) ? "available" : "no available") << "\n";
	}


	return 0;
} 
