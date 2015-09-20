// B5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int numb = 0;
	

	scanf_s("%d", &numb);

	long long summaDividers = summaDiv(numb);

	printf("%lli\n", summaDividers);
	return 0;
}

