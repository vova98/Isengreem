// C1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int num=0;
	bool flag = false;
	scanf_s("%d", &num);
	flag = isWeigh(num);

	if (!flag) printf_s("YES\n");
	else printf_s("NO\n");
	return 0;
}

