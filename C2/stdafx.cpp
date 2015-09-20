// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// C2.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"

int reshetoEratosfena(int mas[], int num)
{
	bool arr[maxN + 1000] = {false};
	//int mas[maxN];
	int k=1,j=0;
	for (int i = 2; i <= maxN; i++)
	{
		j = 2;
		while (i*j <= maxN || k<=num)
		{
			arr[i*j] = true;
			j++;
		}
	}
	j = 0;
	for (int i = 0; i < maxN + 1000;i++)
	if (!arr[i]) { mas[j] = i; j++; }
	return 1;
}
