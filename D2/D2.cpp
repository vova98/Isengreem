// D2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int num = 0;
	int count = 0;

	//if (scanf_s("%d", &num) != 1)
	if (scanf_s("%d", &num) != 1)
		printf("You entered wrong symbol!\n");
	else
	count = func(num, num);

	printf("%d\n", count);
	return 0;
}

