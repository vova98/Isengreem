// C4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	FILE *filein;
	errno_t err = fopen_s(&filein, "input.txt", "r");
	char arrayConvers[1000] = {};
	int isOk = convers(filein);

	return 0;
}

