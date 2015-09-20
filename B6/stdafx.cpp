// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// B6.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"

int numberCounter(int count, int* arrayNum)
{
	int summa = 0, tmp = 0, countN = 0;

	if (count > 36 || count < 1)
		printf("0\n");
	else
	{
		for (int i = 1000; i < 10000; i++)
		{
			tmp = i;
			for (int j = 0; j < 5; j++)
			{
				summa += tmp % 10;
				tmp = tmp / 10;
			}
			if (summa == count)
			{
				arrayNum[countN] = i;
				//printf("%d ", i);
				countN++;
			}
			summa = 0;
		}
	}
	return countN;
}