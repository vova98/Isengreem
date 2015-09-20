// C5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int count = 0;
	scanf_s("%d", &count);
	StudAndMark* arrayOfStud = InputData(count);
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < arrayOfStud[i].surnlength; j++)
			printf("%c", arrayOfStud[i].surname[j]);
		printf(" %d", arrayOfStud[i].mark);
	}


	return 0;
}

