// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// SelectSort_recurs.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"

int InitArray(int* sortArray)
{

	srand(time(0));
	for (int i = 0; i < CountELem; i++)
		sortArray[i] = rand() % 10 + 1;

	//for (int i = 0; i < CountELem; i++)
	//	printf("%d ", sortArray[i]);

	return allOk;
}

int SelectSort(int* sortArray, int curFirst)
{
	int MinElem = MAX_INT, CurElem = 0;

	for (int i = curFirst; i < CountELem;i++)
	if (sortArray[i] < MinElem)
	{
		MinElem = sortArray[i];
		CurElem = i;
	}

	Swap(&sortArray[curFirst], &sortArray[CurElem]);

	if (curFirst == CountELem-1)
		return *sortArray;
	else return SelectSort(sortArray, curFirst+1);
}

void Swap(int* First, int* Second)
{
	int Tmp = 0;
	Tmp = *First;
	*First = *Second;
	*Second = Tmp;
}