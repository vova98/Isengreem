// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// B2.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"

int normalroot(int num, int* A, int* B)
{
	for (int i = 1; i <= ceil(sqrt(num)); i++)
	{
		int sqrI = i*i;
		if (num%sqrI == 0)
			*B = i;
	}
	*A = num / (*B*(*B));
	return Happy;
}
