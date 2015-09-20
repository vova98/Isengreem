// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// C5.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"

StudAndMark* InputData(int count)
{
	int j = 0;
	char letter = '0';
	StudAndMark* arrayStud = new StudAndMark[count];
	//if (!arrayStud) { errno = enomem; return NULL; }
	for (int i = 0; i < count; i++)
	{
		while (letter != ' ')
		{
			scanf_s("%c", &letter);
			arrayStud[i].surname[j] = letter;
			j++;
		}
		arrayStud[i].surnlength = j;
		j = 0;
		scanf_s("%d", &arrayStud[i].mark);
	}
	return arrayStud;
}
