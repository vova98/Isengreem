// B1.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include "stdafx.h"


int main(int argc, _TCHAR* argv[])
{
		setlocale(LC_ALL, "rus");
		int num = 0;
		bool flag = false;

		cout << "¬ведите число, программа вычислит, есть ли среди его делителей точные квадраты\n";
		cin >> num;

		flag = isSimple(num);

		if (flag) cout << "YES\n";
		else cout << "NO\n";
		//system("")
		return 0;
		
}

