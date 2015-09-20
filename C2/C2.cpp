// C2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	ofstream fout("output.txt");
	int num = 0, mas[10000] = {},isOk=0;
	cin >> num;
	isOk = reshetoEratosfena(mas,10000);
	for (int i = 0; i < 10000; i++)
	fout << mas[num]<<", ";

	return 0;
}

