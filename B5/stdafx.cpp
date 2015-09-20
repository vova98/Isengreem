// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// B5.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"

long long summaDiv(int numb)
{
	int summa = 0;
	for (int i = 1; i <= (numb + 1) / 2; i++)
	if (numb%i == 0)
		summa += i;

	summa += numb;
	return summa;
}