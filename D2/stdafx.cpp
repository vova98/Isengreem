// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// D2.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"

int func(int n, int k)
{
	if (n == 1 || n == 0) return 1;
	if (k > 1) return func(n - k, k - 1) + func(n, k - 1);
	else return 0;
}
