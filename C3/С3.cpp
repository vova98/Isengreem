// С3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int num = 0, isOk = 0, mas[4] = {};
	scanf_s("%d", &num);
	isOk=lagrange(mas,num);
	for (int i = 3; i >= 0;i--)
	printf("%d ", mas[i]);
	return 0;
}

