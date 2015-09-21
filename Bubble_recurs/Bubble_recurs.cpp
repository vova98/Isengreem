// Bubble_recurs.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int sortArray[CountELem], curElem = 0, LastElem = CountELem;
	int isOk = InitArray(sortArray);


	BubbleSort(sortArray, curElem, &LastElem);

	for (int i = 0; i < CountELem; i++)
		printf("%d ", sortArray[i]);
	printf("\n");

	return 0;
}

