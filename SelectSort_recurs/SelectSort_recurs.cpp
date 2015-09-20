// SelectSort_recurs.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int sortArray[CountELem] = {};
	int isOk = InitArray(sortArray);
	int curFirst = 0;
	
	SelectSort(sortArray, curFirst);
	
	for (int i = 0; i < CountELem; i++)
		printf("%d ", sortArray[i]);
	printf("\n");
	return 0;
}


