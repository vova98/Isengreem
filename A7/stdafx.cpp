// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// A7.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"




int* makegrad2(FILE* fileout)
{
	int* arr = new int [32];
	arr[0] = 1;
	fprintf_s(fileout, "%d, ", arr[0]);
	for (int i = 1; i < 32; i++)
	{
		arr[i] = arr[i - 1] * 2;
		fprintf_s(fileout, "%d, ", arr[i]);
	}
	return arr;
}
