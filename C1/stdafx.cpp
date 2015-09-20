// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// C1.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"

bool isWeigh(int num)
{
	while (num > 1)
	{
		if (num % 4 != 2)
		if (num % 4 != 3)
			num = num / 4;
		else num = num / 4 + 1;
		else return true; 
	}
	return false;
}
