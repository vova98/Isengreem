// B6.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int count = 0, countN = 0, array[616] = {};

	scanf_s("%d", &count);
	countN = numberCounter(count, array);
	for (int i = 0; i < countN; i++)
		printf("%d ", array[i]);
	printf("\n%d\n", countN);
	return 0;
}

