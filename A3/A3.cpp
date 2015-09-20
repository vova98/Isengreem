// A3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int fir = 0, sec = 0, thi = 0, nod1 = 0, nod2 = 0, nok1 = 0, NOK = 0;
	scanf_s("%d %d %d", &fir, &sec, &thi);
	nod1 = NOD(fir, sec);
	nok1 = (fir / nod1)*sec;
	nod2 = NOD(nok1, thi);
	NOK = (nok1 / nod2)*thi;

	printf("%d\n", NOK);
	return 0;
}

