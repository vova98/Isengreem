// B2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int num = 0, B = 0, A = 0;
	scanf_s("%d", &num);

	int isHappy=normalroot(num, &A, &B);

	printf("%d %d\n", A, B);
	return 0;
}

