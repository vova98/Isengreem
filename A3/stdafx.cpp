// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// A3.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"

int NOD(int a, int b)
{
	//int x = 0;
	if (a != 0)
		return NOD(b%a,a);
	else return b;

	return b;
}
